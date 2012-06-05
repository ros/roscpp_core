project(rostime)
find_package(catkin REQUIRED)
include_directories(include)

find_package(cpp_common REQUIRED)
include_directories(${cpp_common_INCLUDE_DIRS})
find_package(Boost REQUIRED COMPONENTS date_time thread)

add_library(rostime 
  src/time.cpp src/rate.cpp src/duration.cpp)

target_link_libraries(rostime ${Boost_LIBRARIES})
if(NOT APPLE)
  target_link_libraries(rostime ${RT_LIBRARY})
endif()

install(TARGETS rostime
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  )

install(DIRECTORY include/
        DESTINATION include
        FILES_MATCHING PATTERN "*.h"
        PATTERN ".svn" EXCLUDE)

catkin_project(rostime
  INCLUDE_DIRS include
  LIBRARIES rostime
  )
