function(shell arg1)
  set(msg "${arg1}")
  foreach(arg ${ARGN})
    set(msg "${msg} ${arg}")
  endforeach()
  message(STATUS ">>> ${msg}")
  execute_process(COMMAND ${arg1} ${ARGN}
    RESULT_VARIABLE res)
  if (res EQUAL 0)
    message(STATUS "<<< ${res}")
    return()
  endif()
  
  message(FATAL_ERROR ">>> Fatal error running command: ${res}")
    
endfunction()

