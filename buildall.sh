#!/bin/sh -ex

TOP=$(cd dirname $0 ; pwd)

INSTDIR=$TOP/inst
rm -rf $INSTDIR
BUILDDIR=$TOP/build
rm -rf $BUILDDIR
echo "INSTDIR=$INSTDIR"
# INSTDIR=/tmp/ros/electric

CMAKE="cmake -DCMAKE_INSTALL_PREFIX=$INSTDIR -DCMAKE_PREFIX_PATH=$TOP/cmake"

rm -rf $TOP/build

PACKAGES="ros_cmake foo bar snake"

for l in $PACKAGES
do
    mkdir -p $BUILDDIR/$l
    cd $BUILDDIR/$l
    $CMAKE $TOP/$l
    make VERBOSE=1
    make VERBOSE=1 install
done

ls -ltR $INSTDIR

# ssh://vcs@kforge.ros.org/rosrelease/gencpp
# ssh://vcs@kforge.ros.org/rosrelease/genmsg
# ssh://vcs@kforge.ros.org/rosrelease/genpy
