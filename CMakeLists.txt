project(roscpp_core)
cmake_minimum_required(VERSION 2.8)
find_package(catkin REQUIRED)
catkin_stack()

foreach(subdir
    cpp_common
    rostime
    roscpp_traits
    roscpp_serialization
    )
  add_subdirectory(${subdir})
endforeach()

# install all manifests
install_matching_to_share(manifest.xml)

install(FILES stack.xml 
        DESTINATION share/${PROJECT_NAME})
