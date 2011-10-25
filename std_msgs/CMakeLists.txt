cmake_minimum_required(VERSION 2.8)
project(std_msgs)

set(CMAKE_FIND_ROOT_PATH /tmp/sandbox)

find_package(ros_cmake)
find_package(genmsg) # todo: required?
find_package(gencpp)

add_subdirectory(msg)

install_cmake_infrastructure(${PROJECT_NAME}
  VERSION 1.3.1
  )
