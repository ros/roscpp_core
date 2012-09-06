project(cpp_common)
find_package(catkin REQUIRED)
catkin_project(cpp_common
  INCLUDE_DIRS include)

include(CheckIncludeFile)
include(CheckFunctionExists)
include(CheckCXXSourceCompiles)

include_directories(include)

# execinfo.h is needed for backtrace on glibc systems
CHECK_INCLUDE_FILE(execinfo.h HAVE_EXECINFO_H)
if(HAVE_EXECINFO_H)
  add_definitions(-DHAVE_EXECINFO_H=1)
endif(HAVE_EXECINFO_H)
# do we have demangle capability?
# CHECK_INCLUDE_FILE doesn't work here for some reason
CHECK_CXX_SOURCE_COMPILES("#include<cxxabi.h>\nintmain(intargc,char**argv){}" HAVE_CXXABI_H)
if(HAVE_CXXABI_H)
  add_definitions(-DHAVE_CXXABI_H=1)
endif()
CHECK_FUNCTION_EXISTS(backtrace HAVE_GLIBC_BACKTRACE)
if(HAVE_GLIBC_BACKTRACE)
  add_definitions(-DHAVE_GLIBC_BACKTRACE)
endif(HAVE_GLIBC_BACKTRACE)

add_library(${PROJECT_NAME} src/debug.cpp)

install(TARGETS ${PROJECT_NAME}
  ARCHIVE DESTINATION ${CATKIN_PROJECT_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PROJECT_LIB_DESTINATION})

install(DIRECTORY include/
  DESTINATION ${CATKIN_PROJECT_INCLUDE_DESTINATION}
  FILES_MATCHING PATTERN "*.h")
