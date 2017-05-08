export FT_SetDtr

function FT_SetDtr(ft_handle::UInt32)
  ft_status = ccall((:FT_SetDtr, "ftd2xx.dll"),Culong,(Culong,),ft_handle)
  checkstatus(ft_status)
  return nothing
end  