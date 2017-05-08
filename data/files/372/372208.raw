export ft_setresetpiperetrycount

function ft_setresetpiperetrycount(ft_handle::Culong, count::Integer)
  ft_status = ccall((:FT_SetResetPipeRetryCount, d2xx),
                     Cuint,
                     (Culong, Cuint),
                     ft_handle, count)
  checkstatus(ft_status)
  return nothing
end