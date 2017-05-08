export FT_SetRts

function FT_SetRts(ft_handle::UInt32)
  ft_status = ccall((:FT_SetRts, d2xx),Culong,(Culong,),ft_handle)
  checkstatus(ft_status)
  return nothing
end  