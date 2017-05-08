export FT_GetLatencyTimer

function FT_GetLatencyTimer(ft_handle::Culong)
  timer = Ref{Cuchar}()
  ft_status = ccall((:FT_GetLatencyTimer, d2xx),
                     Cuint,
                     (Culong, Ref{Cuchar}),
                     ft_handle, timer)
  checkstatus(ft_status)
  return timer[]
end