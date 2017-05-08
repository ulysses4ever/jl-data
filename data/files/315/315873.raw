export FT_GetQueueStatus

function FT_GetQueueStatus(ft_handle::UInt32)
  amountinrxqueue = Ref{Cuint}()
  ft_status = ccall((:FT_GetQueueStatus, d2xx),
                     Cuint,
                     (Cuint, Ref{Cuint}),
                     ft_handle, amountinrxqueue)
  checkstatus(ft_status)
  return convert(UInt32, amountinrxqueue[])
end 