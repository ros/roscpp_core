cmake_minimum_required(VERSION 2.8.3)
project(rostime)

find_package(catkin REQUIRED COMPONENTS cpp_common)
find_package(Boost REQUIRED COMPONENTS date_time system thread)
catkin_package(
  INCLUDE_DIRS include
  LIBRARIES ${PROJECT_NAME}
  CATKIN_DEPENDS cpp_common
  DEPENDS Boost
)

include_directories(include ${catkin_INCLUDE_DIRS} ${Boost_INCLUDE_DIR})

add_library(rostime 
  src/duration.cpp
  src/rate.cpp
  src/time.cpp)

target_link_libraries(rostime ${Boost_LIBRARIES})
if(NOT APPLE)
  target_link_libraries(rostime ${RT_LIBRARY})
endif()

install(TARGETS rostime
  RUNTIME DESTINATION ${CATKIN_GLOBAL_BIN_DESTINATION}
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION})

install(DIRECTORY include/
  DESTINATION ${CATKIN_GLOBAL_INCLUDE_DESTINATION}
  FILES_MATCHING PATTERN "*.h")

catkin_add_gtest(${PROJECT_NAME}-test_time test/time.cpp)
if(TARGET ${PROJECT_NAME}-test_time)
  target_link_libraries(${PROJECT_NAME}-test_time ${catkin_LIBRARIES} rostime)
endif()
