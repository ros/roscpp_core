project(rostime)
find_package(catkin)
include_directories(include)

find_package(cpp_common)
include_directories(${cpp_common_INCLUDE_DIRS})
find_package(Boost COMPONENTS date_time thread)

add_library(rostime SHARED
  src/time.cpp src/rate.cpp src/duration.cpp)

target_link_libraries(rostime ${Boost_LIBRARIES})
if(NOT APPLE)
  target_link_libraries(rostime ${RT_LIBRARY})
endif()

install(TARGETS rostime
  DESTINATION lib
  )

install(DIRECTORY include/
        DESTINATION include
        FILES_MATCHING PATTERN "*.h"
        PATTERN ".svn" EXCLUDE)

catkin_project(rostime
  VERSION 0.0.0
  INCLUDE_DIRS include
  LIBRARIES rostime
  )
