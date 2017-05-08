export ft_open

function ft_open(iDevice::Integer)
  ft_handle = Ref{Culong}()
  ft_status = ccall((:FT_Open, d2xx),
                      Cuint,
                      (Cuint,Ref{Culong}),
                      iDevice,ft_handle)
  checkstatus(ft_status)
  return ft_handle[]
end