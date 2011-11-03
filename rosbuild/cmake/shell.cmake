function(shell arg1)

  execute_process(COMMAND ${arg1} ${ARGN}
    RESULT_VARIABLE res)
  if (res EQUAL 0)
    log(2 "execute_command ${arg1} result: ${res}")
  else()
    set(msg "${arg1}")
    foreach(arg ${ARGN})
      set(msg "${msg} ${arg}")
    endforeach()
    message(FATAL_ERROR "execute_command: ${msg}\n${res}")
  endif()

endfunction()