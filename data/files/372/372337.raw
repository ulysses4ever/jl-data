export FT_SetUSBParameters

function FT_SetUSBParameters(ft_handle::UInt32,
                             intransfersize::Integer = 4096,
                             outtransfersize::Integer = 4096)
  @assert intransfersize > 63
  @assert outtransfersize > 63
  @assert intransfersize < 2^16+1
  @assert outtransfersize < 2^16+1
  @assert (intransfersize>>4)*16 == intransfersize
  @assert (outtransfersize>>4)*16 == outtransfersize
  ft_status = ccall((:FT_SetUSBParameters, "ftd2xx.dll"),
                     Culong,
                     (Culong, Culong, Culong),
                     ft_handle, intransfersize, outtransfersize)
  checkstatus(ft_status)
  return nothing
end