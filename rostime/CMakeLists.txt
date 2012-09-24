cmake_minimum_required(VERSION 2.8)
project(rostime)
find_package(catkin REQUIRED COMPONENTS cpp_common)
catkin_package(
  INCLUDE_DIRS include
  LIBRARIES ${PROJECT_NAME})

include_directories(include ${catkin_INCLUDE_DIRS})
link_directories(${catkin_LIBRARY_DIRS})

find_package(Boost REQUIRED COMPONENTS date_time system thread)

add_library(rostime 
  src/duration.cpp
  src/rate.cpp
  src/time.cpp)

target_link_libraries(rostime ${Boost_LIBRARIES})
if(NOT APPLE)
  target_link_libraries(rostime ${RT_LIBRARY})
endif()

install(TARGETS rostime
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION})

install(DIRECTORY include/
  DESTINATION ${CATKIN_GLOBAL_INCLUDE_DESTINATION}
  FILES_MATCHING PATTERN "*.h")
