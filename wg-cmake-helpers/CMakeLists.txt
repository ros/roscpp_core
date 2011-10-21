cmake_minimum_required(VERSION 2.8)

project(wg-cmake-helpers)

set(INSTALL_SUFFIX share/${PROJECT_NAME})

set(INFRA_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/${INSTALL_SUFFIX})


configure_file(wg-cmake-helpers-config.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/wg-cmake-helpers-config.cmake
  @ONLY
  )


install(
  FILES 
  ${CMAKE_CURRENT_BINARY_DIR}/wg-cmake-helpers-config.cmake
  pkg-config.cmake.in
  pkg-config-version.cmake.in
  DESTINATION share/wg-cmake-helpers
  )
