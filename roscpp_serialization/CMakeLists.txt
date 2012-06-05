project(roscpp_serialization)

find_package(catkin REQUIRED)

find_package(cpp_common REQUIRED)
include_directories(${cpp_common_INCLUDE_DIRS})

find_package(rostime REQUIRED)
include_directories(${rostime_INCLUDE_DIRS})

find_package(roscpp_traits REQUIRED)
include_directories(${roscpp_traits_INCLUDE_DIRS})

include_directories(include)

add_library(roscpp_serialization src/serialization.cpp)

install(TARGETS roscpp_serialization
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
  )

install(DIRECTORY include/
        DESTINATION include
        FILES_MATCHING PATTERN "*.h"
        PATTERN ".svn" EXCLUDE)

catkin_project(roscpp_serialization
  LIBRARIES roscpp_serialization
  INCLUDE_DIRS include
  )
