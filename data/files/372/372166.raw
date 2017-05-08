export ft_read!

function ft_read!(ft_handle::Culong,
                 buffer::Array{UInt8,1},
                 bytestoread::Integer = length(buffer))
  bytesreturned = Ref{Cuint}()
  ft_status = ccall((:FT_Read, d2xx),
                      Cuint,
                      (Culong, Ptr{UInt8}, Cuint, Ref{Cuint}),
                      ft_handle, buffer, bytestoread, bytesreturned)
  checkstatus(ft_status) 
  return (bytesreturned[])
end
