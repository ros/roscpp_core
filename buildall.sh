#!/bin/sh -ex

TOP=$(cd dirname $0 ; pwd)

INSTDIR=$TOP/inst
rm -rf $INSTDIR
BUILDDIR=$TOP/build
rm -rf $BUILDDIR
rm -f *.build *.deb *.changes

echo "INSTDIR=$INSTDIR"
# INSTDIR=/tmp/ros/electric

CMAKE="cmake -DCMAKE_INSTALL_PREFIX=$INSTDIR -DCMAKE_PREFIX_PATH=$TOP/cmake"

rm -rf $TOP/build

PACKAGES="ros_cmake foo bar snake simpleinstall"
for l in $PACKAGES
do
    mkdir -p $BUILDDIR/$l
    cd $BUILDDIR/$l
    $CMAKE $TOP/$l
    make VERBOSE=1
    make VERBOSE=1 install
    
    if [ -d $TOP/$l/debian ] ; then
        cd $TOP/$l
        debuild -i -uc -us -b
    fi
done

# ls -ltR $INSTDIR

export PYTHONPATH=$INSTDIR/lib/python2.6/site-packages
python -c 'import snake ; print dir(snake)'

# ssh://vcs@kforge.ros.org/rosrelease/gencpp
# ssh://vcs@kforge.ros.org/rosrelease/genmsg
# ssh://vcs@kforge.ros.org/rosrelease/genpy


# simpleinstall binary only
# debuild -i -us -uc -b

# dpkg --contents something_x.x.x.deb

