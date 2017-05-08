# test IOftuart type
using FTD2XX
using Base.Test

# assume at least ont device is attached
deviceinfo = ft_getdeviceinfolist()[1]

# open by description
io = open(ft_description(deviceinfo.description))
close(io)

# open by serial number
io = open(ft_serialnumber(deviceinfo.serialnumber))
close(io)

# open by location
io = open(ft_location(deviceinfo.locid))
close(io)

# open by index (zero based)
io = open(ft_deviceindex(0))

# assume external loopback is connected
write(io, 0x55)
@test read(io, UInt8) == 0x55

write(io, "hello world")
@test readuntil(io, "d") == "hello world"  # carefull, eof == true always

close(io)

