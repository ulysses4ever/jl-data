# ps3000_get_streaming_last_values.jl

export ps3000_get_streaming_last_values

function ps3000_get_streaming_last_values(handle::Int16, callback::Ptr{Void})
  #=
  c call signature for callback:

  void my_get_overview_buffers (
    int16_t ** overviewBuffers,
    int16_t overflow,
    uint32_t triggeredAt,
    int16_t triggered,
    int16_t auto_stop,
    uint32_t nValues )
  =#
  ps_status = ccall((:ps3000_get_streaming_last_values, ps3000driver),
                  Int16,
                  (Int16, Ptr{Void}),
                  handle, callback)
  if ps_status == 0
    error("ps3000 Error: Parameter Out Of Range (possibly from ps3000_run_streaming_ns()")
  end
  return ps_status  # The actual number of data values returned per channel
end