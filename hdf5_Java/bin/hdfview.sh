#!/bin/sh

# Set up default variable values if not supplied by the user.

# where the HDFView is installed, e.g. /home/user1/hdfview
HDFJAVA=/home/buck/install/hdf5-java
export HDFJAVA

# where Java is installed (requires jdk1.4.x or above), e.g. /usr/jdk1.4.2/bin
JAVAHOME=/usr/lib/jvm/java-7-oracle/bin
export JAVAHOME

###############################################################################
#            DO NOT MODIFY BELOW THIS LINE
###############################################################################

CPATH=$HDFJAVA"/lib/jhdf.jar:"$HDFJAVA"/lib/jhdf5.jar:"$HDFJAVA"/lib/jhdfobj.jar"
CPATH=$CPATH":"$HDFJAVA"/lib/netcdf.jar:"$HDFJAVA"/lib/fits.jar:"$HDFJAVA"/lib/h5srb.jar"
CPATH=$CPATH":"$HDFJAVA"/lib/jhdf4obj.jar:"$HDFJAVA"/lib/jhdf5obj.jar:"$HDFJAVA"/lib/jhdfview.jar"
CPATH=$CPATH":"$HDFJAVA"/lib/jgraph.jar:"$HDFJAVA"/lib/ext/*"

TEST=/usr/bin/test
if [ ! -x /usr/bin/test ] 
then
TEST=`which test`
fi

if [ ! -d $JAVAHOME ]; then
    JAVALOC=`which java`
    LASTSLASH=`perl -e "print rindex(\"${JAVALOC}\", '/')"`
    JAVAHOME=`perl -e "print substr(\"${JAVALOC}\", 0, $LASTSLASH)"`
fi

if $TEST -z "$CLASSPATH"; then
	CLASSPATH=""
fi
CLASSPATH=$CPATH":"$CLASSPATH
export CLASSPATH

if $TEST -n "$JAVAHOME" ; then
	PATH=$JAVAHOME":"$PATH
	export PATH
fi


if $TEST -e /bin/uname; then
   os_name=`/bin/uname -s`
elif $TEST -e /usr/bin/uname; then
   os_name=`/usr/bin/uname -s`
else
   os_name=unknown
fi

if $TEST -z "$LD_LIBRARY_PATH" ; then
        LD_LIBRARY_PATH=""
fi

case  $os_name in
    SunOS)
	LD_LIBRARY_PATH=$HDFJAVA/lib/solaris:$HDFJAVA/lib/ext:$LD_LIBRARY_PATH
	;;
    Linux)
        LD_LIBRARY_PATH=$HDFJAVA"/lib/linux:"$HDFJAVA"/lib/ext:"$LD_LIBRARY_PATH
	;;
    IRIX*)
	OSREV=`/bin/uname -r`
	LD_LIBRARY_PATH=$HDFJAVA"/lib/irix-6.5:"$HDFJAVA"/lib/ext:"$LD_LIBRARY_PATH 
	LD_LIBRARYN32_PATH=$HDFJAVA"/lib/irix-6.5:"$HDFJAVA"/lib/ext":$LD_LIBRARY_PATH
	export LD_LIBRARYN32_PATH
	;;
    OSF1)
	LD_LIBRARY_PATH=$HDFJAVA"/lib/alpha:"$HDFJAVA"/lib/ext:"$LD_LIBRARY_PATH
	;;
    AIX)
	LD_LIBRARY_PATH=$HDFJAVA"/lib/aix:"$HDFJAVA"/lib/ext:"$LD_LIBRARY_PATH
	;;
    Darwin)
	DYLD_LIBRARY_PATH=$HDFJAVA"/lib/macosx:"$HDFJAVA"/lib/ext:"$DYLD_LIBRARY_PATH
	export DYLD_LIBRARY_PATH
	LD_LIBRARY_PATH=$DYLD_LIBRARY_PATH
	;;
    FreeBSD)
	LD_LIBRARY_PATH=$HDFJAVA"/lib/freebsd:"$HDFJAVA"/lib/ext:"$LD_LIBRARY_PATH
	;;
    *)
	echo "Unknown Operating System:  HDFView may not work correctly"
        ;;
esac

export LD_LIBRARY_PATH

$JAVAHOME/java  -Djava.library.path=$LD_LIBRARY_PATH ncsa.hdf.view.HDFView -root $HDFJAVA $*
