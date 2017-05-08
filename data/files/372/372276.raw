# FT_SetVIDPID
export FT_SetVIDPID

function FT_SetVIDPID(vid::Integer, pid::Integer)
  @assert vid>=0
  @assert pid>=0
  ft_status = ccall((:FT_SetVIDPID, d2xx),
                     Culong,
                     (Culong, Culong),
                     vid, pid)
  checkstatus(ft_status)
  return nothing
end