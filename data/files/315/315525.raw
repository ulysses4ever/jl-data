# FT_GetVIDPID.jl
export FT_GetVIDPID

function FT_GetVIDPID()
  vid = Ref{Cuint}()
  pid = Ref{Cuint}()
  ft_status = ccall((:FT_GetVIDPID, d2xx),
                     Cuint,
                     (Ref{Cuint}, Ref{Cuint}),
                      vid, pid)
  checkstatus(ft_status)
  return (convert(UInt32, vid[]), convert(UInt32, pid[]))
end