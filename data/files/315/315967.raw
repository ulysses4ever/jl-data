export FT_SetResetPipeRetryCount

function FT_SetResetPipeRetryCount(ft_handle::UInt32, count::Integer)
  ft_status = ccall((:FT_SetResetPipeRetryCount, d2xx),
                     Cuint,
                     (Cuint, Cuint),
                     ft_handle, count)
  checkstatus(ft_status)
  return nothing
end