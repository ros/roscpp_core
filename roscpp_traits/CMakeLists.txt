project(roscpp_traits)
find_package(catkin)

install(DIRECTORY include
  DESTINATION include)

catkin_project(roscpp_traits
  VERSION 0.0.0
  INCLUDE_DIRS include
  )