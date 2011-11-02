cmake_minimum_required(VERSION 2.8)

project(rosbuild)

set(INSTALL_SUFFIX share/cmake/${PROJECT_NAME})

# in source, do we even want this to be possible? :)
set(INFRA_INSTALL_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(PKG_LOCATION "from Source")

configure_file(${PROJECT_NAME}-config.cmake.in
  ${PROJECT_NAME}-config.cmake
  @ONLY
  )

# installable
set(INFRA_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/${INSTALL_SUFFIX})
set(PKG_LOCATION "Installed")

configure_file(${PROJECT_NAME}-config.cmake.in
  cmake_install/${PROJECT_NAME}-config.cmake
  @ONLY
  )

install(
  FILES
  ${CMAKE_CURRENT_BINARY_DIR}/cmake_install/${PROJECT_NAME}-config.cmake

  cmake/em_expander.py

  parse_arguments.cmake
  wg_python.cmake
  debian-util.cmake
  shell.cmake

  pkg-config.cmake.in
  pkg-config-version.cmake.in
  DESTINATION ${INSTALL_SUFFIX}
  )
