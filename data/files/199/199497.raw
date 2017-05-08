# ps3000_set_ets.jl

export ps3000_set_ets, PS3000ETSMode

function ps3000_set_ets(handle::Int16, mode, ets_cycles, ets_interleave)
  effective_sample_time_ps = ccall((:ps3000_set_ets, ps3000driver), Int32,
    (Int16,Int16,Int16,Int16),handle,mode,ets_cycles,ets_interleave)
  if effective_sample_time_ps == 0
    error("ps3000 Error: ETS is disabled or one of the parameters is out of range")
  end
  return effective_sample_time_ps
end

baremodule PS3000ETSMode
  const OFF = 0 # disables ETS
  const FAST = 1 # enables ETS and provides ets_cycles cycles of data, which may contain data from previously returned cycles
  const SLOW = 2 # enables ETS and provides fresh data every ets_cycles cycles. PS3000_ETS_SLOW takes longer to provide each data set, but the data sets are more stable and unique
end  # module