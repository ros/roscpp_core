cmake_minimum_required(VERSION 2.8)

set(ROSBUILD TRUE CACHE BOOL   "Yes, we are building under the new rosbuild")
set(ROS_LANGS cpp CACHE STRING "ros languages") 

set(CMAKE_INSTALL_PREFIX /tmp/sandbox2)
set(CMAKE_PREFIX_PATH ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_INSTALL_PREFIX})

message(STATUS "============== rosbuild ========================================")
add_subdirectory(rosbuild)

#foreach(proj ${ROS_LANGS})
#  message(STATUS "============== gen${proj} ========================================")
#  add_subdirectory(gen${proj})
#endforeach() 
    
foreach(proj 
    genmsg
    gencpp
    cpp_common
    rostime
    roscpp_traits
    roscpp_serialization
    std_msgs
    foo
    bar
    quux_msgs
    quux_user)
  message(STATUS "============== ${proj} ========================================")
  add_subdirectory(${proj})
endforeach()
