#!/bin/sh -ex

TOP=$(cd dirname $0 ; pwd)

INSTDIR=$TOP/inst
echo "INSTDIR=$INSTDIR"
# INSTDIR=/tmp/ros/electric

CMAKE="cmake -DCMAKE_INSTALL_PREFIX=$INSTDIR"

rm -rf $TOP/build

for l in foo
do
    mkdir -p $TOP/build/$l
    cd $TOP/build/$l
    $CMAKE $TOP/$l
    make
    make install
done