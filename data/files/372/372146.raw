# test IOftuart type
using FTD2XX
using Base.Test

# assume at least ont device is attached
deviceinfo = ft_getdeviceinfolist()[1]

# open by description
io = open(FT_Description(deviceinfo.description))
close(io)

# open by serial number
io = open(FT_SerialNumber(deviceinfo.serialnumber))
close(io)

# open by location
io = open(FT_Location(deviceinfo.locid))
close(io)

# open by index (zero based)
io = open(FT_DeviceIndex(0))

# assume external loopback is connected
write(io, 0x55)
@test read(io, UInt8) == 0x55

write(io, "hello world")
@test readuntil(io, "d") == "hello world"  # carefull, eof == true always

testvector = [0x44, 0x67, 0x88, 0x01, 0xab]
write(io, testvector)
readbuffer = zeros(UInt8,length(testvector))
read!(io, readbuffer)
@test testvector == readbuffer

close(io)

