
SCRATCH
-------

evolving docs for new build stuff



workflow
--------

PREFIX will be /opt/ros/fuerte/  (thereunder, (include|lib|share)), but practice
with temp directories whereever.

cmake will find the packagename-config.cmake stuff via
CMAKE_PREFIX_PATH, which must contain the installdir above (see docs
for find_package)

for now, install python executable scripts to PREFIX/bin and library
code to PREFIX/lib/python and add PREFIX/lib/python to pythonpath
manually.

* ros_cmake is a package.  it has only cmake and python as
  dependencies.  it is the base of everything... common cmake
  infrastructure goes in there.  Maybe eventually it contains all the
  rosbuild2 cmake infrastructure.

  it is capable of e.g. finding all the lang packages listed in
  ROS_GENLANGS

  std_msgs calls generate_msg(${PROJECT_NAME} MESSAGES String.msg LANGS ${ROS_GENLANGS})
  so that packages can selectively enable/disable languages

* install genmsg, gencpp, genpy:
  * from debs -or-
  * from a checkout
  * ros_cmake should provide most of what you need
  * or they can be in your buildspace

* rosinstall file should set up the builds of all this
* rosdeps yaml files should be available for tracking dependencies (e.g. python-setuptools, cmake)

* use find_package(ros_gencpp ...) from my project which contains ros messages (quux_msgs)
  * this should work (for the user who only wants c++)
* use macros pulled in by this find_package to create message-building targets
* there are the lang-specific ones, and then then lang-generic ones that take a LANGS argument

lang-generic case:
------------------
find_package(genmsg)
generate_msgs(... LANGS ${ROS_GENLANGS}) <= comes from genmsg, uses LANGS argument to find available lanaguages

* generate code for these messages
* install this generated code in a normal cmakeish way (make install)
* in a different package (quux_user) use find_package(quux_msgs ...) to get the include paths for these messages
*  [ e.g. include_directories(${quux_msgs_INCLUDE_DIRS}) ]
* compile quux_user_chatter that creates and serializes a message from quux_msgs



debian pkgs
-----------

the 'standard' build will be parameterized on a list of languages ROS_GENLANGS=cpp;py;lua (for instance)
packages that contain messages will be dependent on genmsg and genX for x in ROS_GENLANGS

standard stack .debs will contain generated messages for langs in ROS_GENLANGS

optional packagess for other langs would be ros-DISTRO-STACK-LANG e.g. ros-fuerte-common-msgs-haskell.deb

scenarios
---------

one buildspace, with packages that generate cpp only, py only, both, and e.g. ${ROS_GENLANGS} + lua 
(can write a dummy lua generator for testing purposes)


open questions
==============

rosbuild2 currently makes .deb-per-package... not .deb-per-stack.  :(   

-debug and non-debug packages.

