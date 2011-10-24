cmake_minimum_required(VERSION 2.8)

install(PROGRAMS simpleinstall_bin.py
  DESTINATION bin)

add_subdirectory(src)
