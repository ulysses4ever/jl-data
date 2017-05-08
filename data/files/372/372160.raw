# ft_getvidpid.jl
export ft_getvidpid

function ft_getvidpid()
  vid = Ref{Cuint}()
  pid = Ref{Cuint}()
  ft_status = ccall((:FT_GetVIDPID, d2xx),
                     Cuint,
                     (Ref{Cuint}, Ref{Cuint}),
                      vid, pid)
  checkstatus(ft_status)
  return vid[], pid[]
end