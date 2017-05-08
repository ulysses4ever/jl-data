export FT_SetBreakOff

function FT_SetBreakOff(ft_handle::Culong)
  ft_status = ccall((:FT_SetBreakOff, d2xx),Cuint,(Culong,),ft_handle)
  checkstatus(ft_status)
  return nothing
end
