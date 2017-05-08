export ft_ee_uasize

function ft_ee_uasize(ft_handle::Culong)
  eesize = Ref{Cuint}()
  ft_status = ccall((:ft_ee_uasize, d2xx),
                     Cuint,
                     (Culong, Ref{Cuint}),
                     ft_handle, eesize)
  checkstatus(ft_status)
  return eesize[]
end