/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Copyright by The HDF Group.                                               *
 * Copyright by the Board of Trustees of the University of Illinois.         *
 * All rights reserved.                                                      *
 *                                                                           *
 * This file is part of HDF5.  The full HDF5 copyright notice, including     *
 * terms governing use, modification, and redistribution, is contained in    *
 * the files COPYING and Copyright.html.  COPYING can be found at the root   *
 * of the source code distribution tree; Copyright.html can be found at the  *
 * root level of an installed copy of the electronic HDF5 document set and   *
 * is linked from the top-level documents page.  It can also be found at     *
 * http://hdfgroup.org/HDF5/doc/Copyright.html.  If you do not have          *
 * access to either file, you may request a copy from help@hdfgroup.org.     *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/*
 * Programmer:  Robb Matzke <matzke@llnl.gov>
 *              Thursday, July 29, 1999
 *
 * Purpose:	The POSIX unbuffered file driver using only the HDF5 public
 *		API and with a few optimizations: the lseek() call is made
 *		only when the current file position is unknown or needs to be
 *		changed based on previous I/O through this driver (don't mix
 *		I/O from this driver with I/O from other parts of the
 *		application to the same file).
 */

/* Interface initialization */
#define H5_INTERFACE_INIT_FUNC	H5FD_ceph_init_interface


#include "H5private.h"		/* Generic Functions			*/
#include "H5Eprivate.h"		/* Error handling		  	*/
#include "H5Fprivate.h"		/* File access				*/
#include "H5FDprivate.h"	/* File drivers				*/
#include "H5FDceph.h"		/* ceph file driver			*/
#include "H5FLprivate.h"	/* Free Lists                           */
#include "H5Iprivate.h"		/* IDs			  		*/
#include "H5MMprivate.h"	/* Memory management			*/
#include "H5Pprivate.h"		/* Property lists			*/
#include "cephfs/libcephfs.h" /* Ceph header file */

/* The driver identification number, initialized at runtime */
static hid_t H5FD_CEPH_g = 0;

/* Since Windows doesn't follow the rest of the world when it comes
 * to POSIX I/O types, some typedefs and constants are needed to avoid
 * making the code messy with #ifdefs.
 */

/* Unix, everyone else */
typedef size_t          h5_ceph_io_t;
typedef ssize_t         h5_ceph_io_ret_t;
static size_t H5_CEPH_MAX_IO_BYTES_g = SSIZET_MAX;

typedef struct H5FD_ceph_fapl_t { 
  char              path_to_conf_file[H5FD_MAX_FILENAME_LEN];
  struct            ceph_mount_info *cmount;
} H5FD_ceph_fapl_t;
/* The description of a file belonging to this driver. The `eoa' and `eof'
 * determine the amount of hdf5 address space in use and the high-water mark
 * of the file (the current size of the underlying filesystem file). The
 * `pos' value is used to eliminate file position updates when they would be a
 * no-op. Unfortunately we've found systems that use separate file position
 * indicators for reading and writing so the lseek can only be eliminated if
 * the current operation is the same as the previous operation.  When opening
 * a file the `eof' will be set to the current file size, `eoa' will be set
 * to zero, `pos' will be set to H5F_ADDR_UNDEF (as it is when an error
 * occurs), and `op' will be set to H5F_OP_UNKNOWN.
 */
typedef struct H5FD_ceph_t {
    H5FD_t          pub;    /* public stuff, must be first      */
    int             fd;     /* the filesystem file descriptor   */
    haddr_t         eoa;    /* end of allocated region          */
    haddr_t         eof;    /* end of file; current file size   */
    haddr_t         pos;    /* current file I/O position        */
    H5FD_file_op_t  op;     /* last operation                   */
    char            filename[H5FD_MAX_FILENAME_LEN];    /* Copy of file name from open operation */
    /* On most systems the combination of device and i-node number uniquely
     * identify a file.  Note that Cygwin, MinGW and other Windows POSIX
     * environments have the stat function (which fakes inodes)
     * and will use the 'device + inodes' scheme as opposed to the
     * Windows code further below.
     */
    dev_t           device;     /* file device number   */
    ino_t           inode;      /* file i-node number   */
    H5FD_ceph_fapl_t  *fapl;   /* fapl for the file */

} H5FD_ceph_t;

/*
 * These macros check for overflow of various quantities.  These macros
 * assume that HDoff_t is signed and haddr_t and size_t are unsigned.
 *
 * ADDR_OVERFLOW:	Checks whether a file address of type `haddr_t'
 *			is too large to be represented by the second argument
 *			of the file seek function.
 *
 * SIZE_OVERFLOW:	Checks whether a buffer size of type `hsize_t' is too
 *			large to be represented by the `size_t' type.
 *
 * REGION_OVERFLOW:	Checks whether an address and size pair describe data
 *			which can be addressed entirely by the second
 *			argument of the file seek function.
 */
#define MAXADDR (((haddr_t)1<<(8*sizeof(HDoff_t)-1))-1)
#define ADDR_OVERFLOW(A)	(HADDR_UNDEF==(A) ||			      \
				 ((A) & ~(haddr_t)MAXADDR))
#define SIZE_OVERFLOW(Z)	((Z) & ~(hsize_t)MAXADDR)
#define REGION_OVERFLOW(A,Z)	(ADDR_OVERFLOW(A) || SIZE_OVERFLOW(Z) ||      \
                                 HADDR_UNDEF==(A)+(Z) ||		      \
				 (HDoff_t)((A)+(Z))<(HDoff_t)(A))

/* Prototypes */
static H5FD_t *H5FD_ceph_open(const char *name, unsigned flags, hid_t fapl_id,
			      haddr_t maxaddr);
static herr_t H5FD_ceph_close(H5FD_t *_file);
static int H5FD_ceph_cmp(const H5FD_t *_f1, const H5FD_t *_f2);
static herr_t H5FD_ceph_query(const H5FD_t *_f1, unsigned long *flags);
static haddr_t H5FD_ceph_get_eoa(const H5FD_t *_file, H5FD_mem_t type);
static herr_t H5FD_ceph_set_eoa(H5FD_t *_file, H5FD_mem_t type, haddr_t addr);
static haddr_t H5FD_ceph_get_eof(const H5FD_t *_file);
static herr_t  H5FD_ceph_get_handle(H5FD_t *_file, hid_t fapl, void** file_handle);
static herr_t H5FD_ceph_read(H5FD_t *_file, H5FD_mem_t type, hid_t fapl_id, haddr_t addr,
			     size_t size, void *buf);
static herr_t H5FD_ceph_write(H5FD_t *_file, H5FD_mem_t type, hid_t fapl_id, haddr_t addr,
			      size_t size, const void *buf);
static herr_t H5FD_ceph_truncate(H5FD_t *_file, hid_t dxpl_id, hbool_t closing);
static int H5FD_setup_ceph( H5FD_ceph_fapl_t *fa );
static void *H5FD_ceph_fapl_copy(const void *_old_fa);
static void *H5FD_ceph_fapl_get(H5FD_t *_file);

static const H5FD_class_t H5FD_ceph_g = {
    "ceph",					/*name			*/
    MAXADDR,					/*maxaddr		*/
    H5F_CLOSE_WEAK,				/* fc_degree		*/
    NULL,					/*sb_size		*/
    NULL,					/*sb_encode		*/
    NULL,					/*sb_decode		*/
    sizeof(H5FD_ceph_fapl_t), 						/*fapl_size		*/
    H5FD_ceph_fapl_get,					/*fapl_get		*/
    H5FD_ceph_fapl_copy,					/*fapl_copy		*/
    NULL, 					/*fapl_free		*/
    0,						/*dxpl_size		*/
    NULL,					/*dxpl_copy		*/
    NULL,					/*dxpl_free		*/
    H5FD_ceph_open,				/*open			*/
    H5FD_ceph_close,				/*close			*/
   // H5FD_ceph_cmp,				/*cmp			*/
    NULL,                   /* cmp */
    H5FD_ceph_query,				/*query			*/
    NULL,					/*get_type_map		*/
    NULL,					/*alloc			*/
    NULL,					/*free			*/
    H5FD_ceph_get_eoa,				/*get_eoa		*/
    H5FD_ceph_set_eoa, 				/*set_eoa		*/
    H5FD_ceph_get_eof,				/*get_eof		*/
    H5FD_ceph_get_handle,                       /*get_handle            */
    H5FD_ceph_read,				/*read			*/
    H5FD_ceph_write,				/*write			*/
    NULL,					/*flush			*/
    H5FD_ceph_truncate,				/*truncate		*/
    NULL,                                       /*lock                  */
    NULL,                                       /*unlock                */
    H5FD_FLMAP_SINGLE 				/*fl_map		*/
};

/* Declare a free list to manage the H5FD_ceph_t struct */
H5FL_DEFINE_STATIC(H5FD_ceph_t);


/*--------------------------------------------------------------------------
NAME
   H5FD_ceph_init_interface -- Initialize interface-specific information
USAGE
    herr_t H5FD_ceph_init_interface()

RETURNS
    Non-negative on success/Negative on failure
DESCRIPTION
    Initializes any interface-specific data or routines.  (Just calls
    H5FD_ceph_init currently).

--------------------------------------------------------------------------*/
static herr_t
H5FD_ceph_init_interface(void)
{
    FUNC_ENTER_NOAPI_NOINIT_NOFUNC(H5FD_ceph_init_interface)

    FUNC_LEAVE_NOAPI(H5FD_ceph_init())
} /* H5FD_ceph_init_interface() */


/*-------------------------------------------------------------------------
 * Function:	H5FD_ceph_init
 *
 * Purpose:	Initialize this driver by registering the driver with the
 *		library.
 *
 * Return:	Success:	The driver ID for the ceph driver.
 *		Failure:	Negative.
 *
 * Programmer:	Robb Matzke
 *              Thursday, July 29, 1999
 *
 *-------------------------------------------------------------------------
 */
hid_t
H5FD_ceph_init(void)
{
    hid_t ret_value;            /* Return value */

    FUNC_ENTER_NOAPI(H5FD_ceph_init, FAIL)

    if(H5I_VFL != H5I_get_type(H5FD_CEPH_g))
        H5FD_CEPH_g = H5FD_register(&H5FD_ceph_g, sizeof(H5FD_class_t), FALSE);

    /* Set return value */
    ret_value = H5FD_CEPH_g;

done:
    FUNC_LEAVE_NOAPI(ret_value)
} /* end H5FD_ceph_init() */


/*---------------------------------------------------------------------------
 * Function:	H5FD_ceph_term
 *
 * Purpose:	Shut down the VFD
 *
 * Returns:     <none>
 *
 * Programmer:  Quincey Koziol
 *              Friday, Jan 30, 2004
 *
 *---------------------------------------------------------------------------
 */
void
H5FD_ceph_term(void)
{
    FUNC_ENTER_NOAPI_NOINIT_NOFUNC(H5FD_ceph_term)

    /* Reset VFL ID */
    H5FD_CEPH_g = 0;

    FUNC_LEAVE_NOAPI_VOID
} /* end H5FD_ceph_term() */


/*-------------------------------------------------------------------------
 * Function:	H5Pset_fapl_ceph
 *
 * Purpose:	Modify the file access property list to use the H5FD_CEPH
 *		driver defined in this source file.  There are no driver
 *		specific properties.
 *
 * Return:	Non-negative on success/Negative on failure
 *
 * Programmer:	Robb Matzke
 *		Thursday, February 19, 1998
 *
 *-------------------------------------------------------------------------
 */

static int 
H5FD_setup_ceph( H5FD_ceph_fapl_t *fa ) { 
    int ret_value = 0;
    FUNC_ENTER_NOAPI(H5FD_setup_ceph, FAIL)

    ret_value = ceph_create(&fa->cmount, NULL);
    if ( ret_value ) { 
        HGOTO_ERROR(H5E_ARGS, H5E_BADVALUE, NULL, "ceph_create failed")
    }

   ret_value = ceph_conf_read_file(fa->cmount, fa->path_to_conf_file);

   if ( ret_value ) { 
        HGOTO_ERROR(H5E_ARGS, H5E_BADVALUE, NULL, 
                    "ceph_conf_read_file failed for conf file %s", fa->path_to_conf_file)
   }

   ret_value = ceph_mount(fa->cmount, NULL);
   if ( ret_value ) { 
        HGOTO_ERROR(H5E_ARGS, H5E_BADVALUE, NULL, "ceph_mount failed")
   }

  done:
    FUNC_LEAVE_NOAPI(ret_value)
}

herr_t
H5Pset_fapl_ceph(hid_t fapl_id, const char *conf_file_path)
{
    H5P_genplist_t *plist;      /* Property list pointer */
    H5FD_ceph_fapl_t  fa;
    herr_t ret_value;

    FUNC_ENTER_API(H5Pset_fapl_ceph, FAIL)
    H5TRACE1("e", "i", fapl_id);

    if(NULL == (plist = H5P_object_verify(fapl_id, H5P_FILE_ACCESS)))
        HGOTO_ERROR(H5E_ARGS, H5E_BADTYPE, FAIL, "not a file access property list")

    /* Create the new file struct */
    /*
    if(NULL == (fa = malloc(sizeof(*fa))))
        HGOTO_ERROR(H5E_RESOURCE, H5E_NOSPACE, NULL, "unable to allocate fapl struct")
    */

    HDstrncpy(fa.path_to_conf_file, conf_file_path, sizeof(fa.path_to_conf_file));
    fa.path_to_conf_file[sizeof(fa.path_to_conf_file) - 1] = '\0';
    //HDstrncpy(file->filename, name, sizeof(file->filename));
    //file->filename[sizeof(file->filename) - 1] = '\0';

    // lets setup the mount and what not here
    ret_value = H5FD_setup_ceph(&fa);
    if (  ret_value  ) { 
      HGOTO_ERROR(H5E_ARGS, H5E_BADTYPE, FAIL, "H5FD_setup_ceph failed")
    }

    ret_value = H5P_set_driver(plist, H5FD_CEPH, &fa);
    /*
    if (  ret_value  ) { 
      printf("H5P_set_driver failed with status %d\n", ret_value);
      HGOTO_ERROR(H5E_ARGS, H5E_BADTYPE, FAIL, "H5P_set_driver failed")
    }
    */

done:
    FUNC_LEAVE_API(ret_value)
} /* end H5Pset_fapl_ceph() */

static herr_t 
H5FD_ceph_stat(void *_mount, const char *file, h5_stat_t *stat) 
{
    int ret_value = 0;
    struct ceph_mount_info *cmount = (struct ceph_mount_info *)_mount;

    FUNC_ENTER_API(H5FD_ceph_stat, FAIL)

    int o_flags = O_RDONLY;
    int fd = ceph_open(cmount, file, o_flags, 0666);
    if ( fd < 0 ) {
        int myerrno = errno;
        HGOTO_ERROR(H5E_FILE, H5E_CANTOPENFILE, NULL, "unable to open file %s fd %d errno %d %s",
                    file, fd, myerrno, HDstrerror(myerrno));
    }

    ret_value = ceph_fstat(cmount, fd, stat); 
    if ( ret_value < 0 ) {
        HGOTO_ERROR(H5E_FILE, H5E_BADFILE, NULL, "unable to stat file %s",
                        file);
    }

done:
    FUNC_LEAVE_API(ret_value)
}


/*-------------------------------------------------------------------------
 * Function:	H5FD_ceph_open
 *
 * Purpose:	Create and/or opens a file as an HDF5 file.
 *
 * Return:	Success:	A pointer to a new file data structure. The
 *				public fields will be initialized by the
 *				caller, which is always H5FD_open().
 *		Failure:	NULL
 *
 * Programmer:	Robb Matzke
 *              Thursday, July 29, 1999
 *
 *-------------------------------------------------------------------------
 */
static H5FD_t *
H5FD_ceph_open(const char *name, unsigned flags, hid_t fapl_id, haddr_t maxaddr)
{
    H5FD_ceph_t     *file       = NULL;     /* ceph VFD info            */
    int             fd          = -1;       /* File descriptor          */
    int             o_flags;                /* Flags for open() call    */
    h5_stat_t       sb;
    H5FD_t          *ret_value;             /* Return value             */
    H5P_genplist_t      *plist;      /* Property list pointer */
    H5FD_ceph_fapl_t  *fa;
    H5FD_ceph_fapl_t  *new_fa;
    const char      *conf_file_path;
    int ret_int = 0;

    FUNC_ENTER_NOAPI_NOINIT(H5FD_ceph_open)

    /* Sanity check on file offsets */
    HDcompile_assert(sizeof(HDoff_t) >= sizeof(size_t));

    /* Check arguments */
    if(!name || !*name)
        HGOTO_ERROR(H5E_ARGS, H5E_BADVALUE, NULL, "invalid file name")
    if(0 == maxaddr || HADDR_UNDEF == maxaddr)
        HGOTO_ERROR(H5E_ARGS, H5E_BADRANGE, NULL, "bogus maxaddr")
    if(ADDR_OVERFLOW(maxaddr))
        HGOTO_ERROR(H5E_ARGS, H5E_OVERFLOW, NULL, "bogus maxaddr")

    /* Build the open flags */
    o_flags = (H5F_ACC_RDWR & flags) ? O_RDWR : O_RDONLY;
    if(H5F_ACC_TRUNC & flags) 
        o_flags |= O_TRUNC;
    if(H5F_ACC_CREAT & flags) 
        o_flags |= O_CREAT;
    if(H5F_ACC_EXCL & flags) 
        o_flags |= O_EXCL;

    // get the fapl
    if(NULL == (plist = H5P_object_verify(fapl_id, H5P_FILE_ACCESS)))
      HGOTO_ERROR(H5E_ARGS, H5E_BADTYPE, FAIL, "not a file access list")

    if(NULL == (fa=H5P_get_driver_info(plist)))
      HGOTO_ERROR(H5E_PLIST, H5E_BADVALUE, FAIL, "bad VFL driver info")


    /* Open the file */
    fd = ceph_open(fa->cmount, name, o_flags, 0666);
    if ( fd < 0 ) {
        int myerrno = errno;
        HGOTO_ERROR(H5E_FILE, H5E_CANTOPENFILE, NULL, 
                    "unable to open file %s fd %d errno %d %s",
                    name, fd, myerrno, HDstrerror(myerrno));
    }

    ret_int = ceph_fstat(fa->cmount, fd, &sb); 
    if ( ret_int < 0 ) {
        HGOTO_ERROR(H5E_FILE, H5E_BADFILE, NULL, "unable to stat file %s",
                        name);
    }

    /* Create the new file struct */
    if(NULL == (file = H5FL_CALLOC(H5FD_ceph_t)))
        HGOTO_ERROR(H5E_RESOURCE, H5E_NOSPACE, NULL, "unable to allocate file struct")

    file->fd = fd;
    H5_ASSIGN_OVERFLOW(file->eof, sb.st_size, h5_stat_size_t, haddr_t);
    file->pos = HADDR_UNDEF;
    file->op = OP_UNKNOWN;

    file->device = sb.st_dev;
    file->inode = sb.st_ino;

    /* Retain a copy of the name used to open the file, for possible error reporting */
    HDstrncpy(file->filename, name, sizeof(file->filename));
    file->filename[sizeof(file->filename) - 1] = '\0';

    // make a copy of the fapl and store it in the file 
    new_fa = H5FD_ceph_fapl_copy(fa);
    file->fapl = new_fa;

    /* Set return value */
    ret_value = (H5FD_t*)file;

done:
    if(NULL == ret_value) {
        printf("error with opening the file, in done of H5FD_ceph_open\n");

        if(fd >= 0) { 
          ret_value = ceph_close((file->fapl)->cmount, file->fd);
          if( ret_value < 0)
            HSYS_GOTO_ERROR(H5E_IO, H5E_CANTCLOSEFILE, FAIL, "unable to close file")
        }
        if(file)
            file = H5FL_FREE(H5FD_ceph_t, file);
    } /* end if */

    FUNC_LEAVE_NOAPI(ret_value)
} /* end H5FD_ceph_open() */


/*-------------------------------------------------------------------------
 * Function:	H5FD_ceph_close
 *
 * Purpose:	Closes an HDF5 file.
 *
 * Return:	Success:	0
 *		Failure:	-1, file not closed.
 *
 * Programmer:	Robb Matzke
 *              Thursday, July 29, 1999
 *
 *-------------------------------------------------------------------------
 */
static herr_t
H5FD_ceph_close(H5FD_t *_file)
{
    H5FD_ceph_t	*file = (H5FD_ceph_t *)_file;
    herr_t ret_value = SUCCEED;                 /* Return value */

    FUNC_ENTER_NOAPI_NOINIT(H5FD_ceph_close)

    /* Sanity check */
    HDassert(file);

    /* Close the underlying file */
    ret_value = ceph_close((file->fapl)->cmount, file->fd);
    if( ret_value < 0)
        HSYS_GOTO_ERROR(H5E_IO, H5E_CANTCLOSEFILE, FAIL, "unable to close file")

    /* Release the file info */
    file = H5FL_FREE(H5FD_ceph_t, file);

done:
    FUNC_LEAVE_NOAPI(ret_value)
} /* end H5FD_ceph_close() */


/*-------------------------------------------------------------------------
 * Function:	H5FD_ceph_cmp
 *
 * Purpose:	Compares two files belonging to this driver using an
 *		arbitrary (but consistent) ordering.
 *
 * Return:	Success:	A value like strcmp()
 *		Failure:	never fails (arguments were checked by the
 *				caller).
 *
 * Programmer:	Robb Matzke
 *              Thursday, July 29, 1999
 *
 *-------------------------------------------------------------------------
 */
static int
H5FD_ceph_cmp(const H5FD_t *_f1, const H5FD_t *_f2)
{
    const H5FD_ceph_t	*f1 = (const H5FD_ceph_t *)_f1;
    const H5FD_ceph_t	*f2 = (const H5FD_ceph_t *)_f2;
    int ret_value = 0;

    FUNC_ENTER_NOAPI_NOINIT_NOFUNC(H5FD_ceph_cmp)

    /* If dev_t isn't a scalar value on this system, just use memcmp to
     * determine if the values are the same or not.  The actual return value
     * shouldn't really matter...
     */
    if(HDmemcmp(&(f1->device),&(f2->device),sizeof(dev_t)) < 0) HGOTO_DONE(-1)
    if(HDmemcmp(&(f1->device),&(f2->device),sizeof(dev_t)) > 0) HGOTO_DONE(1)
    if(f1->inode < f2->inode) HGOTO_DONE(-1)
    if(f1->inode > f2->inode) HGOTO_DONE(1)

done:
    FUNC_LEAVE_NOAPI(ret_value)
} /* end H5FD_ceph_cmp() */


/*-------------------------------------------------------------------------
 * Function:	H5FD_ceph_query
 *
 * Purpose:	Set the flags that this VFL driver is capable of supporting.
 *              (listed in H5FDpublic.h)
 *
 * Return:	Success:	non-negative
 *		Failure:	negative
 *
 * Programmer:	Quincey Koziol
 *              Friday, August 25, 2000
 *
 *-------------------------------------------------------------------------
 */
static herr_t
H5FD_ceph_query(const H5FD_t *_file, unsigned long *flags /* out */)
{
    const H5FD_ceph_t	*file = (const H5FD_ceph_t *)_file;    /* ceph VFD info */

    FUNC_ENTER_NOAPI_NOINIT_NOFUNC(H5FD_ceph_query)

    /* Set the VFL feature flags that this driver supports */
    if(flags) {
        *flags = 0;
        *flags |= H5FD_FEAT_AGGREGATE_METADATA;     /* OK to aggregate metadata allocations                             */
        *flags |= H5FD_FEAT_ACCUMULATE_METADATA;    /* OK to accumulate metadata for faster writes                      */
        *flags |= H5FD_FEAT_DATA_SIEVE;             /* OK to perform data sieving for faster raw data reads & writes    */
        *flags |= H5FD_FEAT_AGGREGATE_SMALLDATA;    /* OK to aggregate "small" raw data allocations                     */
        *flags |= H5FD_FEAT_POSIX_COMPAT_HANDLE;    /* VFD handle is POSIX I/O call compatible                          */

    } /* end if */

    FUNC_LEAVE_NOAPI(SUCCEED)
} /* end H5FD_ceph_query() */


/*-------------------------------------------------------------------------
 * Function:	H5FD_ceph_get_eoa
 *
 * Purpose:	Gets the end-of-address marker for the file. The EOA marker
 *		is the first address past the last byte allocated in the
 *		format address space.
 *
 * Return:	Success:	The end-of-address marker.
 *		Failure:	HADDR_UNDEF
 *
 * Programmer:	Robb Matzke
 *              Monday, August  2, 1999
 *
 *-------------------------------------------------------------------------
 */
/* ARGSUSED */
static haddr_t
H5FD_ceph_get_eoa(const H5FD_t *_file, H5FD_mem_t UNUSED type)
{
    const H5FD_ceph_t	*file = (const H5FD_ceph_t *)_file;

    FUNC_ENTER_NOAPI_NOINIT_NOFUNC(H5FD_ceph_get_eoa)

    FUNC_LEAVE_NOAPI(file->eoa)
} /* end H5FD_ceph_get_eoa() */


/*-------------------------------------------------------------------------
 * Function:	H5FD_ceph_set_eoa
 *
 * Purpose:	Set the end-of-address marker for the file. This function is
 *		called shortly after an existing HDF5 file is opened in order
 *		to tell the driver where the end of the HDF5 data is located.
 *
 * Return:	Success:	0
 *		Failure:	-1
 *
 * Programmer:	Robb Matzke
 *              Thursday, July 29, 1999
 *
 *-------------------------------------------------------------------------
 */
/* ARGSUSED */
static herr_t
H5FD_ceph_set_eoa(H5FD_t *_file, H5FD_mem_t UNUSED type, haddr_t addr)
{
    H5FD_ceph_t	*file = (H5FD_ceph_t *)_file;

    FUNC_ENTER_NOAPI_NOINIT_NOFUNC(H5FD_ceph_set_eoa)

    file->eoa = addr;

    FUNC_LEAVE_NOAPI(SUCCEED)
} /* end H5FD_ceph_set_eoa() */


/*-------------------------------------------------------------------------
 * Function:	H5FD_ceph_get_eof
 *
 * Purpose:	Returns the end-of-file marker, which is the greater of
 *		either the filesystem end-of-file or the HDF5 end-of-address
 *		markers.
 *
 * Return:	Success:	End of file address, the first address past
 *				the end of the "file", either the filesystem file
 *				or the HDF5 file.
 *		Failure:	HADDR_UNDEF
 *
 * Programmer:	Robb Matzke
 *              Thursday, July 29, 1999
 *
 *-------------------------------------------------------------------------
 */
static haddr_t
H5FD_ceph_get_eof(const H5FD_t *_file)
{
    const H5FD_ceph_t	*file = (const H5FD_ceph_t *)_file;

    FUNC_ENTER_NOAPI_NOINIT_NOFUNC(H5FD_ceph_get_eof)

    FUNC_LEAVE_NOAPI(MAX(file->eof, file->eoa))
} /* end H5FD_ceph_get_eof() */


/*-------------------------------------------------------------------------
 * Function:       H5FD_ceph_get_handle
 *
 * Purpose:        Returns the file handle of ceph file driver.
 *
 * Returns:        Non-negative if succeed or negative if fails.
 *
 * Programmer:     Raymond Lu
 *                 Sept. 16, 2002
 *
 *-------------------------------------------------------------------------
 */
/* ARGSUSED */
static herr_t
H5FD_ceph_get_handle(H5FD_t *_file, hid_t UNUSED fapl, void **file_handle)
{
    H5FD_ceph_t         *file = (H5FD_ceph_t *)_file;
    herr_t              ret_value = SUCCEED;

    FUNC_ENTER_NOAPI_NOINIT(H5FD_ceph_get_handle)

    if(!file_handle)
        HGOTO_ERROR(H5E_ARGS, H5E_BADVALUE, FAIL, "file handle not valid")

    *file_handle = &(file->fd);

done:
    FUNC_LEAVE_NOAPI(ret_value)
} /* end H5FD_ceph_get_handle() */


/*-------------------------------------------------------------------------
 * Function:	H5FD_ceph_read
 *
 * Purpose:	Reads SIZE bytes of data from FILE beginning at address ADDR
 *		into buffer BUF according to data transfer properties in
 *		DXPL_ID.
 *
 * Return:	Success:	Zero. Result is stored in caller-supplied
 *				buffer BUF.
 *		Failure:	-1, Contents of buffer BUF are undefined.
 *
 * Programmer:	Robb Matzke
 *              Thursday, July 29, 1999
 *
 *-------------------------------------------------------------------------
 */
/* ARGSUSED */
static herr_t
H5FD_ceph_read(H5FD_t *_file, H5FD_mem_t UNUSED type, hid_t UNUSED dxpl_id,
    haddr_t addr, size_t size, void *buf /*out*/)
{
    H5FD_ceph_t     *file       = (H5FD_ceph_t *)_file;
    herr_t          ret_value   = SUCCEED;                  /* Return value */

    FUNC_ENTER_NOAPI_NOINIT(H5FD_ceph_read)

    HDassert(file && file->pub.cls);
    HDassert(buf);

    /* Check for overflow conditions */
    if(!H5F_addr_defined(addr))
        HGOTO_ERROR(H5E_ARGS, H5E_BADVALUE, FAIL, "addr undefined, addr = %llu", (unsigned long long)addr)
    if(REGION_OVERFLOW(addr, size))
        HGOTO_ERROR(H5E_ARGS, H5E_OVERFLOW, FAIL, "addr overflow, addr = %llu", (unsigned long long)addr)
    if((addr + size) > file->eoa)
        HGOTO_ERROR(H5E_ARGS, H5E_OVERFLOW, FAIL, "addr overflow, addr = %llu, size=%lu, eoa=%llu", 
                    (unsigned long long)addr, size, (unsigned long long)file->eoa)

    /* Seek to the correct location */
    if(addr != file->pos || OP_READ != file->op) {
        if( ceph_lseek( (file->fapl)->cmount, file->fd, (HDoff_t)addr, SEEK_SET)<0)
            HSYS_GOTO_ERROR(H5E_IO, H5E_SEEKERROR, FAIL, "unable to ceph_lseek to proper position")

            
    }  // end if 

    /* Read data, being careful of interrupted system calls, partial results,
     * and the end of the file.
     */
    while(size > 0) {

        h5_ceph_io_t        bytes_in        = 0;    /* # of bytes to read       */
        h5_ceph_io_ret_t    bytes_read      = -1;   /* # of bytes actually read */ 

        /* Trying to read more bytes than the return type can handle is
         * undefined behavior in POSIX.
         */
        if(size > H5_CEPH_MAX_IO_BYTES_g)
            bytes_in = H5_CEPH_MAX_IO_BYTES_g;
        else
            bytes_in = (h5_ceph_io_t)size;

        do {
            bytes_read = ceph_read((file->fapl)->cmount, file->fd, buf, 
                                   (loff_t)bytes_in, (loff_t)addr);

        } while(-1 == bytes_read && EINTR == errno);
        
        if(-1 == bytes_read) { /* error */
            int myerrno = errno;
            time_t mytime = HDtime(NULL);
            printf("bytes_read == -1, erroring out\n");
            HDoff_t myoffset =  ceph_lseek( (file->fapl)->cmount, file->fd, 
                                            (HDoff_t)0, SEEK_CUR);

            HGOTO_ERROR(H5E_IO, H5E_READERROR, FAIL, "file read failed: time = %s, filename = '%s', file descriptor = %d, errno = %d, error message = '%s', buf = %p, size = %lu, offset = %llu", HDctime(&mytime), file->filename, file->fd, myerrno, HDstrerror(myerrno), buf, (unsigned long)size, (unsigned long long)myoffset);
        } /* end if */
        
        if(0 == bytes_read) {
            /* end of file but not end of format address space */
            HDmemset(buf, 0, size);
            break;
        } /* end if */
        
        HDassert(bytes_read >= 0);
        HDassert((size_t)bytes_read <= size);
        
        size -= (size_t)bytes_read;
        addr += (haddr_t)bytes_read;
        buf = (char *)buf + bytes_read;
    } /* end while */

    /* Update current position */
    file->pos = addr;
    file->op = OP_READ;

done:
    if(ret_value < 0) {
        /* Reset last file I/O information */
        file->pos = HADDR_UNDEF;
        file->op = OP_UNKNOWN;
    } /* end if */

    FUNC_LEAVE_NOAPI(ret_value)
} /* end H5FD_ceph_read() */


/*-------------------------------------------------------------------------
 * Function:	H5FD_ceph_write
 *
 * Purpose:	Writes SIZE bytes of data to FILE beginning at address ADDR
 *		from buffer BUF according to data transfer properties in
 *		DXPL_ID.
 *
 * Return:	Success:	Zero
 *		Failure:	-1
 *
 * Programmer:	Robb Matzke
 *              Thursday, July 29, 1999
 *
 *-------------------------------------------------------------------------
 */
/* ARGSUSED */
static herr_t
H5FD_ceph_write(H5FD_t *_file, H5FD_mem_t UNUSED type, hid_t UNUSED dxpl_id,
                haddr_t addr, size_t size, const void *buf)
{
    H5FD_ceph_t     *file       = (H5FD_ceph_t *)_file;
    herr_t          ret_value   = SUCCEED;                  /* Return value */

    FUNC_ENTER_NOAPI_NOINIT(H5FD_ceph_write)

    HDassert(file && file->pub.cls);
    HDassert(buf);

    /* Check for overflow conditions */
    if(!H5F_addr_defined(addr))
        HGOTO_ERROR(H5E_ARGS, H5E_BADVALUE, FAIL, 
                    "addr undefined, addr = %llu", (unsigned long long)addr)
    if(REGION_OVERFLOW(addr, size))
        HGOTO_ERROR(H5E_ARGS, H5E_OVERFLOW, FAIL, 
                    "addr overflow, addr = %llu, size = %llu", 
                    (unsigned long long)addr, (unsigned long long)size)
    if((addr + size) > file->eoa)
        HGOTO_ERROR(H5E_ARGS, H5E_OVERFLOW, FAIL, 
                    "addr overflow, addr = %llu, size = %llu, eoa = %llu", 
                    (unsigned long long)addr, (unsigned long long)size, 
                    (unsigned long long)file->eoa)

    /* Seek to the correct location */
    if(addr != file->pos || OP_WRITE != file->op) {
      if( ceph_lseek( (file->fapl)->cmount, file->fd, (HDoff_t)addr, SEEK_SET) < 0)
          HSYS_GOTO_ERROR(H5E_IO, H5E_SEEKERROR, FAIL, 
                          "unable to ceph_lseek to proper position")
    } 

    /* Write the data, being careful of interrupted system calls and partial
     * results
     */
    while(size > 0) {

        h5_ceph_io_t        bytes_in        = 0;    /* # of bytes to write  */
        h5_ceph_io_ret_t    bytes_wrote     = -1;   /* # of bytes written   */ 

        /* Trying to write more bytes than the return type can handle is
         * undefined behavior in POSIX.
         */
        if(size > H5_CEPH_MAX_IO_BYTES_g)
            bytes_in = H5_CEPH_MAX_IO_BYTES_g;
        else
            bytes_in = (h5_ceph_io_t)size;

        do {
            bytes_wrote = ceph_write( (file->fapl)->cmount, file->fd, buf,
                                      (loff_t)bytes_in, (loff_t)addr);
        } while(-1 == bytes_wrote && EINTR == errno);
        
        if(-1 == bytes_wrote) { /* error */
            int myerrno = errno;
            time_t mytime = HDtime(NULL);
            HDoff_t myoffset = ceph_lseek( (file->fapl)->cmount, file->fd, 
                                               (HDoff_t)0, SEEK_SET);

            HGOTO_ERROR(H5E_IO, H5E_WRITEERROR, FAIL, "file write failed: time = %s, filename = '%s', file descriptor = %d, errno = %d, error message = '%s', buf = %p, size = %lu, offset = %llu", HDctime(&mytime), file->filename, file->fd, myerrno, HDstrerror(myerrno), buf, (unsigned long)size, (unsigned long long)myoffset);
        } /* end if */
        
        HDassert(bytes_wrote > 0);
        HDassert((size_t)bytes_wrote <= size);

        size -= (size_t)bytes_wrote;
        addr += (haddr_t)bytes_wrote;
        buf = (const char *)buf + bytes_wrote;
    } /* end while */

    /* Update current position and eof */
    file->pos = addr;
    file->op = OP_WRITE;
    if(file->pos > file->eof)
        file->eof = file->pos;

done:
    if(ret_value < 0) {
        /* Reset last file I/O information */
        file->pos = HADDR_UNDEF;
        file->op = OP_UNKNOWN;
    } /* end if */

    FUNC_LEAVE_NOAPI(ret_value)
} /* end H5FD_ceph_write() */

static void *
H5FD_ceph_fapl_get(H5FD_t *_file)
{
  H5FD_ceph_t *file = (H5FD_ceph_t*)_file;
  void *ret_value;

  FUNC_ENTER_NOAPI(H5FD_ceph_fapl_get, NULL)

  ret_value=H5FD_ceph_fapl_copy(&(file->fapl));

done:
  FUNC_LEAVE_NOAPI(ret_value)
}

static void *
H5FD_ceph_fapl_copy(const void *_old_fa)
{
  const H5FD_ceph_fapl_t *old_fa = (const H5FD_ceph_fapl_t*)_old_fa;
  H5FD_ceph_fapl_t *new_fa = H5MM_malloc(sizeof(H5FD_ceph_fapl_t));
  void *ret_value;  // return value

  FUNC_ENTER_NOAPI(H5FD_ceph_fapl_copy, NULL)

  assert(new_fa);

  HDmemcpy(new_fa, old_fa, sizeof(H5FD_ceph_fapl_t));

  ret_value=new_fa;

done:
  FUNC_LEAVE_NOAPI(ret_value)
}

/*-------------------------------------------------------------------------
 * Function:	H5FD_ceph_truncate
 *
 * Purpose:	Makes sure that the true file size is the same (or larger)
 *		than the end-of-address.
 *
 * Return:	Success:	Non-negative
 *		Failure:	Negative
 *
 * Programmer:	Robb Matzke
 *              Wednesday, August  4, 1999
 *
 *-------------------------------------------------------------------------
 */
/* ARGSUSED */
static herr_t
H5FD_ceph_truncate(H5FD_t *_file, hid_t UNUSED dxpl_id, hbool_t UNUSED closing)
{
    H5FD_ceph_t *file = (H5FD_ceph_t *)_file;
    herr_t ret_value = SUCCEED;                 /* Return value */

    FUNC_ENTER_NOAPI_NOINIT(H5FD_ceph_truncate)

    HDassert(file);

    /* Extend the file to make sure it's large enough */
    if(!H5F_addr_eq(file->eoa, file->eof)) {
#ifdef H5_HAVE_WIN32_API
        LARGE_INTEGER   li;         /* 64-bit (union) integer for SetFilePointer() call */
        DWORD           dwPtrLow;   /* Low-order pointer bits from SetFilePointer()
                                     * Only used as an error code here.
                                     */
        DWORD           dwError;    /* DWORD error code from GetLastError() */
        BOOL            bError;     /* Boolean error flag */

        /* Windows uses this odd QuadPart union for 32/64-bit portability */
        li.QuadPart = (__int64)file->eoa;

        /* Extend the file to make sure it's large enough.
         *
         * Since INVALID_SET_FILE_POINTER can technically be a valid return value
         * from SetFilePointer(), we also need to check GetLastError().
         */
        dwPtrLow = SetFilePointer(file->hFile, li.LowPart, &li.HighPart, FILE_BEGIN);
        if(INVALID_SET_FILE_POINTER == dwPtrLow) {
            dwError = GetLastError();
            if(dwError != NO_ERROR )
                HGOTO_ERROR(H5E_FILE, H5E_FILEOPEN, FAIL, "unable to set file pointer")
        }

        bError = SetEndOfFile(file->hFile);
        if(0 == bError)
            HGOTO_ERROR(H5E_IO, H5E_SEEKERROR, FAIL, "unable to extend file properly")
#else /* H5_HAVE_WIN32_API */
#ifdef H5_VMS
        /* Reset seek offset to the beginning of the file, so that the file isn't
         * re-extended later.  This may happen on Open VMS. */
        if(-1 == HDlseek(file->fd, (HDoff_t)0, SEEK_SET))
            HSYS_GOTO_ERROR(H5E_IO, H5E_SEEKERROR, FAIL, "unable to seek to proper position")
#endif
        if(-1 == HDftruncate(file->fd, (HDoff_t)file->eoa))
            HSYS_GOTO_ERROR(H5E_IO, H5E_SEEKERROR, FAIL, "unable to extend file properly")
#endif /* H5_HAVE_WIN32_API */

        /* Update the eof value */
        file->eof = file->eoa;

        /* Reset last file I/O information */
        file->pos = HADDR_UNDEF;
        file->op = OP_UNKNOWN;
    } /* end if */

done:
    FUNC_LEAVE_NOAPI(ret_value)
} /* end H5FD_ceph_truncate() */

