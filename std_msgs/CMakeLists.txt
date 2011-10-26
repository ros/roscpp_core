cmake_minimum_required(VERSION 2.8)
project(std_msgs)

set(CMAKE_FIND_ROOT_PATH /tmp/sandbox)

find_package(ros_cmake)
find_package(genmsg) # todo: required?
find_package(gencpp)

add_subdirectory(msg)
#generate_msg_cpp(${PROJECT_NAME}
#  MESSAGES msg/String.msg)

install(DIRECTORY gen_msgs/include/std_msgs
  DESTINATION include
  FILES_MATCHING PATTERN *.h
  )

install_cmake_infrastructure(${PROJECT_NAME}
  VERSION 0.0.1
  MSG_DIRS msg
  INCLUDE_DIRS include
  )
