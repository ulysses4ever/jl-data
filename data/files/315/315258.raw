export ft_restartintask

function ft_restartintask(ft_handle::Culong)
  ft_status = ccall((:FT_RestartInTask, d2xx),Cuint,(Culong,),ft_handle)
  checkstatus(ft_status)
  return nothing
end