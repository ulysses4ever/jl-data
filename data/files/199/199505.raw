# ps3000_run_streaming_ns.jl

export ps3000_run_streaming_ns

function ps3000_run_streaming_ns(handle :: Int16,
                                 sample_interval,
                                 time_unit,
                                 max_samples,
                                 auto_stop,
                                 no_of_samples_per_aggeregate,
                                 overview_buffer_size = 0x4000)
  ps_status = ccall((:ps3000_run_streaming_ns, ps3000driver), Int16,
    (Int16, UInt32, Int16, UInt32, Int16, UInt32, Uint32),
    handle, sample_interval, time_unit, max_samples, auto_stop,
    no_of_samples_per_aggeregate, overview_buffer_size)
  if ps_status == 0
    error("ps3000 Error: problem occurred or value out of range")
  end
  return nothing
end

function ps3000_run_streaming_ns(handle :: Int16,
                                 sample_interval,
                                 time_unit,
                                 max_samples,
                                 auto_stop::Bool,
                                 no_of_samples_per_aggeregate,
                                 overview_buffer_size = 0x4000)
  ps3000_run_streaming_ns(handle,
                          sample_interval,
                          time_unit,
                          max_samples,
                          auto_stop?0x0001:0x0000
                          no_of_samples_per_aggeregate,
                          overview_buffer_size)

end
