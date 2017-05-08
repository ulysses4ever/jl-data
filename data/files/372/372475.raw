export FT_Rescan

function FT_Rescan(ft_handle::Culong)
  ft_status = ccall((:FT_Rescan, d2xx),Cuint,(Culong,),ft_handle)
  checkstatus(ft_status)
  return nothing
end