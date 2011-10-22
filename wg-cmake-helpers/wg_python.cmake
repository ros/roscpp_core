message("WHEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE")
find_package(PythonInterp)

macro(wg_python)
  if(EXISTS ${PROJECT_SOURCE_DIR}/setup.sh)
    execute_process(${PYTHON_EXECUTABLE} ${PROJECT_SOURCE_DIR}/setup.sh -q develop 
      --install-dir ${CMAKE_BINARY_DIR}
      )
  endif()
endmacro()