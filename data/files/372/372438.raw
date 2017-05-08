export FT_GetStatus

function FT_GetStatus(ft_handle::UInt32)
  amountinrxqueue = Ref{Culong}()
  amountintxqueue = Ref{Culong}()
  eventstatus = Ref{Culong}()
  ft_status = ccall((:FT_GetStatus, d2xx),
                     Culong,
                     (Culong,Ref{Culong},Ref{Culong},Ref{Culong}),
                     ft_handle, amountinrxqueue, amountintxqueue, eventstatus)
  checkstatus(ft_status)
  return (convert(Int32,amountinrxqueue[]),
          convert(Int32,amountintxqueue[]),convert(Int32,eventstatus[]))
end
