cmake_minimum_required(VERSION 2.8)
project(std_msgs)

find_package(rosbuild)
find_package(genmsg)

#add_subdirectory(msg)
generate_msgs(${PROJECT_NAME}
  MESSAGES msg/String.msg
  #LANGS cpp
  )

install_cmake_infrastructure(${PROJECT_NAME}
  VERSION 0.0.1
  MSG_DIRS msg
  INCLUDE_DIRS include
  )
