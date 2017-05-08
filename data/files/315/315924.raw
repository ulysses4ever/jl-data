export FT_ResetPort

function FT_ResetPort(ft_handle::UInt32)
  ft_status = ccall((:FT_ResetPort, "ftd2xx.dll"),Culong,(Culong,),ft_handle)
  checkstatus(ft_status)
  return nothing
end