cmake_minimum_required(VERSION 2.8)
project(quux_user)

# set(CMAKE_FIND_ROOT_PATH /tmp/sandbox)

find_package(rosbuild)
find_package(genmsg)
find_package(gencpp)
find_package(std_msgs)
find_package(quux_msgs)

find_package(rostime)
include_directories(${rostime_INCLUDE_DIRS})

find_package(cpp_common)
include_directories(${cpp_common_INCLUDE_DIRS})

find_package(roscpp_traits)
include_directories(${roscpp_traits_INCLUDE_DIRS})

find_package(roscpp_serialization)
include_directories(${roscpp_serialization_INCLUDE_DIRS})

assert(gencpp_INCLUDE_DIRS)
include_directories(${gencpp_INCLUDE_DIRS})


# todo: will be set by find_package
include_directories(${std_msgs_INCLUDE_DIRS} ${quux_msgs_INCLUDE_DIRS})


# Manual ROS deps
#include_directories(/opt/ros/electric/stacks/ros_comm/clients/cpp/roscpp_serialization/include)
#include_directories(/opt/ros/electric/stacks/ros_comm/utilities/rostime/include)
#include_directories(/opt/ros/electric/stacks/ros_comm/clients/cpp/roscpp_traits/include)
# include_directories(/opt/ros/electric/stacks/ros_comm/utilities/cpp_common/include)
#include_directories(/opt/ros/electric/stacks/ros_comm/tools/rosconsole/include)

add_executable(quux_user-exec 
  src/main.cpp
  )

target_link_libraries(quux_user-exec ${roscpp_serialization_LIBRARIES})
