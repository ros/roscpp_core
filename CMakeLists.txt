cmake_minimum_required(VERSION 2.8)
find_package(catkin)
find_package(genmsg)

message(STATUS "dist sandbox!  whee!")

foreach(subdir

    cpp_common
    rostime
    roscpp_traits
    roscpp_serialization
    std_msgs

    )
  message("distsandbox: ${subdir}")
  add_subdirectory(${subdir})
endforeach()