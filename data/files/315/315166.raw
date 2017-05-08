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
uartconfig1 = UARTConfiguration(921600,8,1,"n",readtimeout = 1000,writetimeout = 1000)
uartconfig2 = UARTConfiguration(9600,8,1,"n",readtimeout = 100,writetimeout = 100)
io = open(FT_DeviceIndex(0),uartconfig1)

wait(Timer(0.1))  # why do I need this?

# assume external loopback is connected
for i in 1:50
  write(io, 0x55)
  @test read(io, UInt8) == 0x55

  write(io, "hello world")
  @test readuntil(io, "d") == "hello world"  # carefull, eof == true always

  testvector = [0x44, 0x67, 0x88, 0x01, 0xab]
  byteswritten = write(io, testvector)
  @test byteswritten == length(testvector)
  readbuffer = zeros(UInt8,length(testvector))
  read!(io, readbuffer)
  @test testvector == readbuffer
  print(i%10)
end
println()

close(io)