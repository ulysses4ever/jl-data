export FT_RestartInTask

function FT_RestartInTask(ft_handle::UInt32)
  ft_status = ccall((:FT_RestartInTask, "ftd2xx.dll"),Culong,(Culong,),ft_handle)
  checkstatus(ft_status)
  return nothing
end