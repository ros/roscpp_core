cmake_minimum_required(VERSION 2.8)

set(CMAKE_INSTALL_PREFIX /tmp/sandbox2)
set(CMAKE_PREFIX_PATH ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_INSTALL_PREFIX})

message(STATUS 'rosbuild')
add_subdirectory(rosbuild)

message(STATUS 'genmsg')
add_subdirectory(genmsg)

message(STATUS 'gencpp')
add_subdirectory(gencpp)

message(STATUS 'std_msgs')
add_subdirectory(std_msgs)

message(STATUS 'quux_msgs')
add_subdirectory(quux_msgs)

