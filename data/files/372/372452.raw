export FT_Purge

function FT_Purge(ft_handle::UInt32, mask::Integer)
  ft_status = ccall((:FT_Purge, "ftd2xx.dll"),
                     Culong,
                     (Culong, Culong),
                     ft_handle, mask)
  checkstatus(ft_status)
  return nothing
end