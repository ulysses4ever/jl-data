export FT_GetLatencyTimer

function FT_GetLatencyTimer(ft_handle::UInt32)
  timer = Ref{Cuchar}()
  ft_status = ccall((:FT_GetLatencyTimer, d2xx),
                     Cuint,
                     (Cuint, Ref{Cuchar}),
                     ft_handle, timer)
  checkstatus(ft_status)
  return convert(UInt8,timer[])
end