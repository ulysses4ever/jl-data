# ps3000_save_streaming_data.jl

export ps3000_save_streaming_data

function ps3000_save_streaming_data(handle :: Int16,
                                    callback :: Ptr{Void},
                                    data_buffer_size :: Int16 = 0x4000)
  buffer = Array(Int16,data_buffer_size)
  undefined_return_value = ccall((:ps3000_save_streaming_data, ps3000driver), Int16,
    (Int16, Ptr{Void}, Ptr{Int16}, Int16),
    handle, callback, buffer, data_buffer_size)
  return nothing
end