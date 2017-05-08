export FT_Open

function FT_Open(iDevice::Integer)
  ft_handle = Ref{Cuint}()
  ft_status = ccall((:FT_Open, d2xx),
                      Cuint,
                      (Cuint,Ref{Cuint}),
                      iDevice,ft_handle)
  checkstatus(ft_status)
  return ft_handle[]
end