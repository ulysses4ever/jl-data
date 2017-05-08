export FT_ClrRts

function FT_ClrRts(ft_handle::Culong)
  ft_status = ccall((:FT_ClrRts, d2xx),Cuint,(Culong,),ft_handle)
  checkstatus(ft_status)
  return nothing
end