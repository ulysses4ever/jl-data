#__precompile__()
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


include("InfoNode_show.jl")
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
  Manufacturer :: ASCIIString     # "FTDI"
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
    newpd = new(pd.Signature1,pd.Signature2,pd.Version,pd.VendorId,pd.ProductId)
    newpd.Manufacturer = bytestring(pd.Manufacturer)
    newpd.ManufacturerId = bytestring(pd.ManufacturerId)
    newpd.Description = bytestring(pd.Description)
    newpd.SerialNumber = bytestring(pd.SerialNumber)
    for i in 10:130
      newpd.(i) = pd.(i)
    end
    return newpd
  end
end

function ft_program_data(pd::FtProgramData)
  newpd = ft_program_data(pd.Version,pd.Manufacturer,pd.ManufacturerId,pd.Description,pd.SerialNumber)
  newpd.VendorId = pd.VendorId
  newpd.ProductId = pd.ProductId
  for i in 10:130
    newpd.(i) = pd.(i)
  end
  return newpd
end

include("FtProgramData_show.jl")

function checkstatus(ft_status::Culong)
  if ft_status != 0
    throw(Ftd2xxError(ft_status))
  end
  return 0
end







































#=
function FT_SetEventNotification(ft_handle::UInt32, eventmask::Integer)

What do I do here ????

=#
























function FT_WriteEE(ft_handle::UInt32, wordoffset::Integer, value::UInt16)
  @assert wordoffset >= 0
  ft_status = ccall((:FT_WriteEE, "ftd2xx.dll"),
                     Culong,
                     (Culong, Culong, Cushort),
                     ft_handle, wordoffset, value)
  checkstatus(ft_status)
  return nothing
end 

function FT_EraseEE(ft_handle::UInt32)
  ft_status = ccall((:FT_EraseEE, "ftd2xx.dll"),Culong,(Culong, ),ft_handle)
  checkstatus(ft_status)
  return nothing
end 

function FT_EE_Read(ft_handle::UInt32, version::Integer = 5)
  @assert version>-1
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
  ft_status = ccall((:FT_GetLatencyTimer, "ftd2xx.dll"),
                     Culong,
                     (Culong, Ref{Cuchar}),
                     ft_handle, timer)
  checkstatus(ft_status)
  return convert(UInt8,timer[])
end

function FT_SetBitMode(ft_handle::UInt32, mask::UInt8, mode::UInt8)
  @assert mode in keys(ftbitmodedict)
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
  @assert (intransfersize>>4)*16 == intransfersize
  @assert (outtransfersize>>4)*16 == outtransfersize
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
