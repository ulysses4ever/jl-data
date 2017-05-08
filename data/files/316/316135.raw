module FTD2XX

export FT_CreateDeviceInfoList, FT_GetDeviceInfoList

type Ftd2xxError <: Exception 
  ft_status :: Uint
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
  ftdeviceinfolist = Array{_ft_device_list_info_node,1}(lpdwNumDevs)
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
    serialnumber = node.sn1  * node.sn2  * node.sn3  * node.sn4  *
                   node.sn5  * node.sn6  * node.sn7  * node.sn8  *
                   node.sn9  * node.sn10 * node.sn11 * node.sn12 *
                   node.sn13 * node.sn14 * node.sn15 * node.sn16
    description = 
    node.d1  * node.d2  * node.d3  * node.d4  * 
    node.d5  * node.d6  * node.d7  * node.d8  *
    node.d9  * node.d10 * node.d11 * node.d12 *
    node.d13 * node.d14 * node.d15 * node.d16 *
    node.d17 * node.d18 * node.d19 * node.d20 *
    node.d21 * node.d22 * node.d23 * node.d24 *
    node.d25 * node.d26 * node.d27 * node.d28 *
    node.d29 * node.d30 * node.d31 * node.d32 *
    node.d33 * node.d34 * node.d35 * node.d36 *
    node.d37 * node.d38 * node.d39 * node.d40 *
    node.d41 * node.d42 * node.d43 * node.d44 *        
    node.d45 * node.d46 * node.d47 * node.d48 *    
    node.d49 * node.d50 * node.d51 * node.d52
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
