export ft_createdeviceinfolist

function ft_createdeviceinfolist()
  lpdwNumDevs = Ref{Cuint}()
  ft_status = ccall((:FT_CreateDeviceInfoList, d2xx),
                      Cuint,
                      (Ref{Cuint},),
                      lpdwNumDevs)
  checkstatus(ft_status)
  return lpdwNumDevs[]
end
