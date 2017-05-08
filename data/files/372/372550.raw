export FT_Write

function FT_Write(ft_handle::UInt32, stringtowrite::ASCIIString)
  bytestowrite = Culong(length(stringtowrite))
  byteswritten = Ref{Culong}()
  buffer = Array(UInt8,bytestowrite)
  for (pos,char) in enumerate(stringtowrite)
    buffer[pos] = char
  end
  ft_status = ccall((:FT_Write, d2xx),
                     Culong,
                     (Culong, Ptr{UInt8}, Culong, Ref{Culong}),
                     ft_handle, buffer, bytestowrite, byteswritten)
  checkstatus(ft_status)
  return byteswritten[]
end
