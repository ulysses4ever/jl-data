export ft_write

function ft_write(ft_handle::Culong,
                  buffer::Array{UInt8,1},
                  bytestowrite::Integer = length(buffer))
  byteswritten = Ref{Cuint}()
  ft_status = ccall((:FT_Write, d2xx),
                     Cuint,
                     (Culong, Ptr{UInt8}, Cuint, Ref{Cuint}),
                     ft_handle, buffer, bytestowrite, byteswritten)
  checkstatus(ft_status)
  return byteswritten[]
end
