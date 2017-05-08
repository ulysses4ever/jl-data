export  FT_GetComPortNumber

function FT_GetComPortNumber(ft_handle::UInt32)
  comportnumber = Ref{Cuint}()
  ft_status = ccall((:FT_GetComPortNumber, d2xx),
                     Cuint,
                     (Cuint, Ref{Cuint}),
                     ft_handle, comportnumber)
  checkstatus(ft_status)
  return convert(Int32, comportnumber[])
end