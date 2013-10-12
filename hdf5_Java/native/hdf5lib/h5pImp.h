/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class ncsa_hdf_hdf5lib_H5_H5_H5P */

#ifndef _Included_ncsa_hdf_hdf5lib_H5_H5P
#define _Included_ncsa_hdf_hdf5lib_H5_H5P
#ifdef __cplusplus
extern "C" {
#endif
    
    extern JavaVM *jvm;
    extern jobject visit_callback;   

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pall_filters_avail
     * Signature: (I)Z
     */
    JNIEXPORT jboolean JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pall_1filters_1avail
      (JNIEnv *env, jclass clss, jint dcpl_id);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pclose
     * Signature: (I)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5__1H5Pclose
      (JNIEnv *env, jclass clss, jint plist);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pclose_list
     * Signature: (I)I   
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pclose_1class
      (JNIEnv *env, jclass clss, jint plid);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pcopy
     * Signature: (I)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5__1H5Pcopy
      (JNIEnv *env, jclass clss, jint plist);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pcopy_prop
     * Signature: (IILjava/lang/String;)I 
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pcopy_1prop
      (JNIEnv *env, jclass clss, jint dst_plid, jint src_plid, jstring name);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pcreate
     * Signature: (I)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5__1H5Pcreate
      (JNIEnv *env, jclass clss, jint type);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pequal
     * Signature: (II)I    
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pequal
      (JNIEnv *env, jclass clss, jint plid1, jint plid2);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pexist
     * Signature: (ILjava/lang/String;)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pexist
      (JNIEnv *env, jclass clss, jint plid, jstring name);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pfill_value_defined
     * Signature: (I[I)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pfill_1value_1defined
      (JNIEnv *env, jclass clss, jint plist, jintArray status);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pget
     * Signature: (ILjava/lang/String;)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pget
      (JNIEnv *env, jclass clss, jint plid, jstring name);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pget_alignment
     * Signature: (I[J)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pget_1alignment
      (JNIEnv *env, jclass clss, jint plist, jlongArray alignment);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pget_alloc_time
     * Signature: (I[I)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pget_1alloc_1time
      (JNIEnv *env, jclass clss, jint plist, jintArray alloc_time);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pget_attr_creation_order
     * Signature: (I)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pget_1attr_1creation_1order
      (JNIEnv *env, jclass clss, jint ocpl_id);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pget_attr_phase_change
     * Signature: (I[I)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pget_1attr_1phase_1change
      (JNIEnv *env, jclass clss, jint ocpl_id, jintArray attributes);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pget_btree_ratios
     * Signature: (I[D[D[D)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pget_1btree_1ratios
      (JNIEnv *env, jclass clss, jint plist_id, jdoubleArray left, jdoubleArray middle, jdoubleArray right);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pget_buffer
     * Signature: (I[B[B)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pget_1buffer
      (JNIEnv *env, jclass clss, jint plist, jbyteArray tconv, jbyteArray bkg);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pget_buffer_size
     * Signature: (I)J
     */
    JNIEXPORT jlong JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pget_1buffer_1size
      (JNIEnv *env, jclass clss, jint plist);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pget_cache
     * Signature: (I[I[J[J[D)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pget_1cache
      (JNIEnv *env, jclass clss, jint plist, jintArray mdc_nelmts,
      jlongArray rdcc_nelmts, jlongArray rdcc_nbytes, jdoubleArray rdcc_w0);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pget_char_encoding
     * Signature: (I)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pget_1char_1encoding
      (JNIEnv *env, jclass clss, jint acpl);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pget_chunk
     * Signature: (II[J)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pget_1chunk
      (JNIEnv *env, jclass clss, jint plist, jint max_ndims, jlongArray dims);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pget_chunk_cache
     * Signature: (I[J[J[D)V
     */
    JNIEXPORT void JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pget_1chunk_1cache
      (JNIEnv *env, jclass clss, jint dapl, jlongArray rdcc_nslots, 
              jlongArray rdcc_nbytes, jdoubleArray rdcc_w0);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pget_class
     * Signature: (I)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pget_1class
      (JNIEnv *env, jclass clss, jint plist);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pget_class_name
     * Signature: (I)Ljava/lang/String; 
     */
    JNIEXPORT jstring JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pget_1class_1name
      (JNIEnv *env, jclass clss, jint plid);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pget_class_parent
     * Signature: (I)I   
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pget_1class_1parent
      (JNIEnv *env, jclass clss, jint plid);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pget_copy_object
     * Signature: (I)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pget_1copy_1object
      (JNIEnv *env, jclass clss, jint ocp_plist_id);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pget_create_intermediate_group
     * Signature: (I)Z
     */
    JNIEXPORT jboolean JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pget_1create_1intermediate_1group
      (JNIEnv *env, jclass clss, jint lcpl_id);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pget_data_transform
     * Signature: (I[Ljava/lang/String;J)J
     */
    JNIEXPORT jlong JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pget_1data_1transform
      (JNIEnv *env, jclass clss, jint plist_id, jobjectArray expression, jlong size);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pget_driver
     * Signature: (I)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pget_1driver
      (JNIEnv *env, jclass clss, jint plist);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pget_dxpl_multi
     * Signature: (I[I)V
     */
    JNIEXPORT void JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pget_1dxpl_1multi
      (JNIEnv *env, jclass clss, jint tid, jintArray dxpl_id);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pget_edc_check
     * Signature: (I)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pget_1edc_1check
      (JNIEnv *env, jclass clss, jint plist);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pget_elink_acc_flags
     * Signature: (I)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pget_1elink_1acc_1flags
      (JNIEnv *env, jclass clss, jint lapl_id);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    _H5Pget_elink_fapl
     * Signature: (I)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5__1H5Pget_1elink_1fapl
      (JNIEnv *env, jclass clss, jint lapl_id);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pget_elink_file_cache_size
     * Signature: (I)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pget_1elink_1file_1cache_1size
      (JNIEnv *env, jclass clss, jint plist);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pget_elink_prefix
     * Signature: (I[Ljava/lang/String;)J
     */
    JNIEXPORT jlong JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pget_1elink_1prefix
      (JNIEnv *env, jclass clss, jint lapl_id, jobjectArray prefix);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pget_est_link_info
     * Signature: (I[I)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pget_1est_1link_1info
      (JNIEnv *env, jclass clss, jint gcpl_id, jintArray link_info);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pget_external
     * Signature: (IIJ[Ljava/lang/String;[J)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pget_1external
      (JNIEnv *env, jclass clss, jint plist, jint idx, jlong name_size,
      jobjectArray name, jlongArray size);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pget_external_count
     * Signature: (I)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pget_1external_1count
      (JNIEnv *env, jclass clss, jint plist);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pget_family_offset
     * Signature: (I)J
     */
    JNIEXPORT jlong JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pget_1family_1offset
      (JNIEnv *env, jclass clss, jint fapl_id);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pget_fapl_core
     * Signature: (I[J[Z)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pget_1fapl_1core
      (JNIEnv *env, jclass clss, jint fapl_id, jlongArray increment, jbooleanArray backing_store);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pget_fapl_direct
     * Signature: (I[J)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pget_1fapl_1direct
     (JNIEnv *env, jclass clss, jint fapl_id, jlongArray info);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pget_fapl_family
     * Signature: (I[J[I)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pget_1fapl_1family
      (JNIEnv *env, jclass clss, jint tid, jlongArray memb_size, jintArray memb_plist);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pget_fapl_muti
     * Signature: (I[I[I[Ljava/lang/String;[J)Z
     */
    JNIEXPORT jboolean JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pget_1fapl_1multi
      (JNIEnv *env, jclass clss, jint tid, jintArray memb_map, jintArray memb_fapl, jobjectArray memb_name, jlongArray memb_addr);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pget_fclose_degree
     * Signature: (I)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pget_1fclose_1degree
      (JNIEnv *env, jclass clss, jint plist);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pget_fill_time
     * Signature: (I[I)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pget_1fill_1time
      (JNIEnv *env, jclass clss, jint plist, jintArray fill_time);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pget_fill_value
     * Signature: (II[B)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pget_1fill_1value
      (JNIEnv *env, jclass clss, jint plist_id, jint type_id, jbyteArray value);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pget_filter
     * Signature: (II[I[J[IJ[Ljava/lang/String;)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pget_1filter
      (JNIEnv *env, jclass clss, jint plist, jint filter_number, jintArray flags,
      jlongArray cd_nelmts, jintArray cd_values, jlong namelen, jobjectArray name);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pget_filter2
     * Signature: (II[I[J[IJ[Ljava/lang/String;[I)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pget_1filter2
      (JNIEnv *env, jclass clss, jint plist, jint filter_number, jintArray flags,
      jlongArray cd_nelmts, jintArray cd_values, jlong namelen, jobjectArray name, 
      jintArray filter_config);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pget_filter_by_id
     * Signature: (II[I[J[IJ[Ljava/lang/String;)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pget_1filter_1by_1id
      (JNIEnv *env, jclass clss, jint plist, jint filter, jintArray flags,
      jlongArray cd_nelmts, jintArray cd_values, jlong namelen, jobjectArray name);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pget_filter_by_id2
     * Signature: (II[I[J[IJ[Ljava/lang/String;[I)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pget_1filter_1by_1id2
      (JNIEnv *env, jclass clss, jint plist, jint filter, jintArray flags,
      jlongArray cd_nelmts, jintArray cd_values, jlong namelen, jobjectArray name, jintArray filter_config);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pget_gc_references
     * Signature: (I[Z)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pget_1gc_1references
      (JNIEnv *env, jclass clss, jint fapl_id, jbooleanArray gc_ref);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pget_gcreferences
     * Signature: (I)Z
     */
    JNIEXPORT jboolean JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pget_1gcreferences
      (JNIEnv *env, jclass clss, jint fapl_id);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pget_hyper_vector_size
     * Signature: (I[J)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pget_1hyper_1vector_1size
      (JNIEnv *env, jclass clss, jint plist, jlongArray vector_size);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pget_istore_k
     * Signature: (I[I)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pget_1istore_1k
      (JNIEnv *env, jclass clss, jint plist, jintArray ik);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pget_layout
     * Signature: (I)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pget_1layout
      (JNIEnv *env, jclass clss, jint plist);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pget_libver_bounds
     * Signature: (I[I)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pget_1libver_1bounds
      (JNIEnv *env, jclass clss, jint fapl_id, jintArray libver);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pget_link_creation_order
     * Signature: (I)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pget_1link_1creation_1order
      (JNIEnv *env, jclass clss, jint gcpl_id);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pget_link_phase_change
     * Signature: (I[I)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pget_1link_1phase_1change
      (JNIEnv *env, jclass clss, jint gcpl_id, jintArray links);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pget_local_heap_size_hint
     * Signature: (I)J
     */
    JNIEXPORT jlong JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pget_1local_1heap_1size_1hint
      (JNIEnv *env, jclass clss, jint gcpl_id);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pget_mdc_config
     * Signature: (I)Lncsa/hdf/hdf5lib/structs/H5AC_cache_config_t;
     */
    JNIEXPORT jobject JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pget_1mdc_1config
      (JNIEnv *env, jclass clss, jint plist);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pget_meta_block_size
     * Signature: (I)J
     */
    JNIEXPORT jlong JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pget_1meta_1block_1size
      (JNIEnv *env, jclass clss, jint plist);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pget_nfilters
     * Signature: (I)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pget_1nfilters
      (JNIEnv *env, jclass clss, jint plist);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pget_nlinks
     * Signature: (I)J
     */
    JNIEXPORT jlong JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pget_1nlinks
      (JNIEnv *env, jclass clss, jint lapl_id);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pget_nprops
     * Signature: (I)J  
     */
    JNIEXPORT jlong JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pget_1nprops
      (JNIEnv *env, jclass clss, jint plid);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pget_obj_track_times
     * Signature: (I)Z  
     */
    JNIEXPORT jboolean JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pget_1obj_1track_1times
      (JNIEnv *env, jclass clss, jint objplid);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pget_preserve
     * Signature: (I)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pget_1preserve
      (JNIEnv *env, jclass clss, jint plist);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pget_sieve_buf_size
     * Signature: (I)J
     */
    JNIEXPORT jlong JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pget_1sieve_1buf_1size
      (JNIEnv *env, jclass clss, jint plist);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pget_shared_mesg_index
     * Signature: (II[I)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pget_1shared_1mesg_1index
      (JNIEnv *env, jclass clss, jint fcpl_id, jint index_num, jintArray mesg_info);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pget_shared_mesg_nindexes
     * Signature: (I)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pget_1shared_1mesg_1nindexes
      (JNIEnv *env, jclass clss, jint fcpl_id);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pget_shared_mesg_phase_change
     * Signature: (I[I)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pget_1shared_1mesg_1phase_1change
      (JNIEnv *env, jclass clss, jint fcpl_id, jintArray size);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pget_size
     * Signature: (ILjava/lang/String;)J 
     */
    JNIEXPORT jlong JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pget_1size
      (JNIEnv *env, jclass clss, jint plid, jstring name);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pget_sizes
     * Signature: (I[J)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pget_1sizes
      (JNIEnv *env, jclass clss, jint plist, jlongArray size);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pget_small_data_block_size
     * Signature: (I[J)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pget_1small_1data_1block_1size
      (JNIEnv *env, jclass clss, jint plist, jlongArray size);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pget_small_data_block_size_long
     * Signature: (I)J
     */
    JNIEXPORT jlong JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pget_1small_1data_1block_1size_1long
      (JNIEnv *env, jclass clss, jint plist);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pget_sym_k
     * Signature: (I[I)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pget_1sym_1k
      (JNIEnv *env, jclass clss, jint plist, jintArray size);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pget_userblock
     * Signature: (I[J)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pget_1userblock
      (JNIEnv *env, jclass clss, jint plist, jlongArray size);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pget_version
     * Signature: (I[I)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pget_1version
      (JNIEnv *env, jclass clss, jint plist, jintArray version_info);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pisa_class
     * Signature: (II)I    
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pisa_1class
      (JNIEnv *env, jclass clss, jint plid, jint pcls);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pmodify_filter
     * Signature: (IIIJ[I)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pmodify_1filter
      (JNIEnv *env, jclass clss, jint plist, jint filter, jint flags,
      jlong cd_nelmts, jintArray cd_values);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Premove
     * Signature: (ILjava/lang/String;)I 
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Premove
      (JNIEnv *env, jclass clss, jint plid, jstring name);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Premove_filter
     * Signature: (II)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5P1remove_1filter
      (JNIEnv *env, jclass clss, jint obj_id, jint filter);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pset
     * Signature: (ILjava/lang/String;I)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pset
      (JNIEnv *env, jclass clss, jint plid, jstring name, jint val);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pset_alignment
     * Signature: (IJJ)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pset_1alignment
      (JNIEnv *env, jclass clss, jint plist, jlong threshold, jlong alignment);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pset_alloc_time
     * Signature: (II)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pset_1alloc_1time
      (JNIEnv *env, jclass clss, jint plist, jint alloc_time);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pset_attr_creation_order
     * Signature: (II)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pset_1attr_1creation_1order
      (JNIEnv *env, jclass clss, jint ocpl_id, jint crt_order_flags);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pset_btree_ratios
     * Signature: (IDDD)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pset_1btree_1ratios
      (JNIEnv *env, jclass clss, jint plist_id, jdouble left, jdouble middle, jdouble right);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pset_buffer
     * Signature: (IJ[B[B)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pset_1buffer
      (JNIEnv *env, jclass clss, jint plist, jlong size, jbyteArray tconv, jbyteArray bkg);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pset_buffer_size
     * Signature: (IJ)V
     */
    JNIEXPORT void JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pset_1buffer_1size
      (JNIEnv *env, jclass clss, jint plist, jlong size);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pset_cache
     * Signature: (IIJJD)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pset_1cache
      (JNIEnv *env, jclass clss, jint plist, jint mdc_nelmts, jlong rdcc_nelmts,
      jlong rdcc_nbytes, jdouble rdcc_w0);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pset_char_encoding
     * Signature: (II)V
     */
    JNIEXPORT void JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pset_1char_1encoding
      (JNIEnv *env, jclass clss, jint acpl, jint encoding);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pset_chunk
     * Signature: (II[B)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pset_1chunk
      (JNIEnv *env, jclass clss, jint plist, jint ndims, jbyteArray dim);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pset_chunk_cache
     * Signature: (IJJD)V
     */
    JNIEXPORT void JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pset_1chunk_1cache
      (JNIEnv *env, jclass clss, jint dapl, jlong rdcc_nslots,
      jlong rdcc_nbytes, jdouble rdcc_w0);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pset_copy_object
     * Signature: (II)V
     */
    JNIEXPORT void JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pset_1copy_1object
      (JNIEnv *env, jclass clss, jint ocp_plist_id, jint copy_options);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pset_create_intermediate_group
     * Signature: (IZ)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pset_1create_1intermediate_1group
      (JNIEnv *env, jclass clss, jint lcpl_id, jboolean crt_intermed_group);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pset_data_transform
     * Signature: (ILjava/lang/String;)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pset_1data_1transform
      (JNIEnv *env, jclass clss, jint plist_id, jstring expression);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pset_deflate
     * Signature: (II)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pset_1deflate
      (JNIEnv *env, jclass clss, jint plist, jint level);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pset_dxpl_multi
     * Signature: (I[I)V
     */
    JNIEXPORT void JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pset_1dxpl_1multi
      (JNIEnv *env, jclass clss, jint tid, jintArray dxpl_id);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pset_edc_check
     * Signature: (II)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pset_1edc_1check
      (JNIEnv *env, jclass clss, jint plist, jint check);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pset_elink_acc_flags
     * Signature: (II)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pset_1elink_1acc_1flags
      (JNIEnv *env, jclass clss, jint lapl_id, jint flags);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pset_elink_fapl
     * Signature: (II)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pset_1elink_1fapl
      (JNIEnv *env, jclass clss, jint lapl_id, jint fapl_id);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pset_elink_file_cache_size
     * Signature: (II)V
     */
    JNIEXPORT void JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pset_1elink_1file_1cache_1size
      (JNIEnv *env, jclass clss, jint plist, jint size);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pset_elink_prefix
     * Signature: (ILjava/lang/String;)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pset_1elink_1prefix
      (JNIEnv *env, jclass clss, jint lapl_id, jstring prefix);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pset_est_link_info
     * Signature: (III)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pset_1est_1link_1info
      (JNIEnv *env, jclass clss, jint gcpl_id, jint est_num_entries, jint est_name_len);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pset_external
     * Signature: (ILjava/lang/String;JJ)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pset_1external
      (JNIEnv *env, jclass clss, jint plist, jstring name, jlong offset, jlong size);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pset_family_offset
     * Signature: (IJ)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pset_1family_1offset
      (JNIEnv *env, jclass clss, jint fapl_id, jlong offset);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pset_fapl_core
     * Signature: (IJZ)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pset_1fapl_1core
      (JNIEnv *env, jclass clss, jint fapl_id, jlong increment, jboolean backing_store);

    //JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pset_1fapl_1ceph
    //  (JNIEnv *env, jclass clss, jint fapl_id, jstring ceph_conf_path);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pset_fapl_direct
     * Signature: (IJJJ)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pset_1fapl_1direct
     (JNIEnv *env, jclass clss, jint fapl_id, jlong alignment, jlong block_size, jlong cbuf_size);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pset_fapl_family
     * Signature: (IJI)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pset_1fapl_1family
      (JNIEnv *env, jclass clss, jint plist, jlong memb_size, jint memb_plist);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pset_fapl_log
     * Signature: (ILjava/lang/String;JJ)V
     */
    JNIEXPORT void JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pset_1fapl_1log
      (JNIEnv *env, jclass clss, jint fapl_id, jstring logfile, jlong flags, jlong buf_size);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pset_fapl_muti
     * Signature: (I[I[I[Ljava/lang/String;[JZ)V
     */
    JNIEXPORT void JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pset_1fapl_1multi
      (JNIEnv *env, jclass clss, jint tid, jintArray memb_map, jintArray memb_fapl, jobjectArray memb_name, jlongArray memb_addr, jboolean relax);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pset_fapl_sec2
     * Signature: (I)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pset_1fapl_1sec2
      (JNIEnv *env, jclass clss, jint fapl_id);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pset_fapl_split
     * Signature: (ILjava/lang/String;ILjava/lang/String;I)V
     */
    JNIEXPORT void JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pset_1fapl_1split
      (JNIEnv *env, jclass clss, jint fapl_id, jstring metaext, jint meta_pl_id, jstring rawext, jint raw_pl_id);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pset_fapl_stdio
     * Signature: (I)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pset_1fapl_1stdio
      (JNIEnv *env, jclass clss, jint fapl_id);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pset_fapl_windows
     * Signature: (I)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pset_1fapl_1windows
      (JNIEnv *env, jclass clss, jint fapl_id);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pset_fclose_degree
     * Signature: (II)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pset_1fclose_1degree
      (JNIEnv *env, jclass clss, jint plist, jint fc_degree);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pset_fill_time
     * Signature: (II)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pset_1fill_1time
      (JNIEnv *env, jclass clss, jint plist, jint fill_time);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pset_fill_value
     * Signature: (II[B)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pset_1fill_1value
      (JNIEnv *env, jclass clss, jint plist_id, jint type_id, jbyteArray value);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pset_filter
     * Signature: (IIIJ[I)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pset_1filter
      (JNIEnv *env, jclass clss, jint plist, jint filter, jint flags,
      jlong cd_nelmts, jintArray cd_values);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pset_fletcher32
     * Signature: (I)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pset_1fletcher32
      (JNIEnv *env, jclass clss, jint plist);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pset_gc_references
     * Signature: (IZ)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pset_1gc_1references
      (JNIEnv *env, jclass clss, jint fapl_id, jboolean gc_ref);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pset_hyper_vector_size
     * Signature: (IJ)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pset_1hyper_1vector_1size
      (JNIEnv *env, jclass clss, jint plist, jlong vector_size);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pset_istore_k
     * Signature: (II)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pset_1istore_1k
      (JNIEnv *env, jclass clss, jint plist, jint ik);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pset_layout
     * Signature: (II)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pset_1layout
      (JNIEnv *env, jclass clss, jint plist, jint layout);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pset_libver_bounds
     * Signature: (III)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pset_1libver_1bounds
      (JNIEnv *env, jclass clss, jint fapl_id, jint low, jint high);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pset_link_creation_order
     * Signature: (II)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pset_1link_1creation_1order
      (JNIEnv *env, jclass clss, jint gcpl_id, jint crt_order_flags);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pset_link_phase_change
     * Signature: (III)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pset_1link_1phase_1change
      (JNIEnv *env, jclass clss, jint gcpl_id, jint max_compact, jint min_dense);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pset_local_heap_size_hint
     * Signature: (IJ)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pset_1local_1heap_1size_1hint
      (JNIEnv *env, jclass clss, jint gcpl_id, jlong size_hint);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pset_mdc_config
     * Signature: (ILncsa/hdf/hdf5lib/structs/H5AC_cache_config_t;)V
     */
    JNIEXPORT void JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pset_1mdc_1config
      (JNIEnv *env, jclass clss, jint plist, jobject cache_config);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pset_meta_block_size
     * Signature: (IJ)V
     */
    JNIEXPORT void JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pset_1meta_1block_1size
      (JNIEnv *env, jclass clss, jint fapl_id, jlong size);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pset_nbit
     * Signature: (I)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pset_1nbit
      (JNIEnv *env, jclass clss, jint plist_id);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pset_nlinks
     * Signature: (IJ)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pset_1nlinks
      (JNIEnv *env, jclass clss, jint lapl_id, jlong nlinks);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pset_obj_track_times
     * Signature: (IZ)V
     */
    JNIEXPORT void JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pset_1obj_1track_1times
      (JNIEnv *env, jclass clss, jint objplid, jboolean track_times);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pset_preserve
     * Signature: (IZ)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pset_1preserve
      (JNIEnv *env, jclass clss, jint plist, jboolean status);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pset_scaleoffset
     * Signature: (III)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pset_1scaleoffset
      (JNIEnv *env, jclass clss, jint plist_id, jint scale_type, jint scale_factor);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pset_sieve_buf_size
     * Signature: (IJ)V
     */
    JNIEXPORT void JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pset_1sieve_1buf_1size
      (JNIEnv *env, jclass clss, jint fapl_id, jlong size);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pset_shared_mesg_index
     * Signature: (IIII)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pset_1shared_1mesg_1index
      (JNIEnv *env, jclass clss, jint fcpl_id, jint index_num, jint mesg_type_flags, jint min_mesg_size);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pset_shared_mesg_nindexes
     * Signature: (II)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pset_1shared_1mesg_1nindexes
      (JNIEnv *env, jclass clss, jint plist_id, jint nindexes);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pset_shared_mesg_phase_change
     * Signature: (III)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pset_1shared_1mesg_1phase_1change
      (JNIEnv *env, jclass clss, jint fcpl_id, jint max_list, jint min_btree);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pset_shuffle
     * Signature: (I)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pset_1shuffle
      (JNIEnv *env, jclass clss, jint plist);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pset_sizes
     * Signature: (III)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pset_1sizes
      (JNIEnv *env, jclass clss, jint plist, jint sizeof_addr, jint sizeof_size);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pset_small_data_block_size
     * Signature: (IJ)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pset_1small_1data_1block_1size
      (JNIEnv *env, jclass clss, jint plist, jlong size);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pset_sym_k
     * Signature: (III)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pset_1sym_1k
      (JNIEnv *env, jclass clss, jint plist, jint ik, jint lk);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pset_szip
     * Signature: (III)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pset_1szip
      (JNIEnv *env, jclass clss, jint plist, jint options_mask, jint pixels_per_block);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Pset_userblock
     * Signature: (IJ)I
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Pset_1userblock
      (JNIEnv *env, jclass clss, jint plist, jlong size);

    /*
     * Class:     ncsa_hdf_hdf5lib_H5
     * Method:    H5Punregister
     * Signature: (ILjava/lang/String;)I  
     */
    JNIEXPORT jint JNICALL Java_ncsa_hdf_hdf5lib_H5_H5Punregister
      (JNIEnv *env, jclass clss, jint plid, jstring name);

#ifdef __cplusplus
}
#endif
#endif
