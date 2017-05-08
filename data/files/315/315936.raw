export FT_SetBreakOff

function FT_SetBreakOff(ft_handle::UInt32)
  ft_status = ccall((:FT_SetBreakOff, "ftd2xx.dll"),Culong,(Culong,),ft_handle)
  checkstatus(ft_status)
  return nothing
end
