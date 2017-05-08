export FT_ResetDevice

function FT_ResetDevice(ft_handle::UInt32)
  ft_status = ccall((:FT_ResetDevice, "ftd2xx.dll"),Culong,(Culong,),ft_handle)
  checkstatus(ft_status)
  return nothing
end
