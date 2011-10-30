cmake_minimum_required(VERSION 2.8)

project(ros_cmake)

set(INSTALL_SUFFIX share/cmake/${PROJECT_NAME})

set(INFRA_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/${INSTALL_SUFFIX})

configure_file(${PROJECT_NAME}-config.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake
  @ONLY
  )

install(
  FILES 
  ${PROJECT_NAME}-config.cmake
  cmake/em.py
  cmake/em_expander.py

  parse_arguments.cmake
  wg_python.cmake

  pkg-config.cmake.in
  pkg-config-version.cmake.in
  DESTINATION ${INSTALL_SUFFIX}
  )
