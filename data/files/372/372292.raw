export FT_EE_UARead!

function FT_EE_UARead!(ft_handle::UInt32, buffer::Array{UInt8,1})
  len = length(buffer)
  bytesread = Ref{Culong}()
  ft_status = ccall((:FT_EE_UARead, d2xx),
                     Culong,
                     (Culong, Ptr{UInt8}, Culong, Ref{Culong}),
                     ft_handle, buffer, len, bytesread)
  checkstatus(ft_status)
  return convert(UInt32, bytesread[])
end