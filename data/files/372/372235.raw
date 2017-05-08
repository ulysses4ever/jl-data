export ft_eraseee

function ft_eraseee(ft_handle::Culong)
  ft_status = ccall((:FT_EraseEE, d2xx),Cuint,(Culong, ),ft_handle)
  checkstatus(ft_status)
  return nothing
end 