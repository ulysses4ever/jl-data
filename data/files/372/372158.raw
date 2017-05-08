export ft_getstatus

function ft_getstatus(ft_handle::Culong)
  amountinrxqueue = Ref{Cuint}()
  amountintxqueue = Ref{Cuint}()
  eventstatus = Ref{Cuint}()
  ft_status = ccall((:FT_GetStatus, d2xx),
                     Cuint,
                     (Culong,Ref{Cuint},Ref{Cuint},Ref{Cuint}),
                     ft_handle, amountinrxqueue, amountintxqueue, eventstatus)
  checkstatus(ft_status)
  return (convert(Int32,amountinrxqueue[]),
          convert(Int32,amountintxqueue[]),convert(Int32,eventstatus[]))
end
