project(roscpp_serialization)

find_package(catkin)

find_package(cpp_common)
include_directories(${cpp_common_INCLUDE_DIRS})

find_package(rostime)
include_directories(${rostime_INCLUDE_DIRS})

find_package(roscpp_traits)
include_directories(${roscpp_traits_INCLUDE_DIRS})

include_directories(include)

add_library(roscpp_serialization SHARED src/serialization.cpp)

install_cmake_infrastructure(roscpp_serialization
  VERSION 0.0.0
  LIBRARIES roscpp_serialization
  INCLUDE_DIRS include
  )
