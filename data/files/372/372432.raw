export FT_GetQueueStatus

function FT_GetQueueStatus(ft_handle::UInt32)
  amountinrxqueue = Ref{Culong}()
  ft_status = ccall((:FT_GetQueueStatus, "ftd2xx.dll"),
                     Culong,
                     (Culong, Ref{Culong}),
                     ft_handle, amountinrxqueue)
  checkstatus(ft_status)
  return convert(UInt32, amountinrxqueue[])
end 