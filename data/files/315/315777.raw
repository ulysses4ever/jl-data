export ft_cycleport

function ft_cycleport(ft_handle::Culong)
  ft_status = ccall((:FT_CyclePort, d2xx),Cuint,(Culong,),ft_handle)
  checkstatus(ft_status)
  return nothing
end
