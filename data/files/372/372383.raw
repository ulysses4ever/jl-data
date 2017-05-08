export FT_CyclePort

function FT_CyclePort(ft_handle::UInt32)
  ft_status = ccall((:FT_CyclePort, d2xx),Culong,(Culong,),ft_handle)
  checkstatus(ft_status)
  return nothing
end
