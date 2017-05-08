# ps3000_get_streaming_values.jl

export ps3000_get_streaming_values

immutable StreamingBuffer
  start_time   :: Float64
  buffer_a_max :: Array{Int16,1}
  buffer_a_mim :: Array{Int16,1}
  buffer_b_max :: Array{Int16,1}
  buffer_b_mim :: Array{Int16,1}
  buffer_c_max :: Array{Int16,1}
  buffer_c_mim :: Array{Int16,1}
  buffer_d_max :: Array{Int16,1}
  buffer_d_mim :: Array{Int16,1}
  overflow     :: Int16
  triggered_at :: Uint32
  function StreamingBuffer(length)
    new(0.0,Array(Int16,length),Array(Int16,length),Array(Int16,length),Array(Int16,length),
      Array(Int16,length),Array(Int16,length),Array(Int16,length),Array(Int16,length),0,0)
  end
end

function ps3000_get_streaming_values( handle       :: Int16,
                                      buffer       :: StreamingBuffer
                                      no_of_values :: UInt32
                                      no_of_samples_per_aggreate :: UInt32)
  @assert length(buffer.buffer_a_max)>=no_of_values  # make sure buffer is big enough


                                     