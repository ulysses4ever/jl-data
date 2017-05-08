export FT_GetDeviceInfo

function FT_GetDeviceInfo(ft_handle::UInt32)
  ft_device = Ref{Culong}() # see ftdevicetypedict
  id = Ref{Culong}()
  serialnumber = Array(UInt8,17)
  description = Array(UInt8,65)
  serialnumber[17] = 0x00
  description[65] = 0x00
  ft_status = ccall((:FT_GetDeviceInfo, "ftd2xx.dll"),
                     Culong,
                     (Culong, Ref{Culong}, Ref{Culong}, Ptr{UInt8}, Ptr{UInt8}, Ptr{Void}),
                     ft_handle, ft_device, id, serialnumber, description, C_NULL)
  sn = convert(ASCIIString,serialnumber[1:findfirst(serialnumber,0)-1])
  d = convert(ASCIIString,description[1:findfirst(description,0)-1])
  checkstatus(ft_status)
  return (ft_device[], id[], sn, d)
end 