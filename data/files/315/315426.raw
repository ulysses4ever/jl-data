export ft_getdeviceinfo

include("FT_DEVICE.jl")

function ft_getdeviceinfo(ft_handle::Culong)
  ft_device = Ref{Cuint}() # see ftdevicetypedict
  id = Ref{Cuint}()
  serialnumber = Array(UInt8,17)
  description = Array(UInt8,65)
  serialnumber[17] = 0x00
  description[65] = 0x00
  ft_status = ccall((:FT_GetDeviceInfo, d2xx),
                     Cuint,
                     (Culong, Ref{Cuint}, Ref{Cuint}, Ptr{UInt8}, Ptr{UInt8}, Ptr{Void}),
                     ft_handle, ft_device, id, serialnumber, description, C_NULL)
  sn = convert(ASCIIString,serialnumber[1:findfirst(serialnumber,0)-1])
  d = convert(ASCIIString,description[1:findfirst(description,0)-1])
  checkstatus(ft_status)
  return (ft_device[], id[], sn, d)
end 