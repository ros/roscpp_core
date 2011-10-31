
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

Dependency types
----------------

Times when you have to think about dependencies:

* Making debian source packages ``.dsc``

  * These are actually pretty light, (basically just ``debuild -S``
    but if we are going to automate some of this, there will be
    extras).  

* Making debian binary packages ``.deb``

  * Everything you build against must be listedn in ``Build-Depends``
    in control file and (therefore) also installable via dpkg.

* Building

  TWO STEPS:  configure (cmake) time, and make time.

  * Everything you build against/with (important distinction:
    "against" implies that it is installed, "with" implies that it is
    in the same buildspace") must have cmake find_package()
    infrastructure.

  * Q: what if I depend on e.g. std_msgs, which is installed on the
    system, and I am building with "pascal" in ROS_LANGS.  

* Installing

* Running

  * from build dir
  * from installed dir

* Testing 

  * Locally on developer's box
  * On CI farm (jenkins)
  * after installation

Dependency graph
----------------

.. rubric:: Legend

.. graphviz::

     digraph legend {
           rankdir=LR
           node [shape=box, style=filled, color="#aaaaff"] "environment variable";
           node [shape=box, style=filled, color="#aaffaa"] "system ROS packages";
           node [shape=box, style=filled, color="#ffaaaa"] "developer ROS packages";
           node [shape=box, style=filled, color="#ffffaa"] "debian packages";
     }

.. rubric:: buildtime


.. graphviz:: 

   digraph ros_build_mechanisms {

        rankdir=BT

        // environment variables:  build parameters
	node [shape = box, style=filled, color="#aaaaff"]; ROS_LANGS

        // packages        
	node [shape = box, style=filled, color="#aaffaa"]; rosbuild genmsg gencpp genpy;

        node [shape = box, style=filled, color="#ffffaa"]; cmake python
        node [shape = box, style=filled, color="#ffaaaa"]; roscpp std_msgs geometry_msgs

        rosbuild -> cmake;
        rosbuild -> python;

        genmsg-> ROS_LANGS;
        genmsg -> rosbuild;
        ROS_LANGS -> genpy [style=dotted];
        ROS_LANGS -> gencpp [style=dotted];

        gencpp -> rosbuild;
        genpy -> rosbuild;
        std_msgs -> genmsg;     
        std_msgs -> rosbuild;     

        geometry_msgs -> genmsg;     
        geometry_msgs -> rosbuild;     

        roscpp -> rosbuild;

        quux_msgs -> genmsg;
        quux_msgs -> std_msgs;
        quux_nodes -> quux_msgs;
        quux_nodes -> rosbuild;
        quux_nodes -> roscpp;
        
   }



TODO
----

* take rospkg, walk manifest.xml files, generate dot dependency graph
  of ros-electric-* at the stack and package levels.  Install
  ros-electric- from debians and operate on them.  rospkg should be
  able to do this.


