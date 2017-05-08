# ps3000_overview_buffer_ps_status.jl

export ps3000_overview_buffer_status

function ps3000_overview_buffer_status(handle :: Int16)
  # returns true if buffer has overrun
  previous_buffer_overrun = Ref{Int16}
  ps_status = ccall((:ps3000_overview_buffer_status, ps3000driver),Int16,
    (Int16, Ref{Int16}), handle, previous_buffer_overrun)
  if ps_status == 0
    error("ps3000 Error: invalid handle")
  end
  return previous_buffer_overrun[]==0?false:true
end