project(rostime)
find_package(catkin)
include_directories(include)

find_package(cpp_common)
include_directories(${cpp_common_INCLUDE_DIRS})

find_package(Boost COMPONENTS date_time thread)

if (UBUNTU_ONEIRIC)
  find_library(RT_LIBRARY rt)
  message("RT_LIBRARY: ${RT_LIBRARY}")
endif()

add_library(rostime SHARED
  src/time.cpp src/rate.cpp src/duration.cpp)

target_link_libraries(rostime ${Boost_LIBRARIES} ${RT_LIBRARY})

install(TARGETS rostime
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  )

install_cmake_infrastructure(rostime
  VERSION 0.0.0
  INCLUDE_DIRS include
  LIBRARIES rostime
  )