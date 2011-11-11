#!/bin/sh -ex

PROTONAME=ros-fuerte-roscpp-core-prototype
sudo apt-get install -y python-empy checkinstall wget
sudo apt-get purge -y $PROTONAME || /bin/true
rm -f proto.rosinstall
wget https://raw.github.com/straszheim/roscpp_core/master/etc/proto.rosinstall

rosinstall -n src proto.rosinstall
[ -h src/CMakeLists.txt ] || ln -s catkin/toplevel.cmake src/CMakeLists.txt

[ -d build ] || mkdir build
cd build
cmake ../src -DCMAKE_INSTALL_PREFIX=/opt/ros/fuerte
make
sudo checkinstall -y --install=no --nodoc --pkgname $PROTONAME make install

if [ $(uname -m) = "x86_64" ] ; then
    ARCH=amd64
else
    ARCH=$(uname -m)
fi
# if you are me
scp ${PROTONAME}_*.deb bsq.willowgarage.com:public_html/files/${PROTONAME}_$(lsb_release -sc)_$ARCH.deb





