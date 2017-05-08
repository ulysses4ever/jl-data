export FT_SetDtr

function FT_SetDtr(ft_handle::Culong)
  ft_status = ccall((:FT_SetDtr, d2xx),Cuint,(Culong,),ft_handle)
  checkstatus(ft_status)
  return nothing
end  