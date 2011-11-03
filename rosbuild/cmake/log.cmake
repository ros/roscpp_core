# Log levels
# 0 Normal use
# 1 Rosbuild developer use (Stuff being developed)
# 2 Rosbuild developer use (Stuff working)
# 3 Also Print True Assert Statements

function(LOG ARG_LEVEL ARG_MSG)
  if(NOT ROS_LOG_LEVEL)
    set(ROS_LOG_LEVEL 0)
  endif()

  if(NOT ARG_LEVEL GREATER ${ROS_LOG_LEVEL})
    message(STATUS "*${ARG_LEVEL}* ${ARG_MSG}")
  endif()
endfunction()