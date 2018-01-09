cmake_minimum_required(VERSION 3.5)
project(rostime)

find_package(ament_cmake REQUIRED)
find_package(cpp_common REQUIRED)

set(Boost_USE_STATIC_LIBS ON)
find_package(Boost REQUIRED)

include_directories(include 
  ${cpp_common_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIRS}
)

add_library(rostime 
  src/duration.cpp
  src/rate.cpp
  src/time.cpp)

target_link_libraries(rostime)

ament_export_include_directories(include)
ament_export_libraries(rostime)
ament_package()

install(TARGETS rostime
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin)

install(DIRECTORY include/
  DESTINATION include
  FILES_MATCHING PATTERN "*.h")

