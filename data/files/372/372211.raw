export ft_setrts

function ft_setrts(ft_handle::Culong)
  ft_status = ccall((:FT_SetRts, d2xx),Cuint,(Culong,),ft_handle)
  checkstatus(ft_status)
  return nothing
end  