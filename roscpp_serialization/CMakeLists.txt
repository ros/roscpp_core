project(roscpp_serialization)
find_package(catkin REQUIRED COMPONENTS cpp_common roscpp_traits rostime)
catkin_project(roscpp_serialization
  INCLUDE_DIRS include
  LIBRARIES roscpp_serialization)

include_directories(include ${catkin_INCLUDE_DIRS})
link_directories(${catkin_LIBRARY_DIRS})

add_library(roscpp_serialization src/serialization.cpp)

install(TARGETS roscpp_serialization
  ARCHIVE DESTINATION ${PROJECT_LIB_DESTINATION}
  LIBRARY DESTINATION ${PROJECT_LIB_DESTINATION})

install(DIRECTORY include/
  DESTINATION ${PROJECT_INCLUDE_DESTINATION}
  FILES_MATCHING PATTERN "*.h")
