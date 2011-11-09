project(roscpp_core)
cmake_minimum_required(VERSION 2.8)
find_package(catkin)
find_package(genmsg)

foreach(subdir

    cpp_common
    rostime
    roscpp_traits
    roscpp_serialization

    )
  message("roscpp_core: ${subdir}")
  add_subdirectory(${subdir})
endforeach()

