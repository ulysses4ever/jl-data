export ft_getqueuestatus

function ft_getqueuestatus(ft_handle::Culong)
  amountinrxqueue = Ref{Cuint}()
  ft_status = ccall((:FT_GetQueueStatus, d2xx),
                     Cuint,
                     (Culong, Ref{Cuint}),
                     ft_handle, amountinrxqueue)
  checkstatus(ft_status)
  return convert(UInt32, amountinrxqueue[])
end 