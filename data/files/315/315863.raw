export FT_GetModemStatus

function FT_GetModemStatus(ft_handle::UInt32)
  modemstatus = Ref{Culong}()
  ft_status = ccall((:FT_GetModemStatus, "ftd2xx.dll"),
                     Culong,
                     (Culong, Ref{Culong}),
                     ft_handle, modemstatus)
  checkstatus(ft_status)
  return convert(UInt32,modemstatus[])
end 