export ft_reload

function ft_reload(vid::Integer, pid::Integer)
  ft_status = ccall((:FT_Reload, d2xx),
                     Cuint,
                     (Cuint, Cuint),
                     vid, pid)
  checkstatus(ft_status)
  return nothing
end