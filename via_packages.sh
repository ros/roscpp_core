#!/bin/sh -ex

TOP=$(cd `dirname $0` ; pwd)

cd $TOP
git clean -fdx
$(cd $TOP/genmsg ; git clean -fdx)
$(cd $TOP/gencpp ; git clean -fdx)

INSTDIR=$TOP/inst
rm -rf $INSTDIR
BUILDDIR=$TOP/build
rm -rf $BUILDDIR
rm -f *.build *.deb *.changes

#CMAKE="cmake -DCMAKE_INSTALL_PREFIX=$INSTDIR -DCMAKE_PREFIX_PATH=$TOP/cmake"
CMAKE="cmake"
PPA="ppa:straszheim/ros"

mkdir -p PKGS
export DEB_DESTDIR=$TOP/PKGS
export CMAKE_INSTALL_PREFIX=$TOP/INSTALLY
export DEB_BUILD_DIR_PFX=$TOP/DEBBUILD

function dodir {
    rm -f ${2}_*.*.* /tmp/pkg/*
    cd $1
    dh_clean -v
    debuild \
        -e DH_VERBOSE=1 \
        -e DH_OPTIONS="-v -P$TOP/$1/pkg_tmpdir" \
        -e DEB_SOURCE_DIR=`pwd` \
        -e DEB_BUILD_DIR=$DEB_BUILD_DIR_PFX/$1 \
        -e DEB_DEBS_DIR=$TOP/debs
    #dpkg-buildpackage -tc # --changes-option=-u/tmp/pkg #--source-option=-VPackage=MOOKAH -v9.9.9
    #dpkg-buildpackage
    # dh_clean -v
    cd ..
    sudo dpkg -i $2*.deb
}

#dodir rosbuild rosbuild
#dodir foo foo
dodir bar bar
#dodir genmsg ros-fuerte-genmsg
#dodir gencpp ros-fuerte-gencpp
#dodir std_msgs ros-std-msgs

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
    dpkg-buildpackage -tc --source-option=-VPackage=MOOKAH -v9.9.9 # --changes-option=-u$(DEB_DESTDIR)
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

