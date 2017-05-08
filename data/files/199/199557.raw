# ps3000_get_times_and_values.jl

export ps3000_get_times_and_values!, TimesAndValuesBuffer

immutable TimesAndValuesBuffer
  times  :: Array{Int32,1}
  a      :: Array{Int16,1}
  b      :: Array{Int16,1}
  c      :: Array{Int16,1}
  d      :: Array{Int16,1}
  TimesAndValuesBuffer(length) = 
    new(Array(Int32,length), Array(Int16,length), Array(Int16,length),
    Array(Int16,length), Array(Int16,length))
end


function ps3000_get_times_and_values!(handle       :: Int16,
                                     buffer       :: TimesAndValuesBuffer,
                                     time_units,
                                     no_of_values)
  overflow = Ref{Int16}()
  number_of_data_values_per_channel = ccall((:ps3000_get_times_and_values, ps3000driver),Int32,
    (Int16,
     Ptr{Int32}, Ptr{Int16}, Ptr{Int16}, Ptr{Int16}, Ptr{Int16},
     Ref{Int16}, Int16, Int32),
    handle,
    buffer.times, buffer.a, buffer.b, buffer.c, buffer.d,
    overflow, time_units, no_of_values)
  if number_of_data_values_per_channel == 0
    error("ps3000 Error: one or more of the parameters are out of range or the times will overflow with the time_units requested")
  end
  return (number_of_data_values_per_channel, overflow[])
end
