# ps3000_run_block.jl

export ps3000_run_block

function ps3000_run_block(handle::Int16, no_of_samples, timebase, oversample)
  time_indisposed_ms = Ref{Int32}()
  ps_status = ccall((:ps3000_run_block, ps3000driver), Int16,
    (Int16, Int32, Int16, Int16, Ref{Int32}),
    handle, no_of_samples, timebase, oversample, time_indisposed_ms)
  if ps_status == 0
    error("ps3000 Error: one of the parameters is out of range")
  end
  return time_indisposed_ms[]
end
