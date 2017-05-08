export FT_WriteEE

function FT_WriteEE(ft_handle::UInt32, wordoffset::Integer, value::UInt16)
  @assert wordoffset >= 0
  ft_status = ccall((:FT_WriteEE, d2xx),
                     Culong,
                     (Culong, Culong, Cushort),
                     ft_handle, wordoffset, value)
  checkstatus(ft_status)
  return nothing
end 