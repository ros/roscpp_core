cmake_minimum_required(VERSION 2.8)
project(quux_msgs)

set(CMAKE_FIND_ROOT_PATH /tmp/sandbox)

find_package(rosbuild)
find_package(genmsg)
find_package(std_msgs)

# todo: will be set by find_package
set(std_msgs_FOUND 1)

#add_subdirectory(msg)
generate_msgs(${PROJECT_NAME}
  MESSAGES msg/QuuxString.msg
  DEPENDENCIES std_msgs
  LANGS cpp
  )

install(DIRECTORY gen_msgs/include/quux_msgs
  DESTINATION include
  FILES_MATCHING PATTERN *.h
  # add dependency to quux_msgs_gencpp?
  )

install_cmake_infrastructure(${PROJECT_NAME}
  VERSION 0.0.1
  MSG_DIRS msg
  INCLUDE_DIRS include
  )

