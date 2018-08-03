cmake_minimum_required(VERSION 3.5)
project(roscpp_traits)
find_package(ament_cmake REQUIRED)
find_package(cpp_common REQUIRED)
find_package(rostime REQUIRED)

ament_export_include_directories(include)
ament_package()

install(DIRECTORY include/
  DESTINATION include
  FILES_MATCHING PATTERN "*.h")
