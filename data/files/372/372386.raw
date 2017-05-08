export ft_cycleport

function ft_cycleport(ft_handle::Culong)
  ft_status = ccall((:ft_cycleport, d2xx),Cuint,(Culong,),ft_handle)
  checkstatus(ft_status)
  return nothing
end
