module FTD2XX

export FT_CreateDeviceInfoList, FT_GetDeviceInfoList, FT_Open, FT_Description
export FT_SerialNumber, FT_OpenEx, FT_Close, FT_Read, FT_Write, FT_SetBaudRate
export FT_SetDataCharacteristics, FT_SetTimeouts

export FT_BITS_8, FT_BITS_7, FT_STOP_BITS_1, FT_STOP_BITS_2
export FT_PARITY_NONE, FT_PARITY_ODD, FT_PARITY_EVEN
export FT_PARITY_MARK, FT_PARITY_SPACE

type Ftd2xxError <: Exception 
  ft_status :: UInt64
end
function Base.showerror(io::IO, e::Ftd2xxError)
  fts = e.ft_status
  errortext = get(ftstatusdict,fts,"Code Not Found")
  print(io, "Ftd2xxError: FT_STATUS=$(fts), $errortext")
end

type InfoNode
  flags         :: UInt32
  devicetype    :: UInt32
  id            :: UInt32
  locid         :: UInt32
  serialnumber  :: ASCIIString
  description   :: ASCIIString
  handle        :: UInt32
end

include("Types_and_Constants.jl")

function checkstatus(ft_status::Culong)
  if ft_status != 0
    throw(Ftd2xxError(ft_status))
  end
  return 0
end

function FT_CreateDeviceInfoList()
  lpdwNumDevs = Ref{Culong}()
  ft_status = ccall((:FT_CreateDeviceInfoList, "ftd2xx.dll"),
                      Culong,
                      (Ref{Culong},),
                      lpdwNumDevs)
  checkstatus(ft_status)
  return lpdwNumDevs[]
end

function FT_GetDeviceInfoList(lpdwNumDevs)
  ftdeviceinfolist = Array(_ft_device_list_info_node,lpdwNumDevs)
  n = Ref{Culong}(lpdwNumDevs)
  ft_status = ccall((:FT_GetDeviceInfoList, "ftd2xx.dll"),
                      Culong,
                      (Ptr{_ft_device_list_info_node},Ref{Culong}),
                      ftdeviceinfolist,n)
  checkstatus(ft_status)
  infonodearray = InfoNode[]
  sizehint!(infonodearray,lpdwNumDevs)
  for node in ftdeviceinfolist
    flags = node.Flags 
    devicetype = node.Type
    id = node.ID 
    locid = node.LocId
    sn = Array(UInt8,16)
    for i in 1:16 # 5:20
      sn[i] = node.(i+4)
    end
    endofstring = findfirst(sn,0)-1
    serialnumber = convert(ASCIIString,sn[1:endofstring])
    d = Array(UInt8,64)
    for i in 1:64 # 21:85
      d[i] = node.(i+20)
    end
    endofstring = findfirst(d,0)-1
    description = convert(ASCIIString,d[1:endofstring])
    handle = node.FT_HANDLE 
    push!(infonodearray,InfoNode(flags,devicetype,id,locid,serialnumber,
                                 description,handle))
  end
  return infonodearray
end

function FT_Open(iDevice::Integer)
  ft_handle = Ref{Culong}()
  ft_status = ccall((:FT_Open, "ftd2xx.dll"),
                      Culong,
                      (Culong,Ref{Culong}),
                      iDevice,ft_handle)
  checkstatus(ft_status)
  return ft_handle[]
end

immutable FT_Description 
  d :: Array{UInt8,1}
  function FT_Description(s :: ASCIIString)
    description = Array(UInt8,64)
    if length(s) < 64
      for (pos,char) in enumerate(s)
        description[pos] = Int(char)
      end
      description[length(s)+1] = 0
    else
      error("length(desctiption) must be < 64")
    end
    new(description)
  end
end

immutable FT_SerialNumber 
  sn :: Array{UInt8,1}
  function FT_SerialNumber(s :: ASCIIString)
    serialnumber = Array(UInt8,16)
    if length(s) < 16
      for (pos,char) in enumerate(s)
        serialnumber[pos] = Int(char)
      end
      serialnumber[length(s)+1] = 0
    else
      error("length(serialnumber) must be < 16")
    end
    new(serialnumber)
  end
end

function FT_OpenEx(location :: Unsigned)
  ft_handle = Ref{Culong}()
  ft_status = ccall((:FT_OpenEx, "ftd2xx.dll"),
                      Culong,
                      (Ref{Culong},Culong,Ref{Culong}),
                      location,FT_OPEN_BY_LOCATION,ft_handle)
  checkstatus(ft_status)
  return ft_handle[]
end

function FT_OpenEx(serialnumber :: FT_SerialNumber)
  ft_handle = Ref{Culong}()
  ft_status = ccall((:FT_OpenEx, "ftd2xx.dll"),
                      Culong,
                      (Ptr{UInt8},Culong,Ref{Culong}),
                      serialnumber.sn,FT_OPEN_BY_SERIAL_NUMBER,ft_handle)
  checkstatus(ft_status)
  return ft_handle[]
end

function FT_OpenEx(description :: FT_Description)
  ft_handle = Ref{Culong}()
  ft_status = ccall((:FT_OpenEx, "ftd2xx.dll"),
                      Culong,
                      (Ptr{UInt8},Culong,Ref{Culong}),
                      description.d,FT_OPEN_BY_DESCRIPTION,ft_handle)
  checkstatus(ft_status)
  return ft_handle[]
end

function FT_Close(ft_handle :: UInt32)
  ft_status = ccall((:FT_Close, "ftd2xx.dll"),
                      Culong,
                      (Culong,),
                      ft_handle)
  checkstatus(ft_status)
  return nothing
end

function FT_Read(ft_handle::UInt32, bytestoread::Integer)
  buffer = Array(UInt8,bytestoread)
  bytesreturned = Ref{Culong}()
  ft_status = ccall((:FT_Read, "ftd2xx.dll"),
                      Culong,
                      (Culong, Ptr{UInt8}, Culong, Ref{Culong}),
                      ft_handle, buffer, bytestoread, bytesreturned)
  checkstatus(ft_status) 
  return (bytesreturned[], convert(ASCIIString,buffer[1:bytesreturned[]]))
end

function FT_Write(ft_handle::UInt32, stringtowrite::ASCIIString)
  bytestowrite = Culong(length(stringtowrite))
  byteswritten = Ref{Culong}()
  buffer = Array(UInt8,bytestowrite)
  for (pos,char) in enumerate(stringtowrite)
    buffer[pos] = char
  end
  ft_status = ccall((:FT_Write, "ftd2xx.dll"),
                     Culong,
                     (Culong, Ptr{UInt8}, Culong, Ref{Culong}),
                     ft_handle, buffer, bytestowrite, byteswritten)
  checkstatus(ft_status)
  return byteswritten[]
end

function FT_SetBaudRate(ft_handle::UInt32, baud::Integer)
  ft_status = ccall((:FT_SetBaudRate, "ftd2xx.dll"),
                     Culong,
                     (Culong,Culong),
                     ft_handle,baud)
  checkstatus(ft_status)
  return nothing
end

function FT_SetDataCharacteristics(ft_handle::UInt32, 
                                   wordlength::Integer,
                                   stopbits::Integer,
                                   parity::Integer)
  @assert (wordlength==FT_BITS_8) || (wordlength==FT_BITS_7) "invalid word length"
  @assert (stopbits==FT_STOP_BITS_1) || (stopbits==FT_STOP_BITS_2) "invalid stop bits"
  @assert parity == FT_PARITY_NONE || parity == FT_PARITY_ODD ||
          parity == FT_PARITY_EVEN || parity == FT_PARITY_MARK ||
          parity == FT_PARITY_SPACE "invalid parity"
  ft_status = ccall((:FT_SetDataCharacteristics, "ftd2xx.dll"),
                     Culong,
                     (Culong, Cuchar, Cuchar, Cuchar),
                     ft_handle, wordlength, stopbits, parity)
  checkstatus(ft_status)
  return nothing
end

function FT_SetTimeouts(ft_handle::UInt32,
                         readtimeout::Integer,
                         writetimeout::Integer)
  ft_status = ccall((:FT_SetTimeouts, "ftd2xx.dll"),
                     Culong,
                     (Culong, Culong, Culong),
                     ft_handle, readtimeout, writetimeout)
  checkstatus(ft_status)
  return nothing
end 

function FT_SetFlowControl(ft_handle::UInt32, flowcontrol::Integer,
                           xon::UInt8 = 0x11, xoff::UInt8 = 0x13)
  @assert flowcontrol == FT_FLOW_NONE ||
          flowcontrol == FT_FLOW_RTS_CTS ||
          flowcontrol == FT_FLOW_DTR_DSR ||
          flowcontrol == FT_FLOW_XON_XOFF "invalid flow control"
  ft_status = ccall((:FT_SetFlowControl, "ftd2xx.dll"),
                     Culong,
                     (Culong, Cushort, Cuchar, Cuchar),
                     ft_handle, flowcontrol, xon, xoff)
  checkstatus(ft_status)
  return nothing
end 

function FT_SetDtr(ft_handle::UInt32)
  ft_status = ccall((:FT_SetDtr, "ftd2xx.dll"),Culong,(Culong,),ft_handle)
  checkstatus(ft_status)
  return nothing
end  

function FT_ClrDtr(ft_handle::UInt32)
  ft_status = ccall((:FT_ClrDtr, "ftd2xx.dll"),Culong,(Culong,),ft_handle)
  checkstatus(ft_status)
  return nothing
end

function FT_SetRts(ft_handle::UInt32)
  ft_status = ccall((:FT_SetRts, "ftd2xx.dll"),Culong,(Culong,),ft_handle)
  checkstatus(ft_status)
  return nothing
end  

function FT_ClrRts(ft_handle::UInt32)
  ft_status = ccall((:FT_ClrRts, "ftd2xx.dll"),Culong,(Culong,),ft_handle)
  checkstatus(ft_status)
  return nothing
end

function FT_GetModemStatus(ft_handle::UInt32)
  modemstatus = Ref{Culong}()
  ft_status = ccall((:FT_GetModemStatus, "ftd2xx.dll"),
                     Culong,
                     (Culong, Ref{Culong}),
                     ft_handle, modemstatus)
  checkstatus(ft_status)
  return convert(UInt32,modemstatus[])
end 

function FT_GetQueueStatus(ft_handle::UInt32)
  amountinrxqueue = Ref{Culong}()
  ft_status = ccall((:FT_GetQueueStatus, "ftd2xx.dll"),
                     Culong,
                     (Culong, Ref{Culong}),
                     ft_handle, amountinrxqueue)
  checkstatus(ft_status)
  return convert(UInt32, amountinrxqueue[])
end 

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
                     ft_handle, ft_device, id, serialnumber, description, Void)
  sn = convert(ASCIIString,serialnumber[1:findfirst(serialnumber,0)-1])
  d = convert(ASCIIString,description[1:findfirst(description,0)-1])
  checkstatus(ft_status)
  return (ft_device[], id[], sn, d)
end 

function FT_GetDriverVersion(ft_handle::UInt32)
  driverversion = Ref{Culong}()
  ft_status = ccall((:FT_GetDriverVersion, "ftd2xx.dll"),
                     Culong,
                     (Culong, Ref{Culong}),
                     ft_handle, driverversion)
  checkstatus(ft_status)
  build = (driverversion[] & 0x000000ff)
  minor = (driverversion[] & 0x0000ff00)>>8
  major = (driverversion[] & 0x00ff0000)>>16
  return VersionNumber(major,minor,build)
end

function FT_GetLibraryVersion()
  dllversion = Ref{Culong}()
  ft_status = ccall((:FT_GetLibraryVersion, "ftd2xx.dll"),
                     Culong,
                     (Culong, Ref{Culong}),
                     ft_handle, dllversion)
  checkstatus(ft_status)
  build = (driverversion[] & 0x000000ff)
  minor = (driverversion[] & 0x0000ff00)>>8
  major = (driverversion[] & 0x00ff0000)>>16
  return VersionNumber(major,minor,build)
end

function FT_GetComPortNumber(ft_handle::UInt32)
  comportnumber = Ref{Culong}()
  ft_status = ccall((:FT_GetComPortNumber, "ftd2xx.dll"),
                     Culong,
                     (Culong, Ref{Culong}),
                     ft_handle, comportnumber)
  checkstatus(ft_status)
  return convert(Int32, comportnumber[])
end

function FT_GetStatus(ft_handle::UInt32)
  amountinrxqueue = Ref{Culong}()
  amountintxqueue = Ref{Culong}()
  eventstatus = Ref{Culong}()
  ft_status = ccall((:FT_GetStatus, "ftd2xx.dll"),
                     Culong,
                     (Culong, Ref{Culong}),
                     ft_handle, comportnumber)
  checkstatus(ft_status)
  return (convert(Int32,amountinrxqueue[]),
          convert(Int32,amountintxqueue[]),convert(Int32,eventstatus))
end

#=
function FT_SetEventNotification(ft_handle::UInt32, eventmask::Integer)

What do I do here ????

=#







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

ftstatusdict = Dict(
  FT_OK                           => "FT_OK",
  FT_INVALID_HANDLE               => "FT_INVALID_HANDLE",
  FT_DEVICE_NOT_FOUND             => "FT_DEVICE_NOT_FOUND",
  FT_DEVICE_NOT_OPENED            => "FT_DEVICE_NOT_OPENED",
  FT_IO_ERROR                     => "FT_IO_ERROR",
  FT_INSUFFICIENT_RESOURCES       => "FT_INSUFFICIENT_RESOURCES",
  FT_INVALID_PARAMETER            => "FT_INVALID_PARAMETER",
  FT_INVALID_BAUD_RATE            => "FT_INVALID_BAUD_RATE",
  FT_DEVICE_NOT_OPENED_FOR_ERASE  => "FT_DEVICE_NOT_OPENED_FOR_ERASE",
  FT_DEVICE_NOT_OPENED_FOR_WRITE  => "FT_DEVICE_NOT_OPENED_FOR_WRITE",
  FT_FAILED_TO_WRITE_DEVICE       => "FT_FAILED_TO_WRITE_DEVICE",
  FT_EEPROM_READ_FAILED           => "FT_EEPROM_READ_FAILED",
  FT_EEPROM_WRITE_FAILED          => "FT_EEPROM_WRITE_FAILED",
  FT_EEPROM_ERASE_FAILED          => "FT_EEPROM_ERASE_FAILED",
  FT_EEPROM_NOT_PRESENT           => "FT_EEPROM_NOT_PRESENT",
  FT_EEPROM_NOT_PROGRAMMED        => "FT_EEPROM_NOT_PROGRAMMED",
  FT_INVALID_ARGS                 => "FT_INVALID_ARGS",
  FT_NOT_SUPPORTED                => "FT_NOT_SUPPORTED",
  FT_OTHER_ERROR                  => "FT_OTHER_ERROR")

end # module
