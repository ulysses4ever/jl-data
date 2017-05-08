export FT_EraseEE

function FT_EraseEE(ft_handle::UInt32)
  ft_status = ccall((:FT_EraseEE, "ftd2xx.dll"),Culong,(Culong, ),ft_handle)
  checkstatus(ft_status)
  return nothing
end 