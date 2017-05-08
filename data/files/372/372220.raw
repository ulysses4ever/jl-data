# ft_setvidpid
export ft_setvidpid

function ft_setvidpid(vid::Integer, pid::Integer)
  @assert vid>=0
  @assert pid>=0
  ft_status = ccall((:FT_SetVIDPID, d2xx),
                     Cuint,
                     (Cuint, Cuint),
                     vid, pid)
  checkstatus(ft_status)
  return nothing
end