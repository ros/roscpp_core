#!/bin/sh -ex

TOP=$(cd `dirname $0` ; pwd)

INSTDIR=$TOP/inst
rm -rf $INSTDIR
BUILDDIR=$TOP/build
rm -rf $BUILDDIR
rm -f *.build *.deb *.changes

#CMAKE="cmake -DCMAKE_INSTALL_PREFIX=$INSTDIR -DCMAKE_PREFIX_PATH=$TOP/cmake"
CMAKE="cmake"
PPA="ppa:straszheim/ros"

function dodir {
    rm -f $1*.deb
    cd $1
    dpkg-buildpackage
    dh_clean -v
    cd ..
    sudo dpkg -i $1*.deb
}

dodir rosbuild
dodir foo
dodir bar

exit
rm -f rosbuild*.deb
cd rosbuild
dpkg-buildpackage
cd ..
sudo dpkg -i rosbuild*.deb

rm -f foo*.deb
cd foo
dpkg-buildpackage
cd ..

exit

rm -rf $TOP/build

PACKAGES="rosbuild foo bar" #  simpleinstall" #bar snake simpleinstall quux_msgs quux_user"

#
#  Local test
#
cd $TOP
for p in $PACKAGES
do
    echo $p
    rm -f ${p}_?.?.*_*.deb
    rm -f ${p}_?.?.*_*.upload
    pushd $TOP/$p
    dpkg-buildpackage
    popd
    sudo dpkg -i ${p}_?.?.*_*.deb
    dput ppa:straszheim/ros $p*_source.changes
done

exit
# for p in $PACKAGES
# do
#     echo $p
#     cd $TOP
#     rm $p_?.?.?.*
#     cd $BUILDDIR/$p
#     $CMAKE $TOP/$l
#     make
#     make install
#
#     if [ -d $TOP/$l/debian ] ; then
#         pushd $TOP/$l
#         debuild -S
#         popd
#         dput ppa:straszheim/ros $i*_source.changes
#     fi
# done


# ls -ltR $INSTDIR

export PYTHONPATH=$INSTDIR/lib/python2.6/site-packages
python -c 'import snake ; print dir(snake)'

# ssh://vcs@kforge.ros.org/rosrelease/gencpp
# ssh://vcs@kforge.ros.org/rosrelease/genmsg
# ssh://vcs@kforge.ros.org/rosrelease/genpy


# simpleinstall binary only
# debuild -i -us -uc -b

# dpkg --contents something_x.x.x.deb

