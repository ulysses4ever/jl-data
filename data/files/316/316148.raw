module FTD2XX

export FT_CreateDeviceInfoList, FT_GetDeviceInfoList, FT_Open, FT_Description
export FT_SerialNumber, FT_OpenEx, FT_Close, FT_Read, FT_Write, FT_SetBaudRate

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

function FT_Read(ft_handle::UInt32, bytestoread::Unsigned)
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






ftstatusdict = Dict(
  0   => "FT_OK",
  1   => "FT_INVALID_HANDLE",
  2   => "FT_DEVICE_NOT_FOUND",
  3   => "FT_DEVICE_NOT_OPENED",
  4   => "FT_IO_ERROR",
  5   => "FT_INSUFFICIENT_RESOURCES",
  6   => "FT_INVALID_PARAMETER",
  7   => "FT_INVALID_BAUD_RATE",
  8   => "FT_DEVICE_NOT_OPENED_FOR_ERASE",
  9   => "FT_DEVICE_NOT_OPENED_FOR_WRITE",
  10  => "FT_FAILED_TO_WRITE_DEVICE",
  11  => "FT_EEPROM_READ_FAILED",
  12  => "FT_EEPROM_WRITE_FAILED",
  13  => "FT_EEPROM_ERASE_FAILED",
  14  => "FT_EEPROM_NOT_PRESENT",
  15  => "FT_EEPROM_NOT_PROGRAMMED",
  16  => "FT_INVALID_ARGS",
  17  => "FT_NOT_SUPPORTED",
  18  => "FT_OTHER_ERROR")

end # module
