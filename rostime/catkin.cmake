project(rostime)
find_package(catkin)
include_directories(include)

find_package(cpp_common)
include_directories(${cpp_common_INCLUDE_DIRS})

# include(${CMAKE_CURRENT_BINARY_DIR}/package.cmake)
# 
# rosbuild_add_boost_directories()
# 

add_library(${PROJECT_NAME} SHARED
  src/time.cpp src/rate.cpp src/duration.cpp)

install(TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  )

# 
# rosbuild_link_boost(${PROJECT_NAME} date_time thread) 
# 
# if(NOT (APPLE OR WIN32 OR MINGW))
#   target_link_libraries(${PROJECT_NAME} rt)
# endif()
# 

install_cmake_infrastructure(rostime
  VERSION 0.0.0
  INCLUDE_DIRS include
  )