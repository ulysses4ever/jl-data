export FT_Reload

function FT_Reload(vid::Integer, pid::Integer)
  ft_status = ccall((:FT_Reload, "ftd2xx.dll"),
                     Culong,
                     (Cuint, Cuint),
                     vid, pid)
  checkstatus(ft_status)
  return nothing
end