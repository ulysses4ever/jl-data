# ps3000_get_values.jl

export ps3000_get_values!

immutable ValueBuffer
  a :: Array{Int16,1}
  b :: Array{Int16,1}
  c :: Array{Int16,1}
  d :: Array{Int16,1}
  ValueBuffer(length) = new(Array(Int16,length),Array(Int16,length),
                            Array(Int16,length),Array(Int16,length))
end

function ps3000_get_values!(handle       :: Int16,
                            buffer       :: ValueBuffer, 
                            no_of_values)
  overflow = Ref{Int16}  # bitfield, see doc
  values_per_channel_retruned = ccall((:ps3000_get_values, ps3000driver),Int32,
    (Int16,
      Ptr{Int16}, Ptr{Int16}, Ptr{Int16}, Ptr{Int16},
      Ref{Int16}, Int32),
     handle,
     buffer.a, buffer.b, buffer.c, buffer.d,
     overflow, no_of_values)
  if values_per_channel_retruned == 0
    error("ps3000 Error: Parameter Out Of Range")
  end
  return (values_per_channel_returned, overflow[])
end
