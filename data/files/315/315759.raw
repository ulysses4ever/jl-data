export ft_clrdtr

function ft_clrdtr(ft_handle::Culong)
  ft_status = ccall((:FT_ClrDtr, d2xx),Cuint,(Culong,),ft_handle)
  checkstatus(ft_status)
  return nothing
end