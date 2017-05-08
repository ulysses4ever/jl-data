# ps3000_run_streaming.jl

export ps3000_run_streaming

function ps3000_run_streaming(handle :: Int16, sample_interval_ms, max_samples, windowed)
  ps_status = ccall((:ps3000_run_streaming, ps3000driver), Int16,
    (Int16, Int16, Int32, Int16), handle, sample_interval_ms, max_samples, windowed)
  if ps_status == 0
    error("ps3000 Error: problem occurred or a value out of range")
  end
  return nothing
end

function ps3000_run_streaming(handle :: Int16, sample_interval_ms, max_samples, windowed::Bool)
  ps3000_run_streaming(handle,sample_interval_ms,max_samples,windowed?0x0001:0x0000)
end
