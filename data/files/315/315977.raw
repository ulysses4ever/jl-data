export FT_StopInTask

function FT_StopInTask(ft_handle::UInt32)
  ft_status = ccall((:FT_StopInTask, "ftd2xx.dll"),Culong,(Culong,),ft_handle)
  checkstatus(ft_status)
  return nothing
end