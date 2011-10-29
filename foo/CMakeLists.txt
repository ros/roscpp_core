cmake_minimum_required(VERSION 2.8)
find_package(rosbuild)

include_directories(include)

add_library(foo SHARED src/lib.cpp)

install(TARGETS foo
  LIBRARY DESTINATION lib
  )

install(DIRECTORY include/foo
  DESTINATION include
  FILES_MATCHING PATTERN *.hpp
  )

install_cmake_infrastructure(foo
  VERSION 1.3.1
  INCLUDE_DIRS include
  LIBRARIES foo)

