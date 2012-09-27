cmake_minimum_required(VERSION 2.8)
project(rostime)
find_package(catkin REQUIRED COMPONENTS cpp_common rosunit)
catkin_package(
  INCLUDE_DIRS include
  LIBRARIES ${PROJECT_NAME})

find_package(Boost REQUIRED COMPONENTS date_time system thread)

include_directories(include ${Boost_INCLUDE_DIR} ${catkin_INCLUDE_DIRS})
link_directories(${catkin_LIBRARY_DIRS})

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

catkin_add_gtest(${PROJECT_NAME}-test_time test/time.cpp)
if(TARGET ${PROJECT_NAME}-test_time)
  target_link_libraries(${PROJECT_NAME}-test_time ${catkin_LIBRARIES} rostime)
endif()
