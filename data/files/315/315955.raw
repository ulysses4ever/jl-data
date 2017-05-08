export FT_SetDeadmanTimeout

function FT_SetDeadmanTimeout(ft_handle::UInt32, deadmantimeout::Integer = 5000)
  ft_status = ccall((:FT_SetDeadmanTimeout, d2xx),
                     Cuint,
                     (Cuint, Cuint),
                     ft_handle, deadmantimeout)
  checkstatus(ft_status)
  return nothing
end 