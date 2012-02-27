project(roscpp_traits)
find_package(catkin)

install(DIRECTORY include/
        DESTINATION include
        FILES_MATCHING PATTERN "*.h"
        PATTERN ".svn" EXCLUDE)

catkin_project(roscpp_traits
  INCLUDE_DIRS include
  )
