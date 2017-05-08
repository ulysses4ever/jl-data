export FT_SetLatencyTimer

function FT_SetLatencyTimer(ft_handle::Culong, timer::Integer)
  @assert timer> @linux? 0:1 # is 1ms valid for linux?
  @assert timer<256
  ft_status = ccall((:FT_SetLatencyTimer, d2xx),
                     Cuint,
                     (Culong, Cuchar),
                     ft_handle, timer)
  checkstatus(ft_status)
  return nothing
end