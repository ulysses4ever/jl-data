export FT_Write

function FT_Write(ft_handle::Culong, stringtowrite::ASCIIString)
  bytestowrite = Cuint(length(stringtowrite))
  byteswritten = Ref{Cuint}()
  buffer = Array(UInt8,bytestowrite)
  for (pos,char) in enumerate(stringtowrite)
    buffer[pos] = char
  end
  ft_status = ccall((:FT_Write, d2xx),
                     Cuint,
                     (Culong, Ptr{UInt8}, Cuint, Ref{Cuint}),
                     ft_handle, buffer, bytestowrite, byteswritten)
  checkstatus(ft_status)
  return byteswritten[]
end
