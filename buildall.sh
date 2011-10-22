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

PACKAGES="wg-cmake-helpers foo bar snake"

for l in $PACKAGES
do
    mkdir -p $BUILDDIR/$l
    cd $BUILDDIR/$l
    $CMAKE $TOP/$l
    make VERBOSE=1
    make install
done
