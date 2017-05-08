module FTD2XX

export FT_CreateDeviceInfoList, FT_GetDeviceInfoList

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

function FT_CreateDeviceInfoList()
  lpdwNumDevs = Ref{Culong}()
  ft_status = ccall((:FT_CreateDeviceInfoList, "ftd2xx.dll"),
                      Culong,
                      (Ref{Culong},),
                      lpdwNumDevs)
  if ft_status > 0
    throw(Ftd2xxError(ft_status))
  end
  return lpdwNumDevs[]
end

function FT_GetDeviceInfoList(lpdwNumDevs)
  ftdeviceinfolist = Array(_ft_device_list_info_node,lpdwNumDevs)
  n = Ref{Culong}(lpdwNumDevs)
  ft_status = ccall((:FT_GetDeviceInfoList, "ftd2xx.dll"),
                      Culong,
                      (Ptr{_ft_device_list_info_node},Ref{Culong}),
                      ftdeviceinfolist,n)
  if ft_status > 0
    throw(Ftd2xxError(ft_status))
  end
  infonodearray = InfoNode[]
  sizehint!(infonodearray,lpdwNumDevs)
  for node in ftdeviceinfolist
    flags = node.Flags 
    devicetype = node.Type
    id = node.ID 
    locid = node.LocId
    sn = Array(UInt8,16)
    for i in 1:16 # 5:21
      sn[i] = node.(i+4)
    end
    endofstring = findfirst(sn,0)-1
    serialnumber = convert(ASCIIString,sn[1:endofstring])
    d = Array(UInt8,64)
    for i in 1:64 # 22:86
      d[i] = node.(i+21)
    end
    endofstring = findfirst(d,0)-1
    description = convert(ASCIIString,d[1:endofstring])
    handle = node.FT_HANDLE 
    push!(infonodearray,InfoNode(flags,devicetype,id,locid,serialnumber,
                                 description,handle))
  end
  return infonodearray
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
