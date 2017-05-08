export FT_ClrDtr

function FT_ClrDtr(ft_handle::UInt32)
  ft_status = ccall((:FT_ClrDtr, d2xx),Culong,(Culong,),ft_handle)
  checkstatus(ft_status)
  return nothing
end