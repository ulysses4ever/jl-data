export FT_GetStatus

function FT_GetStatus(ft_handle::UInt32)
  amountinrxqueue = Ref{Cuint}()
  amountintxqueue = Ref{Cuint}()
  eventstatus = Ref{Cuint}()
  ft_status = ccall((:FT_GetStatus, d2xx),
                     Cuint,
                     (Cuint,Ref{Cuint},Ref{Cuint},Ref{Cuint}),
                     ft_handle, amountinrxqueue, amountintxqueue, eventstatus)
  checkstatus(ft_status)
  return (convert(Int32,amountinrxqueue[]),
          convert(Int32,amountintxqueue[]),convert(Int32,eventstatus[]))
end
