# FT_GetVIDPID.jl
export FT_GetVIDPID

function FT_GetVIDPID()
  vid = Ref{Culong}()
  pid = Ref{Culong}()
  ft_status = ccall((:FT_GetVIDPID, "ftd2xx.dll"),
                     Culong,
                     (Ref{Culong}, Ref{Culong}),
                      vid, pid)
  checkstatus(ft_status)
  return (convert(UInt32, vid[]), convert(UInt32, pid[]))
end