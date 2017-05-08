export ft_resetdevice

function ft_resetdevice(ft_handle::Culong)
  ft_status = ccall((:FT_ResetDevice, d2xx),Cuint,(Culong,),ft_handle)
  checkstatus(ft_status)
  return nothing
end
