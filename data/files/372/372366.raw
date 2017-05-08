export FT_ClrDtr

function FT_ClrDtr(ft_handle::Culong)
  ft_status = ccall((:FT_ClrDtr, d2xx),Cuint,(Culong,),ft_handle)
  checkstatus(ft_status)
  return nothing
end