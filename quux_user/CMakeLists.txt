cmake_minimum_required(VERSION 2.8)
project(quux_user)

# set(CMAKE_FIND_ROOT_PATH /tmp/sandbox)

find_package(rosbuild)
find_package(genmsg)
find_package(gencpp)
find_package(std_msgs)
find_package(quux_msgs)

# todo: will be set by find_package
include_directories(${std_msgs_INCLUDE_DIRS} ${quux_msgs_INCLUDE_DIRS})


# Manual ROS deps
include_directories(/opt/ros/electric/stacks/ros_comm/messages/std_msgs/msg_gen/cpp/include)
include_directories(/opt/ros/electric/stacks/ros_comm/clients/cpp/roscpp_serialization/include)
include_directories(/opt/ros/electric/stacks/ros_comm/utilities/rostime/include)
include_directories(/opt/ros/electric/stacks/ros_comm/clients/cpp/roscpp_traits/include)
include_directories(/opt/ros/electric/stacks/ros_comm/utilities/cpp_common/include)
include_directories(/opt/ros/electric/stacks/ros_comm/tools/rosconsole/include)

add_executable(quux_user-exec src/main.cpp /opt/ros/electric/stacks/ros_comm/clients/cpp/roscpp_serialization/src/serialization.cpp)