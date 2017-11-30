cmake_minimum_required(VERSION 3.5)
project(rostime)

find_package(ament_cmake REQUIRED)
find_package(cpp_common REQUIRED)

include_directories(include 
  ${cpp_common_INCLUDE_DIRS}
  $ENV{Boost_Root}
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

