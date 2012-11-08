cmake_minimum_required(VERSION 2.8.3)
project(roscpp_traits)
find_package(catkin REQUIRED)
catkin_package(
  INCLUDE_DIRS include
  DEPENDS rostime)

install(DIRECTORY include/
  DESTINATION ${CATKIN_GLOBAL_INCLUDE_DESTINATION}
  FILES_MATCHING PATTERN "*.h")
