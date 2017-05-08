export  ft_getcomportnumber

function ft_getcomportnumber(ft_handle::Culong)
  comportnumber = Ref{Cuint}()
  ft_status = ccall((:FT_GetComPortNumber, d2xx),
                     Cuint,
                     (Culong, Ref{Cuint}),
                     ft_handle, comportnumber)
  checkstatus(ft_status)
  return comportnumber[]
end