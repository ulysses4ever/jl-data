export FT_EE_UAWrite

function FT_EE_UAWrite(ft_handle::UInt32, buffer::Array{UInt8,1})
  len = length(buffer)
  ft_status = ccall((:FT_EE_UAWrite, d2xx),
                     Culong,
                     (Culong, Ptr{UInt8}, Culong),
                     ft_handle, buffer, len)
  checkstatus(ft_status)
  return nothing
end