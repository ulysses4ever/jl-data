module FTD2XX

include("exports.jl")

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

type FtProgramData
  Signature1 :: UInt32 # Header - must be 0x0000000
  Signature2 :: UInt32 # Header - must be 0xffffffff
  Version :: UInt32 # Header - FT_PROGRAM_DATA version 
                   # 0 = original (FT232B) 
                   # 1 = FT2232 extensions 
                   # 2 = FT232R extensions
                   # 3 = FT2232H extensions
                   # 4 = FT4232H extensions
                   # 5 = FT232H extensions
  VendorId :: UInt16 # 0x0403 
  ProductId :: UInt16 # 0x6001 
  Manufactuer :: ASCIIString     # "FTDI"
  ManufacturerId :: ASCIIString  # "FT" 
  Description :: ASCIIString     # "USB HS Serial Converter" 
  SerialNumber :: ASCIIString    # "FT000001" if fixed, or NULL 
  MaxPower :: UInt16 # 0 < MaxPower <= 500
  PnP :: UInt16 # 0 = disabled, 1 = enabled 
  SelfPowered :: UInt16 # 0 = bus powered, 1 = self powered 
  RemoteWakeup :: UInt16  # 0 = not capable, 1 = capable
  #
  # Rev4 (FT232B) extensions 
  #
  Rev4 :: UInt8 # non-zero if Rev4 chip, zero otherwise 
  IsoIn :: UInt8 # non-zero if in endpoint is isochronous 
  IsoOut :: UInt8 # non-zero if out endpoint is isochronous
  PullDownEnable :: UInt8 # non-zero if pull down enabled 
  SerNumEnable :: UInt8 # non-zero if serial number to be used 
  USBVersionEnable :: UInt8 # non-zero if chip uses USBVersion 
  USBVersion :: UInt16 # BCD (0x0200 => USB2) 
  #
  # Rev 5 (FT2232) extensions
  #
  Rev5 :: UInt8 # non-zero if Rev5 chip, zero otherwise 
  IsoInA :: UInt8 # non-zero if in endpoint is isochronous
  IsoInB :: UInt8 # non-zero if in endpoint is isochronous
  IsoOutA :: UInt8 # non-zero if out endpoint is isochronous
  IsoOutB :: UInt8 # non-zero if out endpoint is isochronous 
  PullDownEnable5 :: UInt8 # non-zero if pull down enabled 
  SerNumEnable5 :: UInt8 # non-zero if serial number to be used
  USBVersionEnable5 :: UInt8 # non-zero if chip uses USBVersion 
  USBVersion5 :: UInt16 # BCD (0x0200 => USB2) 
  AIsHighCurrent :: UInt8 # non-zero if interface is high current 
  BIsHighCurrent :: UInt8 # non-zero if interface is high current 
  IFAIsFifo :: UInt8 # non-zero if interface is 245 FIFO 
  IFAIsFifoTar :: UInt8 # non-zero if interface is 245 FIFO CPU target
  IFAIsFastSer :: UInt8 # non-zero if interface is Fast serial 
  AIsVCP :: UInt8 # non-zero if interface is to use VCP drivers 
  IFBIsFifo :: UInt8 # non-zero if interface is 245 FIFO
  IFBIsFifoTar :: UInt8 # non-zero if interface is 245 FIFO CPU target 
  IFBIsFastSer :: UInt8 # non-zero if interface is Fast serial
  BIsVCP  :: UInt8 # non-zero if interface is to use VCP drivers 
  #
  # Rev 6 (FT232R) extensions
  #
  UseExtOsc :: UInt8 # Use External Oscillator 
  HighDriveIOs :: UInt8 # High Drive I/Os 
  EndpointSize :: UInt8 # Endpoint size 
  PullDownEnableR :: UInt8 # non-zero if pull down enabled 
  SerNumEnableR :: UInt8 # non-zero if serial number to be used 
  InvertTXD :: UInt8 # non-zero if invert TXD 
  InvertRXD :: UInt8 # non-zero if invert RXD 
  InvertRTS :: UInt8 # non-zero if invert RTS 
  InvertCTS :: UInt8 # non-zero if invert CTS 
  InvertDTR :: UInt8 # non-zero if invert DTR 
  InvertDSR :: UInt8 # non-zero if invert DSR
  InvertDCD :: UInt8 # non-zero if invert DCD 
  InvertRI  :: UInt8 # non-zero if invert RI 
  Cbus0 :: UInt8 # Cbus Mux control 
  Cbus1 :: UInt8 # Cbus Mux control 
  Cbus2 :: UInt8 # Cbus Mux control 
  Cbus3 :: UInt8 # Cbus Mux control 
  Cbus4 :: UInt8 # Cbus Mux control
  RIsD2XX :: UInt8 # non-zero if using D2XX driver 
  #
  # Rev 7 (FT2232H) Extensions 
  #
  PullDownEnable7 :: UInt8 # non-zero if pull down enabled 
  SerNumEnable7 :: UInt8 # non-zero if serial number to be used 
  ALSlowSlew :: UInt8 # non-zero if AL pins have slow slew 
  ALSchmittInput :: UInt8 # non-zero if AL pins are Schmitt input 
  ALDriveCurrent :: UInt8 # valid values are 4mA, 8mA, 12mA, 16mA 
  AHSlowSlew :: UInt8 # non-zero if AH pins have slow slew 
  AHSchmittInput :: UInt8 # non-zero if AH pins are Schmitt input 
  AHDriveCurrent :: UInt8 # valid values are 4mA, 8mA, 12mA, 16mA 
  BLSlowSlew :: UInt8 # non-zero if BL pins have slow slew 
  BLSchmittInput :: UInt8 # non-zero if BL pins are Schmitt input 
  BLDriveCurrent :: UInt8 # valid values are 4mA, 8mA, 12mA, 16mA 
  BHSlowSlew :: UInt8 # non-zero if BH pins have slow slew 
  BHSchmittInput :: UInt8 # non-zero if BH pins are Schmitt input 
  BHDriveCurrent :: UInt8 # valid values are 4mA, 8mA, 12mA, 16mA 
  IFAIsFifo7 :: UInt8 # non-zero if interface is 245 FIFO 
  IFAIsFifoTar7 :: UInt8 # non-zero if interface is 245 FIFO CPU target 
  IFAIsFastSer7 :: UInt8 # non-zero if interface is Fast serial 
  AIsVCP7 :: UInt8 # non-zero if interface is to use VCP drivers 
  IFBIsFifo7 :: UInt8 # non-zero if interface is 245 FIFO 
  IFBIsFifoTar7 :: UInt8 # non-zero if interface is 245 FIFO CPU target 
  IFBIsFastSer7 :: UInt8 # non-zero if interface is Fast serial 
  BIsVCP7 :: UInt8 # non-zero if interface is to use VCP drivers 
  PowerSaveEnable :: UInt8 # non-zero if using BCBUS7 to save power for self-powered designs 
  #
  # Rev 8 (FT4232H) Extensions 
  #
  PullDownEnable8 :: UInt8 # non-zero if pull down enabled 
  SerNumEnable8 :: UInt8 # non-zero if serial number to be used 
  ASlowSlew :: UInt8 # non-zero if AL pins have slow slew 
  ASchmittInput :: UInt8 # non-zero if AL pins are Schmitt input 
  ADriveCurrent :: UInt8 # valid values are 4mA, 8mA, 12mA, 16mA 
  BSlowSlew :: UInt8 # non-zero if AH pins have slow slew 
  BSchmittInput :: UInt8 # non-zero if AH pins are Schmitt input 
  BDriveCurrent :: UInt8 # valid values are 4mA, 8mA, 12mA, 16mA
  CSlowSlew :: UInt8 # non-zero if BL pins have slow slew 
  CSchmittInput :: UInt8 # non-zero if BL pins are Schmitt input 
  CDriveCurrent :: UInt8 # valid values are 4mA, 8mA, 12mA, 16mA 
  DSlowSlew :: UInt8 # non-zero if BH pins have slow slew 
  DSchmittInput :: UInt8 # non-zero if BH pins are Schmitt input 
  DDriveCurrent :: UInt8 # valid values are 4mA, 8mA, 12mA, 16mA 
  ARIIsTXDEN :: UInt8 # non-zero if port A uses RI as RS485 TXDEN 
  BRIIsTXDEN :: UInt8 # non-zero if port B uses RI as RS485 TXDEN 
  CRIIsTXDEN :: UInt8 # non-zero if port C uses RI as RS485 TXDEN 
  DRIIsTXDEN :: UInt8 # non-zero if port D uses RI as RS485 TXDEN 
  AIsVCP8 :: UInt8 # non-zero if interface is to use VCP drivers 
  BIsVCP8 :: UInt8 # non-zero if interface is to use VCP drivers 
  CIsVCP8 :: UInt8 # non-zero if interface is to use VCP drivers 
  DIsVCP8 :: UInt8 # non-zero if interface is to use VCP drivers 
  #
  # Rev 9 (FT232H) Extensions 
  #
  PullDownEnableH :: UInt8 # non-zero if pull down enabled 
  SerNumEnableH :: UInt8 # non-zero if serial number to be used 
  ACSlowSlewH :: UInt8 # non-zero if AC pins have slow slew 
  ACSchmittInputH :: UInt8 # non-zero if AC pins are Schmitt input 
  ACDriveCurrentH :: UInt8 # valid values are 4mA, 8mA, 12mA, 16mA 
  ADSlowSlewH :: UInt8 # non-zero if AD pins have slow slew 
  ADSchmittInputH :: UInt8 # non-zero if AD pins are Schmitt input 
  ADDriveCurrentH :: UInt8 # valid values are 4mA, 8mA, 12mA, 16mA 
  Cbus0H :: UInt8 # Cbus Mux control 
  Cbus1H :: UInt8 # Cbus Mux control 
  Cbus2H :: UInt8 # Cbus Mux control 
  Cbus3H :: UInt8 # Cbus Mux control 
  Cbus4H :: UInt8 # Cbus Mux control 
  Cbus5H :: UInt8 # Cbus Mux control 
  Cbus6H :: UInt8 # Cbus Mux control 
  Cbus7H :: UInt8 # Cbus Mux control 
  Cbus8H :: UInt8 # Cbus Mux control 
  Cbus9H :: UInt8 # Cbus Mux control 
  IsFifoH :: UInt8 # non-zero if interface is 245 FIFO 
  IsFifoTarH :: UInt8 # non-zero if interface is 245 FIFO CPU target 
  IsFastSerH :: UInt8 # non-zero if interface is Fast serial 
  IsFT1248H :: UInt8 # non-zero if interface is FT1248 
  FT1248CpolH :: UInt8 # FT1248 clock polarity - clock idle high (1) or clock idle low (0) 
  FT1248LsbH :: UInt8 # FT1248 data is LSB (1) or MSB (0) 
  FT1248FlowControlH :: UInt8 # FT1248 flow control enable 
  IsVCPH :: UInt8 # non-zero if interface is to use VCP drivers 
  PowerSaveEnableH :: UInt8 # non-zero if using ACBUS7 to save power for self-powered designs
  function FtProgramData(pd :: ft_program_data)
    newpd = new(pd.Signature1,pd.Signature2,pd.Version,pd.VernorID,pd.ProductId)
    newpd.Manufacture = convert(ASCIIString,
                        pd.Manufacture[1:findfirst(pd.Manufacture,0)-1])
    newpd.ManufactureId = convert(ASCIIString,
                        pd.ManufactureId[1:findfirst(pd.ManufactureId,0)-1])
    newpd.Description = convert(ASCIIString,
                        pd.Description[1:findfirst(pd.Description,0)-1])
    newpd.SerialNumber = convert(ASCIIString,
                        pd.SerialNumber[1:findfirst(pd.SerialNumber,0)-1])
    for i in 10:130
      newpd.[i] = pd.[i]
    end
    return newpd
  end
end

function ft_program_data(pd::FtProgramData)
  newpd = ft_program_data(pd.Version,pd.Manufacture,pd.ManufactureId,pd.Description,pd.SerialNumber)
  newpd.VendorId = pd.VendorId
  newpd.ProductId = pd.ProductId
  for i in 10:130
    newpd.[i] = pd.[i]
  end
  return newpd
end

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
                     ft_handle, ft_device, id, serialnumber, description, C_NULL)
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
  ft_status = ccall((:FT_GetLibraryVersion, "ftd2xx.dll"),Culong,(Ref{Culong},),dllversion)
  checkstatus(ft_status)
  build = (dllversion[] & 0x000000ff)
  minor = (dllversion[] & 0x0000ff00)>>8
  major = (dllversion[] & 0x00ff0000)>>16
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
                     (Culong,Ref{Culong},Ref{Culong},Ref{Culong}),
                     ft_handle, amountinrxqueue, amountintxqueue, eventstatus)
  checkstatus(ft_status)
  return (convert(Int32,amountinrxqueue[]),
          convert(Int32,amountintxqueue[]),convert(Int32,eventstatus[]))
end

#=
function FT_SetEventNotification(ft_handle::UInt32, eventmask::Integer)

What do I do here ????

=#

function FT_SetChars(ft_handle::UInt32, eventch::UInt8, eventchen::Bool,
                                        errorch::UInt8, errorchen::Bool)
  if eventchen
    event = 0x01
  else
    event = 0x00
  end
  if errorchen
    error = 0x01
  else
    error = 0x00
  end
  ft_status = ccall((:FT_SetChars, "ftd2xx.dll"),
                     Culong,
                     (Culong, Cuchar, Cuchar, Cuchar, Cuchar),
                     ft_handle, eventch, event, errorch, error)
  checkstatus(ft_status)
  return nothing
end

function FT_SetBreakOn(ft_handle::UInt32)
  ft_status = ccall((:FT_SetBreakOn, "ftd2xx.dll"),Culong,(Culong,),ft_handle)
  checkstatus(ft_status)
  return nothing
end

function FT_SetBreakOff(ft_handle::UInt32)
  ft_status = ccall((:FT_SetBreakOff, "ftd2xx.dll"),Culong,(Culong,),ft_handle)
  checkstatus(ft_status)
  return nothing
end

function FT_Purge(ft_handle::UInt32, mask::Integer)
  ft_status = ccall((:FT_Purge, "ftd2xx.dll"),
                     Culong,
                     (Culong, Culong),
                     ft_handle, mask)
  checkstatus(ft_status)
  return nothing
end

function FT_ResetDevice(ft_handle::UInt32)
  ft_status = ccall((:FT_ResetDevice, "ftd2xx.dll"),Culong,(Culong,),ft_handle)
  checkstatus(ft_status)
  return nothing
end

function FT_ResetPort(ft_handle::UInt32)
  ft_status = ccall((:FT_ResetPort, "ftd2xx.dll"),Culong,(Culong,),ft_handle)
  checkstatus(ft_status)
  return nothing
end

function FT_CyclePort(ft_handle::UInt32)
  ft_status = ccall((:FT_CyclePort, "ftd2xx.dll"),Culong,(Culong,),ft_handle)
  checkstatus(ft_status)
  return nothing
end

function FT_Rescan(ft_handle::UInt32)
  ft_status = ccall((:FT_Rescan, "ftd2xx.dll"),Culong,(Culong,),ft_handle)
  checkstatus(ft_status)
  return nothing
end

function FT_Reload(vid::Integer, pid::Integer)
  ft_status = ccall((:FT_Reload, "ftd2xx.dll"),
                     Culong,
                     (Cuint, Cuint),
                     vid, pid)
  checkstatus(ft_status)
  return nothing
end

function FT_SetResetPipeRetryCount(ft_handle::UInt32, count::Integer)
  ft_status = ccall((:FT_SetResetPipeRetryCount, "ftd2xx.dll"),
                     Culong,
                     (Culong, Culong),
                     ft_handle, count)
  checkstatus(ft_status)
  return nothing
end

function FT_StopInTask(ft_handle::UInt32)
  ft_status = ccall((:FT_StopInTask, "ftd2xx.dll"),Culong,(Culong,),ft_handle)
  checkstatus(ft_status)
  return nothing
end

function FT_RestartInTask(ft_handle::UInt32)
  ft_status = ccall((:FT_RestartInTask, "ftd2xx.dll"),Culong,(Culong,),ft_handle)
  checkstatus(ft_status)
  return nothing
end

function FT_SetDeadmanTimeout(ft_handle::UInt32, deadmantimeout::Integer = 5000)
  ft_status = ccall((:FT_SetDeadmanTimeout, "ftd2xx.dll"),
                     Culong,
                     (Culong, Culong),
                     ft_handle, deadmantimeout)
  checkstatus(ft_status)
  return nothing
end 

function FT_ReadEE(ft_handle::UInt32, wordoffset::Integer)
  value = Ref{Culong}()
  ft_status = ccall((:FT_ReadEE, "ftd2xx.dll"),
                     Culong,
                     (Culong, Culong, Ref{Culong}),
                     ft_handle, wordoffset, value)
  checkstatus(ft_status)
  return convert(UInt32,value[])
end

function FT_WriteEE(ft_handle::UInt32, wordofffset::Integer, value::Integer)
  ft_status = ccall((:FT_WriteEE, "ftd2xx.dll"),
                     Culong,
                     (Culong, Culong, Culong),
                     ft_handle, wordoffset, value)
  checkstatus(ft_status)
  return nothing
end 

function FT_EraseEE(ft_handle::UInt32)
  ft_status = ccall((:FT_EraseEE, "ftd2xx.dll"),Culong,(Culong, ),ft_handle)
  checkstatus(ft_status)
  return nothing
end 

function FT_EE_Read(ft_handle::UInt32, Version::Integer = 5)
  @assert Version>-1
  ftpds = Ref{ft_program_data}(ft_program_data(version))
  ft_status = ccall((:FT_EE_Read, "ftd2xx.dll"),
                     Culong,
                     (Culong, Ref{ft_program_data}),
                     ft_handle, ftpds)
  checkstatus(ft_status)
  return FtProgramData(ftpds[])
end

function FT_EE_Program(ft_handle::UInt32, pd::FtProgramData)
  ftpds = Ref{ft_program_data}(ft_program_data(pd))
  ft_status = ccall((:FT_EE_Program, "ftd2xx.dll"),
                     Culong,
                     (Culong, Ref{ft_program_data}),
                     ft_handle, ftpds)
  checkstatus(ft_status)
  return nothing
end

function FT_EE_UASize(ft_handle::UInt32)
  eesize = Ref{Culong}()
  ft_status = ccall((:FT_EE_UASize, "ftd2xx.dll"),
                     Culong,
                     (Culong, Ref{Culong}),
                     ft_handle, eesize)
  checkstatus(ft_status)
  return convert(Int32,eesize[])
end

function FT_EE_UARead!(ft_handle::UInt32, buffer::Array{UInt8,1})
  len = length(buffer)
  bytesread = Ref{Culong}()
  ft_status = ccall((:FT_EE_UARead, "ftd2xx.dll"),
                     Culong,
                     (Culong, Ptr{UInt8}, Culong, Ref{Culong}),
                     ft_handle, buffer, len, bytesread)
  checkstatus(ft_status)
  return convert(UInt32, bytesread[])
end

function FT_EE_UAWrite(ft_handle::UInt32, buffer::Array{UInt8,1})
  len = length(buffer)
  ft_status = ccall((:FT_EE_UAWrite, "ftd2xx.dll"),
                     Culong,
                     (Culong, Ptr{UInt8}, Culong),
                     ft_handle, buffer, len)
  checkstatus(ft_status)
  return nothing
end

function FT_SetLatencyTimer(ft_handle::UInt32, timer::Integer)
  @assert timer>1
  @assert timer<256
  ft_status = ccall((:FT_SetLatencyTimer, "ftd2xx.dll"),
                     Culong,
                     (Culong, Cuchar),
                     ft_handle, timer)
  checkstatus(ft_status)
  return nothing
end

function FT_GetLatencyTimer(ft_handle::UInt32)
  timer = Ref{Cuchar}()
  ft_status = ccall((:FT_SetLatencyTimer, "ftd2xx.dll"),
                     Culong,
                     (Culong, Ref{Cuchar}),
                     ft_handle, timer)
  checkstatus(ft_status)
  return convert(UInt8,timer[])
end

function FT_SetBitMode(ft_handle::UInt32, mask::UInt8, mode::UInt8)
  ft_status = ccall((:FT_SetBitMode, "ftd2xx.dll"),
                     Culong,
                     (Culong, Cuchar, Cuchar),
                     ft_handle, mask, mode)
  checkstatus(ft_status)
  return nothing
end

function FT_GetBitMode(ft_handle::UInt32)
  mode = Ref{Cuchar}()
  ft_status = ccall((:FT_GetBitMode, "ftd2xx.dll"),
                     Culong,
                     (Culong, Ref{Cuchar}),
                     ft_handle, mode)
  checkstatus(ft_status)
  return convert(UInt8, mode[])
end 

function FT_SetUSBParameters(ft_handle::UInt32,
                             intransfersize::Integer = 4096,
                             outtransfersize::Integer = 4096)
  @assert intransfersize > 63
  @assert outtransfersize > 63
  @assert intransfersize < 2^16+1
  @assert outtransfersize < 2^16+1
  @assert (intransfer>>4)*16 == intransfersize
  @assert (outtransfer>>4)*16 == outtransfersize
  ft_status = ccall((:FT_SetUSBParameters, "ftd2xx.dll"),
                     Culong,
                     (Culong, Culong, Culong),
                     ft_handle, intransfersize, outtransfersize)
  checkstatus(ft_status)
  return nothing
end



ftbitmodedict = Dict(
  FT_BITMODE_RESET => "FT_BITMODE_RESET",
  FT_BITMODE_ASYNC_BITBANG => "FT_BITMODE_ASYNC_BITBANG",
  FT_BITMODE_MPSSE => "FT_BITMODE_MPSSE",
  FT_BITMODE_SYNC_BITBANG => "FT_BITMODE_SYNC_BITBANG",
  FT_BITMODE_MCU_HOST => "FT_BITMODE_MCU_HOST",
  FT_BITMODE_FAST_SERIAL => "FT_BITMODE_FAST_SERIAL",
  FT_BITMODE_CBUS_BITBANG => "FT_BITMODE_CBUS_BITBANG",
  FT_BITMODE_SYNC_FIFO => "FT_BITMODE_SYNC_FIFO")


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
