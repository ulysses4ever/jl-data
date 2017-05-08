export FT_StopInTask

function FT_StopInTask(ft_handle::UInt32)
  ft_status = ccall((:FT_StopInTask, d2xx),Cuint,(Cuint,),ft_handle)
  checkstatus(ft_status)
  return nothing
end