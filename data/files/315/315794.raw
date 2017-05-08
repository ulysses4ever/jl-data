export FT_GetDeviceInfo
export FT_DEVICE_232BM, FT_DEVICE_232AM, FT_DEVICE_100AX
export FT_DEVICE_UNKNOWN, FT_DEVICE_2232C, FT_DEVICE_232R
export FT_DEVICE_2232H, FT_DEVICE_4232H, FT_DEVICE_232H
export FT_DEVICE_X_SERIES
export ftdevicetypedict

#FT_DEVICE (DWORD) 
const FT_DEVICE_232BM = 0
const FT_DEVICE_232AM = 1
const FT_DEVICE_100AX = 2
const FT_DEVICE_UNKNOWN = 3
const FT_DEVICE_2232C = 4
const FT_DEVICE_232R = 5
const FT_DEVICE_2232H = 6
const FT_DEVICE_4232H = 7
const FT_DEVICE_232H = 8
const FT_DEVICE_X_SERIES = 9

ftdevicetypedict = Dict(
  FT_DEVICE_232BM => "232BM",
  FT_DEVICE_232AM => "232AM",
  FT_DEVICE_100AX => "100AX",
  FT_DEVICE_UNKNOWN => "UNKNOWN",
  FT_DEVICE_2232C => "2232C",
  FT_DEVICE_232R => "232R",
  FT_DEVICE_2232H => "2232H",
  FT_DEVICE_4232H => "4232H",
  FT_DEVICE_232H => "232H",
  FT_DEVICE_X_SERIES => "X_SERIES")

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