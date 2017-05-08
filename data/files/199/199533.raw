# ps3000_get_unit_info.jl

export ps3000_get_unit_info, PS3000GetUnitInfoLine

function ps3000_get_unit_info(handle :: Int16,
                              line)
  string = Array(UInt8,32)
  returned_string_length = ccall((:ps3000_get_unit_info, ps3000driver), Int16,
    (Int16, Ptr{UInt8}, Int16, Int16),
    handle, string, length(string), line)
  if returned_string_length == 0
    error("ps3000 Error: Parameter Out Of Range")
  end
  return bytestring(string[1:returned_string_length])
end

function ps3000_get_unit_info(handle :: Int16)
  info = Array(ASCIIString,6)
  for line in Int16(1):Int16(6)
    info[line] = ps3000_get_unit_info(handle,line)
  end
  return info
end

baremodule PS3000GetUnitInfoLine
  const PS3000_DRIVER_VERSION = 0
  const PS3000_USB_VERSION = 1
  const PS3000_HARDWARE_VERSION = 2
  const PS3000_VARIANT_INFO = 3
  const PS3000_BATCH_AND_SERIAL = 4
  const PS3000_CAL_DATE = 5
  const PS3000_ERROR_CODE = 6   # see PS3000DriverErrorCodes
end