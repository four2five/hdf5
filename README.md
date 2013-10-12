hdf5
====

Both the C (1.8.8) and Java (2.8) branches of HDF5 along with a little test code

The C code is in hdf5_C and the Java code is in hdf5_java.

I like to put all of the export commands in my .bashrc file so that they're loaded automatically when I log in.

Building HDF5C
====

1. HDF5 Java needs some external libraries and they need to be compiled into the Hdf5 C library, so let's start with those. Note that the desired installation directory (specified by '--prefix' should be changed to wherever you would like the binaries installed.
    1. Download and untar the tarball found here: http://www.hdfgroup.org/ftp/lib-external/zlib/
    2. `cd` into the untarred directory and configure like so: `CFLAGS="-fPIC -D_FILE_OFFSET_BITS=64" ./configure --prefix=/home/buck/install/zlib`
    3. `make` `make check` `make install`
    4. Download and untar the tarball found here: http://www.hdfgroup.org/ftp/lib-external/szip/2.1/src/
    5. `cd` into the untarred directory and configure it like so: `CFLAGS="-fPIC -D_FILE_OFFSET_BITS=64" ./configure --prefix=/home/buck/install/zlib`
    6. `make` `make check` `make install`
2. Change directories into the hdf5_C directory     
    1. `CFLAGS="-O0 -fPIC -D_FILE_OFFSET_BITS=64" ./configure --prefix=/home/buck/install/hdf5 --with-zlib=/home/buck/install/zlib/include,/home/buck/install/zlib/lib --with-szlib=/home/buck/install/szip/include,/home/buck/install/szip/lib --disable-shared --enable-filters=all`    
    2. `make` `make check` `make install`
    3. export HDF5_HOME=/home/buck/install/hdf5
    4. export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$HDF5_HOME/lib
    5. export PATH=$PATH:$HDF5_HOME/bin
3. Change into the hdf5_Java directory
    1. Edit the runconfig-example.sh script to point at your installation dir (INSTDIR), java installation (JAVAINC, JAVALIB), hdf5 install (HDF5), GZIP install (GZIP) and SZIP install (SZIP) which you specified in the respective configure commands above
    2. Edit the 'configure' invocation in the runconfig-example.sh script to disable hdf4 (mine looks like so): CC='gcc' CFLAGS='-fPIC  -D_FILE_OFFSET_BITS=64' ./configure --prefix=$INSTDIR --with-jdk=$JAVAINC,$JAVALIB --with-hdf5=$HDF5/include,$HDF5/lib --with-libz=$GZIP/include,$GZIP/lib --without-hdf4 --with-libsz=$SZIP/include,$SZIP/lib 
    3.  `make`, `make check`, `make install`
