cmake_minimum_required(VERSION 2.8)
project(roscpp_core)
find_package(catkin REQUIRED)
catkin_package()

foreach(subdir
    cpp_common
    rostime
    roscpp_traits
    roscpp_serialization
    )
  add_subdirectory(${subdir})
endforeach()
