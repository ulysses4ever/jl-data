# ps3000_get_timebase.jl

export ps3000_get_timebase

function ps3000_get_timebase(handle::Int16,
                             timebase::Int16,
                             no_of_samples::Int32,
                             oversample::Int16)
  time_interval = Ref{Int32}
  time_units = Ref{Int16}
  max_samples = Ref{Int32}
  ps_status = ccall((:ps3000_get_timebase, ps3000driver),Int16,
    (Int16, Int16, Int32, Ref{Int32}, Ref{Int16}, Int16, Ref{Int32}),
    handle, timebase, no_of_samples, time_interval,
    time_units, oversample, max_samples)
  if ps_status == 0
    error("ps3000 Error: Parameter Out Of Range")
  end
  return (time_interval[], time_units[], max_samples[])
end