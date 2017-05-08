export FT_Read!

function FT_Read!(ft_handle::Culong,
                 buffer::Array{UInt8},
                 bytestoread::Integer)
  bytesreturned = Ref{Cuint}()
  ft_status = ccall((:FT_Read, d2xx),
                      Cuint,
                      (Culong, Ptr{UInt8}, Cuint, Ref{Cuint}),
                      ft_handle, buffer, bytestoread, bytesreturned)
  checkstatus(ft_status) 
  return (bytesreturned[])
end
