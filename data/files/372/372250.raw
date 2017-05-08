export FT_EEPROM_Read, FT_EEPROM_Program

include("FT_DEVICE.jl")  # load constants

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
