export FT_Reload

function FT_Reload(vid::Integer, pid::Integer)
  ft_status = ccall((:FT_Reload, d2xx),
                     Culong,
                     (Culong, Culong),
                     vid, pid)
  checkstatus(ft_status)
  return nothing
end