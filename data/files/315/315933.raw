export FT_SetBaudRate

function FT_SetBaudRate(ft_handle::UInt32, baud::Integer)
  ft_status = ccall((:FT_SetBaudRate, d2xx),
                     Culong,
                     (Culong,Culong),
                     ft_handle,baud)
  checkstatus(ft_status)
  return nothing
end