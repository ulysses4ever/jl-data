export FT_EE_UAWrite

function FT_EE_UAWrite(ft_handle::Culong, buffer::Array{UInt8,1})
  len = length(buffer)
  ft_status = ccall((:FT_EE_UAWrite, d2xx),
                     Cuint,
                     (Culong, Ptr{UInt8}, Cuint),
                     ft_handle, buffer, len)
  checkstatus(ft_status)
  return nothing
end