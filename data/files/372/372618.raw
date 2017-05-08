# Types and Constants

# FT_STATUS (DWORD)
const FT_OK = 0 
const FT_INVALID_HANDLE = 1
const FT_DEVICE_NOT_FOUND = 2
const FT_DEVICE_NOT_OPENED = 3
const FT_IO_ERROR = 4
const FT_INSUFFICIENT_RESOURCES = 5
const FT_INVALID_PARAMETER = 6
const FT_INVALID_BAUD_RATE = 7
const FT_DEVICE_NOT_OPENED_FOR_ERASE = 8
const FT_DEVICE_NOT_OPENED_FOR_WRITE = 9
const FT_FAILED_TO_WRITE_DEVICE = 10
const FT_EEPROM_READ_FAILED = 11
const FT_EEPROM_WRITE_FAILED = 12
const FT_EEPROM_ERASE_FAILED = 13
const FT_EEPROM_NOT_PRESENT = 14
const FT_EEPROM_NOT_PROGRAMMED = 15
const FT_INVALID_ARGS = 16
const FT_NOT_SUPPORTED = 17
const FT_OTHER_ERROR = 18

#Flags (see FT_ListDevices)
const FT_LIST_NUMBER_ONLY = 0x80000000
const FT_LIST_BY_INDEX = 0x40000000
const FT_LIST_ALL = 0x20000000

#Flags (see FT_OpenEx)
const FT_OPEN_BY_SERIAL_NUMBER = 1
const FT_OPEN_BY_DESCRIPTION = 2
const FT_OPEN_BY_LOCATION = 4

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

# Driver types
const FT_DRIVER_TYPE_D2XX = 0
const FT_DRIVER_TYPE_VCP = 1

#Word Length (see FT_SetDataCharacteristics) 
const FT_BITS_8 = 8 
const FT_BITS_7 = 7

#Stop Bits (see FT_SetDataCharacteristics) 
const FT_STOP_BITS_1 = 0 
const FT_STOP_BITS_2 = 2

#Parity (see FT_SetDataCharacteristics) 
const FT_PARITY_NONE = 0 
const FT_PARITY_ODD = 1 
const FT_PARITY_EVEN = 2 
const FT_PARITY_MARK = 3 
const FT_PARITY_SPACE = 4

#Flow Control (see FT_SetFlowControl) 
const FT_FLOW_NONE = 0x0000 
const FT_FLOW_RTS_CTS = 0x0100 
const FT_FLOW_DTR_DSR = 0x0200 
const FT_FLOW_XON_XOFF = 0x0400

#Purge RX and TX Buffers (see FT_Purge) 
const FT_PURGE_RX = 1 
const FT_PURGE_TX = 2

#Notification Events (see FT_SetEventNotification) 
const FT_EVENT_RXCHAR = 1 
const FT_EVENT_MODEM_STATUS = 2 
const FT_EVENT_LINE_STATUS = 4

#Modem Status (see FT_GetModemStatus) 
const CTS = 0x10 
const DSR = 0x20 
const RI = 0x40 
const DCD = 0x80

#Line Status (see FT_GetModemStatus) 
const OE = 0x02 
const PE = 0x04 
const FE = 0x08 
const BI = 0x10

#Bit Modes (see FT_SetBitMode) 
const FT_BITMODE_RESET = 0x00 
const FT_BITMODE_ASYNC_BITBANG = 0x01 
const FT_BITMODE_MPSSE = 0x02 
const FT_BITMODE_SYNC_BITBANG = 0x04 
const FT_BITMODE_MCU_HOST = 0x08 
const FT_BITMODE_FAST_SERIAL = 0x10
const FT_BITMODE_CBUS_BITBANG = 0x20 
const FT_BITMODE_SYNC_FIFO = 0x40

#FT232R CBUS EEPROM OPTIONS - Ignored for FT245R (see FT_EE_Program and FT_EE_Read) 
const FT_232R_CBUS_TXDEN = 0x00 
const FT_232R_CBUS_PWRON = 0x01 
const FT_232R_CBUS_RXLED = 0x02 
const FT_232R_CBUS_TXLED = 0x03 
const FT_232R_CBUS_TXRXLED = 0x04 
const FT_232R_CBUS_SLEEP = 0x05 
const FT_232R_CBUS_CLK48 = 0x06 
const FT_232R_CBUS_CLK24 = 0x07 
const FT_232R_CBUS_CLK12 = 0x08 
const FT_232R_CBUS_CLK6 = 0x09 
const FT_232R_CBUS_IOMODE = 0x0A 
const FT_232R_CBUS_BITBANG_WR = 0x0B 
const FT_232R_CBUS_BITBANG_RD = 0x0C

#FT232H CBUS EEPROM OPTIONS (see FT_EE_Program and FT_EE_Read) 
const FT_232H_CBUS_TRISTATE = 0x00 
const FT_232H_CBUS_RXLED = 0x01 
const FT_232H_CBUS_TXLED = 0x02 
const FT_232H_CBUS_TXRXLED = 0x03 
const FT_232H_CBUS_PWREN = 0x04 
const FT_232H_CBUS_SLEEP = 0x05 
const FT_232H_CBUS_DRIVE_0 = 0x06 
const FT_232H_CBUS_DRIVE_1 = 0x07 
const FT_232H_CBUS_IOMODE = 0x08 
const FT_232H_CBUS_TXDEN = 0x09 
const FT_232H_CBUS_CLK30 = 0x0A 
const FT_232H_CBUS_CLK15 = 0x0B 
const FT_232H_CBUS_CLK7_5 = 0x0C

#FT X Series CBUS Options EEPROM values (see FT_EEPROM_Read and FT_EEPROM_Program)
const FT_X_SERIES_CBUS_TRISTATE = 0x00
const FT_X_SERIES_CBUS_RXLED = 0x01
const FT_X_SERIES_CBUS_TXLED = 0x02
const FT_X_SERIES_CBUS_TXRXLED = 0x03
const FT_X_SERIES_CBUS_PWREN = 0x04
const FT_X_SERIES_CBUS_SLEEP = 0x05
const FT_X_SERIES_CBUS_DRIVE_0 = 0x06
const FT_X_SERIES_CBUS_DRIVE_1 = 0x07
const FT_X_SERIES_CBUS_IOMODE = 0x08
const FT_X_SERIES_CBUS_TXDEN = 0x09
const FT_X_SERIES_CBUS_CLK24 = 0x0A
const FT_X_SERIES_CBUS_CLK12 = 0x0B
const FT_X_SERIES_CBUS_CLK6 = 0x0C
const FT_X_SERIES_CBUS_BCD_CHARGER = 0x0D
const FT_X_SERIES_CBUS_BCD_CHARGER_N = 0x0E
const FT_X_SERIES_CBUS_I2C_TXE = 0x0F
const FT_X_SERIES_CBUS_I2C_RXF = 0x10
const FT_X_SERIES_CBUS_VBUS_SENSE = 0x11
const FT_X_SERIES_CBUS_BITBANG_WR = 0x12
const FT_X_SERIES_CBUS_BITBANG_RD = 0x13
const FT_X_SERIES_CBUS_TIMESTAMP = 0x14
const FT_X_SERIES_CBUS_KEEP_AWAKE = 0x15

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
  FT_HANDLE    :: Cuint

  function _ft_device_list_info_node()
    new(0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,0,0,
      0)
  end
end

# FT_FLAGS (see FT_DEVICE_LIST_INFO_NODE)
const FT_FLAGS_OPENED = 0x00000001

# FT_PROGRAM_DATA_STRUCTURE 
type ft_program_data
  Signature1 :: Cuint # Header - must be 0x0000000
  Signature2 :: Cuint # Header - must be 0xffffffff
  Version :: Cuint # Header - FT_PROGRAM_DATA version 
                   # 0 = original (FT232B) 
                   # 1 = FT2232 extensions 
                   # 2 = FT232R extensions
                   # 3 = FT2232H extensions
                   # 4 = FT4232H extensions
                   # 5 = FT232H extensions
  VendorId :: Cushort # 0x0403 
  ProductId :: Cushort # 0x6001 
  Manufactuer :: Ref{UInt8}    # "FTDI"
  ManufacturerId :: Ref{UInt8} # "FT" 
  Description :: Ref{UInt8}    # "USB HS Serial Converter" 
  SerialNumber :: Ref{UInt8}   # "FT000001" if fixed, or NULL 
  MaxPower :: Cushort # 0 < MaxPower <= 500
  PnP :: Cushort # 0 = disabled, 1 = enabled 
  SelfPowered :: Cushort # 0 = bus powered, 1 = self powered 
  RemoteWakeup :: Cushort  # 0 = not capable, 1 = capable
  #
  # Rev4 (FT232B) extensions 
  #
  Rev4 :: Cuchar # non-zero if Rev4 chip, zero otherwise 
  IsoIn :: Cuchar # non-zero if in endpoint is isochronous 
  IsoOut :: Cuchar # non-zero if out endpoint is isochronous
  PullDownEnable :: Cuchar # non-zero if pull down enabled 
  SerNumEnable :: Cuchar # non-zero if serial number to be used 
  USBVersionEnable :: Cuchar # non-zero if chip uses USBVersion 
  USBVersion :: Cushort # BCD (0x0200 => USB2) 
  #
  # Rev 5 (FT2232) extensions
  #
  Rev5 :: Cuchar # non-zero if Rev5 chip, zero otherwise 
  IsoInA :: Cuchar # non-zero if in endpoint is isochronous
  IsoInB :: Cuchar # non-zero if in endpoint is isochronous
  IsoOutA :: Cuchar # non-zero if out endpoint is isochronous
  IsoOutB :: Cuchar # non-zero if out endpoint is isochronous 
  PullDownEnable5 :: Cuchar # non-zero if pull down enabled 
  SerNumEnable5 :: Cuchar # non-zero if serial number to be used
  USBVersionEnable5 :: Cuchar # non-zero if chip uses USBVersion 
  USBVersion5 :: Cshort # BCD (0x0200 => USB2) 
  AIsHighCurrent :: Cuchar # non-zero if interface is high current 
  BIsHighCurrent :: Cuchar # non-zero if interface is high current 
  IFAIsFifo :: Cuchar # non-zero if interface is 245 FIFO 
  IFAIsFifoTar :: Cuchar # non-zero if interface is 245 FIFO CPU target
  IFAIsFastSer :: Cuchar # non-zero if interface is Fast serial 
  AIsVCP :: Cuchar # non-zero if interface is to use VCP drivers 
  IFBIsFifo :: Cuchar # non-zero if interface is 245 FIFO
  IFBIsFifoTar :: Cuchar # non-zero if interface is 245 FIFO CPU target 
  IFBIsFastSer :: Cuchar # non-zero if interface is Fast serial
  BIsVCP  :: Cuchar # non-zero if interface is to use VCP drivers 
  #
  # Rev 6 (FT232R) extensions
  #
  UseExtOsc :: Cuchar # Use External Oscillator 
  HighDriveIOs :: Cuchar # High Drive I/Os 
  EndpointSize :: Cuchar # Endpoint size 
  PullDownEnableR :: Cuchar # non-zero if pull down enabled 
  SerNumEnableR :: Cuchar # non-zero if serial number to be used 
  InvertTXD :: Cuchar # non-zero if invert TXD 
  InvertRXD :: Cuchar # non-zero if invert RXD 
  InvertRTS :: Cuchar # non-zero if invert RTS 
  InvertCTS :: Cuchar # non-zero if invert CTS 
  InvertDTR :: Cuchar # non-zero if invert DTR 
  InvertDSR :: Cuchar # non-zero if invert DSR
  InvertDCD :: Cuchar # non-zero if invert DCD 
  InvertRI  :: Cuchar # non-zero if invert RI 
  Cbus0 :: Cuchar # Cbus Mux control 
  Cbus1 :: Cuchar # Cbus Mux control 
  Cbus2 :: Cuchar # Cbus Mux control 
  Cbus3 :: Cuchar # Cbus Mux control 
  Cbus4 :: Cuchar # Cbus Mux control
  RIsD2XX :: Cuchar # non-zero if using D2XX driver 
  #
  # Rev 7 (FT2232H) Extensions 
  #
  PullDownEnable7 :: Cuchar # non-zero if pull down enabled 
  SerNumEnable7 :: Cuchar # non-zero if serial number to be used 
  ALSlowSlew :: Cuchar # non-zero if AL pins have slow slew 
  ALSchmittInput :: Cuchar # non-zero if AL pins are Schmitt input 
  ALDriveCurrent :: Cuchar # valid values are 4mA, 8mA, 12mA, 16mA 
  AHSlowSlew :: Cuchar # non-zero if AH pins have slow slew 
  AHSchmittInput :: Cuchar # non-zero if AH pins are Schmitt input 
  AHDriveCurrent :: Cuchar # valid values are 4mA, 8mA, 12mA, 16mA 
  BLSlowSlew :: Cuchar # non-zero if BL pins have slow slew 
  BLSchmittInput :: Cuchar # non-zero if BL pins are Schmitt input 
  BLDriveCurrent :: Cuchar # valid values are 4mA, 8mA, 12mA, 16mA 
  BHSlowSlew :: Cuchar # non-zero if BH pins have slow slew 
  BHSchmittInput :: Cuchar # non-zero if BH pins are Schmitt input 
  BHDriveCurrent :: Cuchar # valid values are 4mA, 8mA, 12mA, 16mA 
  IFAIsFifo7 :: Cuchar # non-zero if interface is 245 FIFO 
  IFAIsFifoTar7 :: Cuchar # non-zero if interface is 245 FIFO CPU target 
  IFAIsFastSer7 :: Cuchar # non-zero if interface is Fast serial 
  AIsVCP7 :: Cuchar # non-zero if interface is to use VCP drivers 
  IFBIsFifo7 :: Cuchar # non-zero if interface is 245 FIFO 
  IFBIsFifoTar7 :: Cuchar # non-zero if interface is 245 FIFO CPU target 
  IFBIsFastSer7 :: Cuchar # non-zero if interface is Fast serial 
  BIsVCP7 :: Cuchar # non-zero if interface is to use VCP drivers 
  PowerSaveEnable :: Cuchar # non-zero if using BCBUS7 to save power for self-powered designs 
  #
  # Rev 8 (FT4232H) Extensions 
  #
  PullDownEnable8 :: Cuchar # non-zero if pull down enabled 
  SerNumEnable8 :: Cuchar # non-zero if serial number to be used 
  ASlowSlew :: Cuchar # non-zero if AL pins have slow slew 
  ASchmittInput :: Cuchar # non-zero if AL pins are Schmitt input 
  ADriveCurrent :: Cuchar # valid values are 4mA, 8mA, 12mA, 16mA 
  BSlowSlew :: Cuchar # non-zero if AH pins have slow slew 
  BSchmittInput :: Cuchar # non-zero if AH pins are Schmitt input 
  BDriveCurrent :: Cuchar # valid values are 4mA, 8mA, 12mA, 16mA
  CSlowSlew :: Cuchar # non-zero if BL pins have slow slew 
  CSchmittInput :: Cuchar # non-zero if BL pins are Schmitt input 
  CDriveCurrent :: Cuchar # valid values are 4mA, 8mA, 12mA, 16mA 
  DSlowSlew :: Cuchar # non-zero if BH pins have slow slew 
  DSchmittInput :: Cuchar # non-zero if BH pins are Schmitt input 
  DDriveCurrent :: Cuchar # valid values are 4mA, 8mA, 12mA, 16mA 
  ARIIsTXDEN :: Cuchar # non-zero if port A uses RI as RS485 TXDEN 
  BRIIsTXDEN :: Cuchar # non-zero if port B uses RI as RS485 TXDEN 
  CRIIsTXDEN :: Cuchar # non-zero if port C uses RI as RS485 TXDEN 
  DRIIsTXDEN :: Cuchar # non-zero if port D uses RI as RS485 TXDEN 
  AIsVCP8 :: Cuchar # non-zero if interface is to use VCP drivers 
  BIsVCP8 :: Cuchar # non-zero if interface is to use VCP drivers 
  CIsVCP8 :: Cuchar # non-zero if interface is to use VCP drivers 
  DIsVCP8 :: Cuchar # non-zero if interface is to use VCP drivers 
  #
  # Rev 9 (FT232H) Extensions 
  #
  PullDownEnableH :: Cuchar # non-zero if pull down enabled 
  SerNumEnableH :: Cuchar # non-zero if serial number to be used 
  ACSlowSlewH :: Cuchar # non-zero if AC pins have slow slew 
  ACSchmittInputH :: Cuchar # non-zero if AC pins are Schmitt input 
  ACDriveCurrentH :: Cuchar # valid values are 4mA, 8mA, 12mA, 16mA 
  ADSlowSlewH :: Cuchar # non-zero if AD pins have slow slew 
  ADSchmittInputH :: Cuchar # non-zero if AD pins are Schmitt input 
  ADDriveCurrentH :: Cuchar # valid values are 4mA, 8mA, 12mA, 16mA 
  Cbus0H :: Cuchar # Cbus Mux control 
  Cbus1H :: Cuchar # Cbus Mux control 
  Cbus2H :: Cuchar # Cbus Mux control 
  Cbus3H :: Cuchar # Cbus Mux control 
  Cbus4H :: Cuchar # Cbus Mux control 
  Cbus5H :: Cuchar # Cbus Mux control 
  Cbus6H :: Cuchar # Cbus Mux control 
  Cbus7H :: Cuchar # Cbus Mux control 
  Cbus8H :: Cuchar # Cbus Mux control 
  Cbus9H :: Cuchar # Cbus Mux control 
  IsFifoH :: Cuchar # non-zero if interface is 245 FIFO 
  IsFifoTarH :: Cuchar # non-zero if interface is 245 FIFO CPU target 
  IsFastSerH :: Cuchar # non-zero if interface is Fast serial 
  IsFT1248H :: Cuchar # non-zero if interface is FT1248 
  FT1248CpolH :: Cuchar # FT1248 clock polarity - clock idle high (1) or clock idle low (0) 
  FT1248LsbH :: Cuchar # FT1248 data is LSB (1) or MSB (0) 
  FT1248FlowControlH :: Cuchar # FT1248 flow control enable 
  IsVCPH :: Cuchar # non-zero if interface is to use VCP drivers 
  PowerSaveEnableH :: Cuchar # non-zero if using ACBUS7 to save power for self-powered designs
end

# EEPROM_HEADER STRUCTURE (See FT_EEPROM_Read and FT_EEPROM_Program)
type ft_eeprom_header
  deviceType :: Cuint # FT_DEVICE FTxxxx device type to be programmed
  # Device descriptor options
  VendorId :: Cshort # 0x0403
  ProductId :: Cshort # 0x6001
  SerNumEnable :: Cuchar # non-zero if serial number to be used
  # Config descriptor options
  MaxPower :: Cshort #  0 < MaxPower <= 500
end

# FT232B EEPROM structure for use with FT_EEPROM_Read and FT_EEPROM_Program
type ft_eeprom_232b
  # Common header
  ### BEGIN common elements for all device EEPROMs ###
  deviceType :: Cuint # FT_DEVICE FTxxxx device type to be programmed
  # Device descriptor options
  VendorId :: Cshort # 0x0403
  ProductId :: Cshort # 0x6001
  SerNumEnable :: Cuchar # non-zero if serial number to be used
  # Config descriptor options
  MaxPower :: Cshort #  0 < MaxPower <= 500
  ### END common elements for all device EEPROMs ###
end

# FT2232 EEPROM structure for use with FT_EEPROM_Read and FT_EEPROM_Program
type ft_eeprom_2232
  ### BEGIN common elements for all device EEPROMs ###
  deviceType :: Cuint # FT_DEVICE FTxxxx device type to be programmed
  # Device descriptor options
  VendorId :: Cshort # 0x0403
  ProductId :: Cshort # 0x6001
  SerNumEnable :: Cuchar # non-zero if serial number to be used
  # Config descriptor options
  MaxPower :: Cshort #  0 < MaxPower <= 500
  ### END common elements for all device EEPROMs ###
  # Drive options
  AIsHighCurrent :: Cuchar # non-zero if interface is high current
  BIsHighCurrent :: Cuchar # non-zero if interface is high current
  # Hardware options
  AIsFifo :: Cuchar # non-zero if interface is 245 FIFO
  AIsFifoTar :: Cuchar # non-zero if interface is 245 FIFO CPU target
  AIsFastSer :: Cuchar # non-zero if interface is Fast serial
  BIsFifo :: Cuchar # non-zero if interface is 245 FIFO
  BIsFifoTar :: Cuchar # non-zero if interface is 245 FIFO CPU target
  BIsFastSer :: Cuchar # non-zero if interface is Fast serial
  # Driver option
  ADriverType :: Cuchar 
  BDriverType  :: Cuchar
end

# FT232R EEPROM structure for use with FT_EEPROM_Read and FT_EEPROM_Program
type ft_eeprom_232r
  ### BEGIN common elements for all device EEPROMs ###
  deviceType :: Cuint # FT_DEVICE FTxxxx device type to be programmed
  # Device descriptor options
  VendorId :: Cshort # 0x0403
  ProductId :: Cshort # 0x6001
  SerNumEnable :: Cuchar # non-zero if serial number to be used
  # Config descriptor options
  MaxPower :: Cshort #  0 < MaxPower <= 500
  ### END common elements for all device EEPROMs ###
  # Drive options
  IsHighCurrent :: Cuchar # non-zero if interface is high current
  # Hardware options
  UseExtOsc :: Cuchar # Use External Oscillator
  InvertTXD :: Cuchar # non-zero if invert TXD
  InvertRXD :: Cuchar # non-zero if invert RXD
  InvertRTS :: Cuchar # non-zero if invert RTS
  InvertCTS :: Cuchar # non-zero if invert CTS
  InvertDTR :: Cuchar # non-zero if invert DTR
  InvertDSR :: Cuchar # non-zero if invert DSR
  InvertDCD :: Cuchar # non-zero if invert DCD
  InvertRI :: Cuchar # non-zero if invert RI
  Cbus0 :: Cuchar # Cbus Mux control
  Cbus1 :: Cuchar # Cbus Mux control
  Cbus2 :: Cuchar # Cbus Mux control
  Cbus3 :: Cuchar # Cbus Mux control
  Cbus4 :: Cuchar # Cbus Mux control
# Driver option
  DriverType :: Cuchar #
end

# FT2232H EEPROM structure for use with FT_EEPROM_Read and FT_EEPROM_Program
type ft_eeprom_2232h
  ### BEGIN common elements for all device EEPROMs ###
  deviceType :: Cuint # FT_DEVICE FTxxxx device type to be programmed
  # Device descriptor options
  VendorId :: Cshort # 0x0403
  ProductId :: Cshort # 0x6001
  SerNumEnable :: Cuchar # non-zero if serial number to be used
  # Config descriptor options
  MaxPower :: Cshort #  0 < MaxPower <= 500
  ### END common elements for all device EEPROMs ###
  # Drive options
  ALSlowSlew :: Cuchar # non-zero if AL pins have slow slew
  ALSchmittInput :: Cuchar # non-zero if AL pins are Schmitt input
  ALDriveCurrent :: Cuchar # valid values are 4mA, 8mA, 12mA, 16mA
  AHSlowSlew :: Cuchar # non-zero if AH pins have slow slew
  AHSchmittInput :: Cuchar # non-zero if AH pins are Schmitt input
  AHDriveCurrent :: Cuchar # valid values are 4mA, 8mA, 12mA, 16mA
  BLSlowSlew :: Cuchar # non-zero if BL pins have slow slew
  BLSchmittInput :: Cuchar # non-zero if BL pins are Schmitt input
  BLDriveCurrent :: Cuchar # valid values are 4mA, 8mA, 12mA, 16mA
  BHSlowSlew :: Cuchar # non-zero if BH pins have slow slew
  BHSchmittInput :: Cuchar # non-zero if BH pins are Schmitt input
  BHDriveCurrent :: Cuchar # valid values are 4mA, 8mA, 12mA, 16mA
  # Hardware options
  AIsFifo :: Cuchar # non-zero if interface is 245 FIFO
  AIsFifoTar :: Cuchar # non-zero if interface is 245 FIFO CPU target
  AIsFastSer :: Cuchar # non-zero if interface is Fast serial
  BIsFifo :: Cuchar # non-zero if interface is 245 FIFO
  BIsFifoTar :: Cuchar # non-zero if interface is 245 FIFO CPU target
  BIsFastSer :: Cuchar # non-zero if interface is Fast serial
  PowerSaveEnable :: Cuchar # non-zero if using BCBUS7 to save power for
  # self-powered designs
  # Driver option
  ADriverType :: Cuchar #   
  BDriverType :: Cuchar # 
end

# FT4232H EEPROM structure for use with FT_EEPROM_Read and FT_EEPROM_Program
type ft_eeprom_4232h
  ### BEGIN common elements for all device EEPROMs ###
  deviceType :: Cuint # FT_DEVICE FTxxxx device type to be programmed
  # Device descriptor options
  VendorId :: Cshort # 0x0403
  ProductId :: Cshort # 0x6001
  SerNumEnable :: Cuchar # non-zero if serial number to be used
  # Config descriptor options
  MaxPower :: Cshort #  0 < MaxPower <= 500
  ### END common elements for all device EEPROMs ###
  # Drive options
  ASlowSlew :: Cuchar # non-zero if A pins have slow slew
  ASchmittInput :: Cuchar # non-zero if A pins are Schmitt input
  ADriveCurrent :: Cuchar # valid values are 4mA, 8mA, 12mA, 16mA
  BSlowSlew :: Cuchar # non-zero if B pins have slow slew
  BSchmittInput :: Cuchar # non-zero if B pins are Schmitt input
  BDriveCurrent :: Cuchar # valid values are 4mA, 8mA, 12mA, 16mA
  CSlowSlew :: Cuchar # non-zero if C pins have slow slew
  CSchmittInput :: Cuchar # non-zero if C pins are Schmitt input
  CDriveCurrent :: Cuchar # valid values are 4mA, 8mA, 12mA, 16mA
  DSlowSlew :: Cuchar # non-zero if D pins have slow slew
  DSchmittInput :: Cuchar # non-zero if D pins are Schmitt input
  DDriveCurrent :: Cuchar # valid values are 4mA, 8mA, 12mA, 16mA
  # Hardware options
  ARIIsTXDEN :: Cuchar # non-zero if port A uses RI as RS485 TXDEN
  BRIIsTXDEN :: Cuchar # non-zero if port B uses RI as RS485 TXDEN
  CRIIsTXDEN :: Cuchar # non-zero if port C uses RI as RS485 TXDEN
  DRIIsTXDEN :: Cuchar # non-zero if port D uses RI as RS485 TXDEN
  # Driver option
  ADriverType :: Cuchar #
  BDriverType :: Cuchar #
  CDriverType :: Cuchar #
  DDriverType :: Cuchar #
end

# FT232H EEPROM structure for use with FT_EEPROM_Read and FT_EEPROM_Program
type ft_eeprom_232h
  ### BEGIN common elements for all device EEPROMs ###
  deviceType :: Cuint # FT_DEVICE FTxxxx device type to be programmed
  # Device descriptor options
  VendorId :: Cshort # 0x0403
  ProductId :: Cshort # 0x6001
  SerNumEnable :: Cuchar # non-zero if serial number to be used
  # Config descriptor options
  MaxPower :: Cshort #  0 < MaxPower <= 500
  ### END common elements for all device EEPROMs ###
  # Drive options
  ACSlowSlew :: Cuchar # non-zero if AC bus pins have slow slew
  ACSchmittInput :: Cuchar # non-zero if AC bus pins are Schmitt input
  ACDriveCurrent :: Cuchar # valid values are 4mA, 8mA, 12mA, 16mA
  ADSlowSlew :: Cuchar # non-zero if AD bus pins have slow slew
  ADSchmittInput :: Cuchar # non-zero if AD bus pins are Schmitt input
  ADDriveCurrent :: Cuchar # valid values are 4mA, 8mA, 12mA, 16mA
  # CBUS options
  Cbus0 :: Cuchar # Cbus Mux control
  Cbus1 :: Cuchar # Cbus Mux control
  Cbus2 :: Cuchar # Cbus Mux control
  Cbus3 :: Cuchar # Cbus Mux control
  Cbus4 :: Cuchar # Cbus Mux control
  Cbus5 :: Cuchar # Cbus Mux control
  Cbus6 :: Cuchar # Cbus Mux control
  Cbus7 :: Cuchar # Cbus Mux control
  Cbus8 :: Cuchar # Cbus Mux control
  Cbus9 :: Cuchar # Cbus Mux control
  # FT1248 options
  FT1248Cpol :: Cuchar # FT1248 clock polarity - clock idle high (1) or clock idle  :: Cuchar #(0)
  FT1248Lsb :: Cuchar # FT1248 data is LSB (1) or MSB (0)
  FT1248FlowControl :: Cuchar # FT1248 flow control enable
  # Hardware options
  IsFifo :: Cuchar # non-zero if interface is 245 FIFO
  IsFifoTar :: Cuchar # non-zero if interface is 245 FIFO CPU target
  IsFastSer :: Cuchar # non-zero if interface is Fast serial
  IsFT1248 :: Cuchar # non-zero if interface is FT1248
  PowerSaveEnable :: Cuchar ## Driver option
  DriverType :: Cuchar #  :: Cuchar #FT X Series EEPROM structure for use with FT_EEPROM_Read and FT_EEPROM_Program
end

type ft_eeprom_x_series
  ### BEGIN common elements for all device EEPROMs ###
  deviceType :: Cuint # FT_DEVICE FTxxxx device type to be programmed
  # Device descriptor options
  VendorId :: Cshort # 0x0403
  ProductId :: Cshort # 0x6001
  SerNumEnable :: Cuchar # non-zero if serial number to be used
  # Config descriptor options
  MaxPower :: Cshort #  0 < MaxPower <= 500
  ### END common elements for all device EEPROMs ###
  # Drive options
  ACSlowSlew :: Cuchar # non-zero if AC bus pins have slow slew
  ACSchmittInput :: Cuchar # non-zero if AC bus pins are Schmitt input
  ACDriveCurrent :: Cuchar # valid values are 4mA, 8mA, 12mA, 16mA
  ADSlowSlew :: Cuchar # non-zero if AD bus pins have slow slew
  ADSchmittInput :: Cuchar # non-zero if AD bus pins are Schmitt input
  ADDriveCurrent :: Cuchar # valid values are 4mA, 8mA, 12mA, 16mA
  # CBUS options
  Cbus0 :: Cuchar # Cbus Mux control
  Cbus1 :: Cuchar # Cbus Mux control
  Cbus2 :: Cuchar # Cbus Mux control
  Cbus3 :: Cuchar # Cbus Mux control
  Cbus4 :: Cuchar # Cbus Mux control
  Cbus5 :: Cuchar # Cbus Mux control
  Cbus6 :: Cuchar # Cbus Mux control
  # UART signal options
  InvertTXD :: Cuchar # non-zero if invert TXD
  InvertRXD :: Cuchar # non-zero if invert RXD
  InvertRTS :: Cuchar # non-zero if invert RTS
  InvertCTS :: Cuchar # non-zero if invert CTS
  InvertDTR :: Cuchar # non-zero if invert DTR
  InvertDSR :: Cuchar # non-zero if invert DSR
  InvertDCD :: Cuchar # non-zero if invert DCD
  InvertRI :: Cuchar # non-zero if invert RI
  # Battery Charge Detect options
  BCDEnable :: Cuchar # Enable Battery Charger Detection
  BCDForceCbusPWREN :: Cuchar # asserts the power enable signal on CBUS when charging port detected
  BCDDisableSleep :: Cuchar # forces the device never to go into sleep mode
  # I2C options
  I2CSlaveAddress :: Cushort # I2C slave device address
  I2CDeviceId :: Cuint # I2C device ID
  I2CDisableSchmitt :: Cuchar # Disable I2C Schmitt trigger
  # FT1248 options
  FT1248Cpol :: Cuchar # FT1248 clock polarity - clock idle high (1) orclock idle low (0)
  FT1248Lsb :: Cuchar # FT1248 data is LSB (1) or MSB (0)
  FT1248FlowControl :: Cuchar # FT1248 flow control enable
  # Hardware options
  RS485EchoSuppress :: Cuchar 
  PowerSaveEnable :: Cuchar ## Driver option
  DriverType :: Cuchar
end

# Win32
const OPEN_EXISTING = 3
const FILE_ATTRIBUTE_NORMAL = 0x00000080
const FILE_FLAG_OVERLAPPED = 0x40000000
const GENERIC_READ = 0x80000000
const GENERIC_WRITE = 0x40000000

const CLRDTR = 6 # – Clear the DTR signal 
const CLRRTS = 4 # – Clear the RTS signal 
const SETDTR = 5 # – Set the DTR signal 
const SETRTS = 3 # – Set the RTS signal 
const SETBREAK = 8 # – Set the BREAK condition 
const CLRBREAK = 9 # – Clear the BREAK condition

const MS_CTS_ON = 0x0010 # – Clear To Send (CTS) is on 
const MS_DSR_ON = 0x0020 # – Data Set Ready (DSR) is on 
const MS_RING_ON = 0x0040 # – Ring Indicator (RI) is on 
const MS_RLSD_ON = 0x0080 # – Receive Line Signal Detect (RLSD) is on

# FTDCB structure
type _FTDCB
  DCBlength :: Cuint # sizeof(FTDCB) 
  BaudRate :: Cuint # Baud rate at which running
  status :: Cuint # fields below 
                  # fBinary: 1;  Binary Mode (skip EOF check) 
                  # fParity: 1;  Enable parity checking
                  # fOutxCtsFlow:1; CTS handshaking on output 
                  # fOutxDsrFlow:1; DSR handshaking on output
                  # fDtrControl:2;  DTR Flow control 
                  # fDsrSensitivity:1; DSR Sensitivity
                  # fTXContinueOnXoff: 1; Continue TX when Xoff sent 
                  # fOutX: 1; Enable output X-ON/X-OFF 
                  # fInX: 1; Enable input X-ON/X-OFF 
                  # fErrorChar: 1; Enable Err Replacement 
                  # fNull: 1; Enable Null stripping
                  # fRtsControl:2; Rts Flow control 
                  # fAbortOnError:1; Abort all reads and writes on Error 
                  # fDummy2:17; Reserved 
  wReserved :: Cushort # Not currently used 
  XonLim :: Cushort # Transmit X-ON threshold
  XoffLim :: Cushort # Transmit X-OFF threshold
  ByteSize :: Cuchar # Number of bits/byte, 7-8 
  Parity :: Cuchar # 0-4=None,Odd,Even,Mark,Space 
  StopBits :: Cuchar # 0,2 = 1, 2
  XonChar :: Cchar # Tx and Rx X-ON character
  XoffChar :: Cchar # Tx and Rx X-OFF character
  ErrorChar :: Cchar # Error replacement char 
  EofChar :: Cchar # End of Input character 
  EvtChar :: Cchar # Received Event character 
  wReserved1 :: Cushort # Fill
end

#FTTIMEOUTS structure 
type _FTTIMEOUTS 
  ReadIntervalTimeout :: Cuint #  Maximum time between read chars 
  ReadTotalTimeoutMultiplier :: Cuint #  Multiplier of characters 
  ReadTotalTimeoutConstant :: Cuint #  Constant in milliseconds 
  WriteTotalTimeoutMultiplier :: Cuint #  Multiplier of characters 
  WriteTotalTimeoutConstant :: Cuint #  Constant in milliseconds
end

const EV_BREAK = 0x0040 # – BREAK condition detected 
const EV_CTS = 0x0008 # – Change in Clear To Send (CTS) 
const EV_DSR = 0x0010 # – Change in Data Set Ready (DSR) 
const EV_ERR = 0x0080 # – Error in line status 
const EV_RING = 0x0100 # – Change in Ring Indicator (RI) 
const EV_RLSD = 0x0020 # – Change in Receive Line Signal Detect (RLSD) 
const EV_RXCHAR = 0x0001 # – Character received 
const EV_RXFLAG = 0x0002 # – Event character received 
const EV_TXEMPTY = 0x0004 # – Transmitter empty

const PURGE_TXABORT = 0x0001 # – Terminate outstanding overlapped writes 
const PURGE_RXABORT = 0x0002 # – Terminate outstanding overlapped reads 
const PURGE_TXCLEAR = 0x0004 # – Clear the transmit buffer 
const PURGE_RXCLEAR = 0x0008 # – Clear the receive buffer

# FTCOMSTAT structure 
type _FTCOMSTAT 
  comstat :: Cuint  # fields below
                    # fCtsHold : 1
                    # fDsrHold : 1
                    # fRlsdHold : 1
                    # fXoffHold : 1
                    # fXoffSent : 1
                    # fEof : 1
                    # fTxim : 1
                    # fReserved : 25
                    # cbInQue
                    # cbOutQue;
end