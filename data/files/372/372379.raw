export FT_CreateDeviceInfoList

function FT_CreateDeviceInfoList()
  lpdwNumDevs = Ref{Cuint}()
  ft_status = ccall((:FT_CreateDeviceInfoList, d2xx),
                      Cuint,
                      (Ref{Cuint},),
                      lpdwNumDevs)
  checkstatus(ft_status)
  return lpdwNumDevs[]
end