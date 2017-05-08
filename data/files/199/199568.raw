# ps3000_get_streaming_values_no_aggregation.jl

export ps3000_get_streaming_values_no_aggregation!, StreamingBufferNoAggregation

immutable StreamingBufferNoAggregation
  a :: Array{Int16,1}
  b :: Array{Int16,1}
  c :: Array{Int16,1}
  d :: Array{Int16,1}
  StreamingBufferNoAggregation(length) = new(Array(Int16,length),Array(Int16,length),
                                Array(Int16,length),Array(Int16,length))
end

function ps3000_get_streaming_values_no_aggregation!(handle        :: Int16,
                                                      st           :: Float64,
                                                      buffer       :: StreamingBufferNoAggregation, 
                                                      no_of_values)
  start_time = Ref{Float64}(st)   # start, relative to trigger, time in ns
  overflow = Ref{Int16}           # bitfield, see doc
  triggered_at = Ref{UInt32}      # index trigger occured at
  triggered = Ref{UInt32}         # was there a valid trigger?
    number_written_to_buffer = ccall((:ps3000_get_streaming_values_no_aggregation, ps3000driver),UInt32,
    (Int16, Ref{Cdouble},
    Ptr{Int16},
    Ptr{Int16},
    Ptr{Int16},
    Ptr{Int16},
    Ref{Int16}, Ref{UInt32}, Ref{Int16}, UInt32),
    handle, start_time,
    buffer.a,
    buffer.b,
    buffer.c,
    buffer.d,
    overflow, triggered_at, triggered, no_of_values)
  if number_written_to_buffer == 0
    error("ps3000 Error: Parameter Out Of Range")
  end
  return (number_written_to_buffer,overflow[],triggered_at[],triggered[]==0?false:true)
end
