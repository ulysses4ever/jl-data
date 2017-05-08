export ft_clrrts

function ft_clrrts(ft_handle::Culong)
  ft_status = ccall((:ft_clrrts, d2xx),Cuint,(Culong,),ft_handle)
  checkstatus(ft_status)
  return nothing
end