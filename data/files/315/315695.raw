export FT_SetLatencyTimer

function FT_SetLatencyTimer(ft_handle::UInt32, timer::Integer)
  @assert timer>1
  @assert timer<256
  ft_status = ccall((:FT_SetLatencyTimer, d2xx),
                     Culong,
                     (Culong, Cuchar),
                     ft_handle, timer)
  checkstatus(ft_status)
  return nothing
end