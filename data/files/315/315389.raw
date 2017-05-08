export ft_ee_uaread!

function ft_ee_uaread!(ft_handle::Culong, buffer::Array{UInt8,1})
  len = length(buffer)
  bytesread = Ref{Cuint}()
  ft_status = ccall((:FT_EE_UARead, d2xx),
                     Cuint,
                     (Culong, Ptr{UInt8}, Cuint, Ref{Cuint}),
                     ft_handle, buffer, len, bytesread)
  checkstatus(ft_status)
  return bytesread[]
end