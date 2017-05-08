export ft_resetport

function ft_resetport(ft_handle::Culong)
  ft_status = ccall((:FT_ResetPort, d2xx),Cuint,(Culong,),ft_handle)
  checkstatus(ft_status)
  return nothing
end