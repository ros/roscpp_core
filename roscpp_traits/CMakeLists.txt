project(roscpp_traits)
find_package(catkin REQUIRED)
catkin_project_export(INCLUDE_DIRS include)

install(DIRECTORY include/
  DESTINATION ${CATKIN_GLOBAL_INCLUDE_DESTINATION}
  FILES_MATCHING PATTERN "*.h")
