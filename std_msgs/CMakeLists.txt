cmake_minimum_required(VERSION 2.8)
project(std_msgs)

find_package(catkin)
find_package(genmsg)

generate_msgs(${PROJECT_NAME}
  PATH msg
  MESSAGES 

  msg/Bool.msg msg/Float32MultiArray.msg msg/Int64MultiArray.msg
  msg/UInt32.msg msg/Byte.msg msg/Float64.msg msg/Int8.msg
  msg/UInt32MultiArray.msg msg/ByteMultiArray.msg
  msg/Float64MultiArray.msg msg/Int8MultiArray.msg msg/UInt64.msg
  msg/Char.msg msg/Header.msg msg/MultiArrayDimension.msg
  msg/UInt64MultiArray.msg msg/Int16.msg msg/MultiArrayLayout.msg
  msg/UInt8.msg msg/ColorRGBA.msg msg/Int16MultiArray.msg
  msg/String.msg msg/UInt8MultiArray.msg msg/Duration.msg
  msg/Int32.msg msg/Time.msg msg/Empty.msg msg/Int32MultiArray.msg
  msg/UInt16.msg msg/Float32.msg msg/Int64.msg
  msg/UInt16MultiArray.msg

  )

install_cmake_infrastructure(${PROJECT_NAME}
  VERSION 0.0.1
  MSG_DIRS msg
  )
