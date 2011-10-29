cmake_minimum_required(VERSION 2.8)
find_package(rosbuild)

find_package(foo)
include_directories(${foo_INCLUDE_DIRS})

include_directories(include)

add_library(bar SHARED src/lib.cpp)
add_executable(bar-exec src/main.cpp)
target_link_libraries(bar-exec bar ${foo_LIBRARIES})

install(TARGETS bar
  LIBRARY DESTINATION lib
  )

install(DIRECTORY include/bar
  DESTINATION include
  FILES_MATCHING PATTERN *.hpp
  )

install_cmake_infrastructure(bar VERSION 7.0.3 INCLUDE_DIRS include LIBRARIES bar)