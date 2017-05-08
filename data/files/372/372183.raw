export ft_setbreakon

function ft_setbreakon(ft_handle::Culong)
  ft_status = ccall((:FT_SetBreakOn, d2xx),Cuint,(Culong,),ft_handle)
  checkstatus(ft_status)
  return nothing
end