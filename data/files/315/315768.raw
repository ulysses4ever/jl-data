export FT_CreateDeviceInfoList

function FT_CreateDeviceInfoList()
  lpdwNumDevs = Ref{Culong}()
  ft_status = ccall((:FT_CreateDeviceInfoList, d2xx),
                      Culong,
                      (Ref{Culong},),
                      lpdwNumDevs)
  checkstatus(ft_status)
  return lpdwNumDevs[]
end