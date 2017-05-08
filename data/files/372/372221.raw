export ft_stopintask

function ft_stopintask(ft_handle::Culong)
  ft_status = ccall((:FT_StopInTask, d2xx),Cuint,(Culong,),ft_handle)
  checkstatus(ft_status)
  return nothing
end