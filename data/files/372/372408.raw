export FT_GetDeviceInfoList
export FT_FLAGS_OPENED

type InfoNode
  flags         :: UInt32
  devicetype    :: UInt32
  id            :: UInt32
  locid         :: UInt32
  serialnumber  :: ASCIIString
  description   :: ASCIIString
  handle        :: Culong
end

function Base.show(io::IO, i::InfoNode)
  println(typeof(i),":")
  f()=@printf(io,"flags = 0x%08x \n",i.flags);f()
  f()=@printf(io,"devicetype = 0x%08x \n",i.devicetype);f()
  f()=@printf(io,"id = 0x%08x \n",i.id);f()
  f()=@printf(io,"locid = 0x%08x \n",i.locid);f()
  println(io,"serialnumber = ",i.serialnumber)
  println(io,"description = ",i.description)
  if Culong == UInt32
    f()=@printf(io,"handle = 0x%08x \n",i.handle);f()
  else
    f()=@printf(io,"handle = 0x%016x \n",i.handle);f()
  end
end

function Base.show(io::IO, a::Array{FTD2XX.InfoNode,1})
  println(length(a),"-element ",typeof(a),":")
  for i in a
    println("sn=",rpad(i.serialnumber,17,' ')," description=",rpad(i.description,40,' '))
    if Culong == UInt32
      @printf(io,"f=0x%08x, dt=0x%08x, id=0x%08x, lid=0x%08x, h=0x%08x \n",
        i.flags, i.devicetype, i.id, i.locid, i.handle)
    else
      @printf(io,"f=0x%08x, dt=0x%08x, id=0x%08x, lid=0x%08x, h=0x%016x \n",
        i.flags, i.devicetype, i.id, i.locid, i.handle)
    end
    println()
  end
end
 
# FT_FLAGS (see FT_DEVICE_LIST_INFO_NODE)
const FT_FLAGS_OPENED = 0x00000001

# FT_DEVICE_LIST_INFO_NODE (see FT_GetDeviceInfoList and FT_GetDeviceInfoDetail)
immutable _ft_device_list_info_node
  Flags :: Cuint
  Type  :: Cuint
  ID    :: Cuint
  LocId :: Cuint
  sn1  :: UInt8; sn2  :: UInt8; sn3  :: UInt8; sn4  :: UInt8  # SerialNumber
  sn5  :: UInt8; sn6  :: UInt8; sn7  :: UInt8; sn8  :: UInt8
  sn9  :: UInt8; sn10 :: UInt8; sn11 :: UInt8; sn12 :: UInt8
  sn13 :: UInt8; sn14 :: UInt8; sn15 :: UInt8; sn16 :: UInt8
  d1   :: UInt8; d2   :: UInt8; d3   :: UInt8; d4   :: UInt8  # Description
  d5   :: UInt8; d6   :: UInt8; d7   :: UInt8; d8   :: UInt8
  d9   :: UInt8; d10  :: UInt8; d11  :: UInt8; d12  :: UInt8
  d13  :: UInt8; d14  :: UInt8; d15  :: UInt8; d16  :: UInt8
  d17  :: UInt8; d18  :: UInt8; d19  :: UInt8; d20  :: UInt8
  d21  :: UInt8; d22  :: UInt8; d23  :: UInt8; d24  :: UInt8
  d25  :: UInt8; d26  :: UInt8; d27  :: UInt8; d28  :: UInt8
  d29  :: UInt8; d30  :: UInt8; d31  :: UInt8; d32  :: UInt8
  d33  :: UInt8; d34  :: UInt8; d35  :: UInt8; d36  :: UInt8
  d37  :: UInt8; d38  :: UInt8; d39  :: UInt8; d40  :: UInt8
  d41  :: UInt8; d42  :: UInt8; d43  :: UInt8; d44  :: UInt8
  d45  :: UInt8; d46  :: UInt8; d47  :: UInt8; d48  :: UInt8
  d49  :: UInt8; d50  :: UInt8; d51  :: UInt8; d52  :: UInt8
  d53  :: UInt8; d54  :: UInt8; d55  :: UInt8; d56  :: UInt8 
  d57  :: UInt8; d58  :: UInt8; d59  :: UInt8; d60  :: UInt8 
  d61  :: UInt8; d62  :: UInt8; d63  :: UInt8; d64  :: UInt8  
  FT_HANDLE     :: Cuint
  FT_HANDLE_MSB :: Cuint
end

function FT_GetDeviceInfoList(lpdwNumDevs)
  ftdeviceinfolist = Array(_ft_device_list_info_node,lpdwNumDevs)
  n = Ref{Cuint}(lpdwNumDevs)
  ft_status = ccall((:FT_GetDeviceInfoList, d2xx),
                      Cuint,
                      (Ptr{_ft_device_list_info_node},Ref{Cuint}),
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
    # this seems wrong, but I don't have a better idea.
    if Culong == UInt32
      handle = node.FT_HANDLE
    else
      handle = UInt64(node.FT_HANDLE)
      handle = handle | (node.FT_HANDLE_MSB <<32)
    end
    push!(infonodearray,InfoNode(flags,devicetype,id,locid,serialnumber,
                                 description,handle))
  end
  return infonodearray
end