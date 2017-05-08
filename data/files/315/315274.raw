export ft_setbreakoff

function ft_setbreakoff(ft_handle::Culong)
  ft_status = ccall((:FT_SetBreakOff, d2xx),Cuint,(Culong,),ft_handle)
  checkstatus(ft_status)
  return nothing
end
