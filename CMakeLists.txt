cmake_minimum_required(VERSION 2.8)

set(CMAKE_PREFIX_PATH ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_INSTALL_PREFIX})

set(ROSBUILD TRUE CACHE BOOL   "Yes, we are building under the new rosbuild")
set(ROS_LANGS cpp CACHE STRING "ros languages")
set(ROSBUILD_LOG 9)

#find_package(rosbuild)
if(NOT rosbuild_FOUND)
  message(STATUS "Attempting to bootstrap rosbuild")
  if(IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/rosbuild")
    add_subdirectory(rosbuild)
    find_package(rosbuild)
  else()
    message(STATUS "wtf?")
  endif()

  if(NOT rosbuild_FOUND)
    message(FATAL_ERROR "Could not find rosbuild")
  endif()
endif()

find_the_goods()

return()

##
# old stuff
##

add_custom_target(debs)

foreach(proj
    rosbuild
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
