export FT_SetBaudRate

function FT_SetBaudRate(ft_handle::Culong, baud::Integer)
  ft_status = ccall((:FT_SetBaudRate, d2xx),
                     Cuint,
                     (Culong,Cuint),
                     ft_handle,baud)
  checkstatus(ft_status)
  return nothing
end