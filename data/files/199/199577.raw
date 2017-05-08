# ps3000_get_streaming_values.jl

export ps3000_get_streaming_values, StreamingBufferAggregation

immutable StreamingBuffer
  a_max :: Array{Int16,1}
  a_mim :: Array{Int16,1}
  b_max :: Array{Int16,1}
  b_mim :: Array{Int16,1}
  c_max :: Array{Int16,1}
  c_mim :: Array{Int16,1}
  d_max :: Array{Int16,1}
  d_mim :: Array{Int16,1}
  function StreamingBuffer(length)
    new(Array(Int16,length),Array(Int16,length),Array(Int16,length),Array(Int16,length),
        Array(Int16,length),Array(Int16,length),Array(Int16,length),Array(Int16,length))
  end
end

function ps3000_get_streaming_values!(handle       :: Int16,
                                      st           :: Float64,
                                      buffer       :: StreamingBuffer,
                                      no_of_values :: UInt32,
                                      no_of_samples_per_aggreate :: UInt32)
  @assert length(buffer.buffer_a_max)>=no_of_values  # make sure buffer is big enough
  start_time = Ref{Float64}(st)   # start, relative to trigger, time in ns
  overflow = Ref{Int16}           # bitfield, see doc
  triggered_at = Ref{UInt32}      # index trigger occured at
  triggered = Ref{UInt32}         # was there a valid trigger?  
  number_written_to_buffer = ccall((:ps3000_get_streaming_values, ps3000driver),UInt32,
    (Int16, Ref{Cdouble},
    Ptr{Int16}, Ptr{Int16},
    Ptr{Int16}, Ptr{Int16},
    Ptr{Int16}, Ptr{Int16},
    Ptr{Int16}, Ptr{Int16},
    Ref{Int16}, Ref{UInt32}, Ref{Int16}, UInt32, UInt32),
    handle, start_time,
    buffer.a_max, buffer.a_min,
    buffer.b_max, buffer.b_min,
    buffer.c_max, buffer.c_min,
    buffer.d_max, buffer.d_min,
    overflow, triggered_at, triggered, no_of_values, no_of_samples_aggreate)
  if number_written_to_buffer == 0
    error("ps3000 Error: Parameter Out Of Range")
  end
  return (number_written_to_buffer,overflow[],triggered_at[],triggered[]==0?false:true)
end

                                     