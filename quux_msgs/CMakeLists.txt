cmake_minimum_required(VERSION 2.8)
project(quux_msgs)

set(CMAKE_FIND_ROOT_PATH /tmp/sandbox)

find_package(ros_cmake)
#find_package(genmsg)
find_package(gencpp)
find_package(std_msgs)

# todo: will be set by find_package
set(std_msgs_FOUND 1)
set(std_msgs_MSG_INCLUDE_DIRS /u/mkjargaard/repositories/mkjargaard/dist-sandbox/std_msgs/msg)

add_subdirectory(msg)