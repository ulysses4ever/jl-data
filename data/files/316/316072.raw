# tests require FTDI devices attached to computer
# start julia with sudo julia on linux
# or read the comments below

# https://www.ikalogic.com/ftdi-d2xx-linux-overcoming-big-problem/
#=
Normally your *.rules file would contain this line:
ATTRS{idVendor}==”0403″, ATTRS{idProduct}==”6014″, MODE=”0666″
This line will make your device accessible from applications that do not have super user rights (i.e. normal users, not administrators)
Simply add this line to tell the kernel to unbind the ftdi_sio (usb to serial port driver) from your device:
[alert type=”primary” display=”inline”]ATTRS{idVendor}==”0403″, ATTRS{idProduct}==”6014″, ATTRS{product}==”PRODUCT_NAME”, RUN+=”/bin/sh -c ‘echo $kernel > /sys/bus/usb/drivers/ftdi_sio/unbind'”[/alert]
(this is a single line, even though it might appear here as 2 lines)
The idea to differentiate between various FTDI devices using the product name defined in the USB descriptor.  Once the product named “PRODUCT_NAME” is detected, the shell command above is run, which will effectively unbind the ftdi_sio and your USB device!
And voila! please don’t hesitate to post comments or ideas. I hope this post could help others.
=#

#http://www.linuxforums.org/forum/programming-scripting/112331-usb-ftdi-d2xx-drivers.html
#=
As far a permissions, you should try to make your own rule in /etc/udev/rules.d
This would be for a 2.6 kernel. I wanted to access my USB devices with libusb and could not read them unless I was logged in as root. I picked a rule number and added this rule:
ATTR{idVendor}=="0D7D", ATTR{idProduct}=="1400", MODE="0666"
The idVendor and idProduct are for my USB drive. When I ran my code I was able to read the device.
=#

#https://kenai.com/projects/javaftd2xx/pages/Home
#=
Why can't I list/open/write the ftdi devices under linux?
You should be sure that you have permission to write to the chip. (/dev/bus/usb/[BUS]/[DEVICE], you can determinate the exact location by lsusb). By default you will not have permission, so you must chown it every time when you physically connect, or make an UDEV rule: this way.
You must fit idVendor and idProduct values to ftdi's, using lsusb. For example a device:
Bus 004 Device 003: ID (this is idVendor-->)0b38:0003(<--this is idProduct) ...
=#
const isunix = @unix? true:false
const isosx = @osx? true:false
const islinux = @linux? true:false
const iswindows = @windows? true:false
const iswindows10 = true

# unload VCP driver for linux
if islinux
  try
    run(`sudo rmmod ftdi_sio`)
    run(`sudo rmmod usbserial`)
  end
end

using FTD2XX
using Base.Test 

if islinux
  vid = 0x0403
  pid = 0x6014
  FT_SetVIDPID(vid,pid)
end

lpdwnumdevs = FT_CreateDeviceInfoList()
println("$lpdwnumdevs devices found")
dil = FT_GetDeviceInfoList(lpdwnumdevs)
println(dil)
println()
show(dil[1])
println()
show(dil)
println()

@test length(dil) > 0

h = FT_Open(0)
FT_Close(h)

# need to fix this !!!!!
#locid = dil[1].locid
#h = FT_OpenEx(locid)
#FT_Close(h)

ftsn = FT_SerialNumber(dil[1].serialnumber)
h = FT_OpenEx(ftsn)
FT_Close(h)

ftd = FT_Description(dil[1].description)
h = FT_OpenEx(ftd)
FT_Close(h)

h = FT_OpenEx(FT_SerialNumber("FTXRNZUJ"))  # cable with external loopback
FT_SetBaudRate(h,9600)
FT_SetDataCharacteristics(h, FT_BITS_7, FT_STOP_BITS_1, FT_PARITY_NONE)
FT_SetTimeouts(h, 1000, 1000)
FT_SetFlowControl(h,FT_FLOW_NONE)
byteswritten = FT_Write(h,convert(Array{UInt8,1},"abcd"))
println("$byteswritten bytes written")
bytesinqueue = FT_GetQueueStatus(h)
println("$bytesinqueue bytes in queue")
(bytesreturned,buffer) = FT_Read(h,byteswritten)
println("$bytesreturned bytes read")
println(convert(ASCIIString,buffer))

FT_SetDtr(h)
FT_ClrDtr(h)
FT_SetRts(h)
FT_ClrRts(h)

ms = FT_GetModemStatus(h)
modemstatus = convert(UInt8,ms&0x00ff)
linestatus = convert(UInt8,(ms&0xff00)>>8)
print("modem status = 0x")
@printf("%X",modemstatus)
println()
modemstatus&CTS == CTS ? println("CTS set") : nothing
modemstatus&DSR == DSR ? println("DSR set") : nothing
modemstatus&RI == RI ? println("RI set") : nothing
modemstatus&DCD == DCD ? println("DCD set") : nothing
print("line status = 0x")
@printf("%X",linestatus)
println()
linestatus&OE == OE ? println("Overrun Error") : nothing
linestatus&PE == PE ? println("Parity Error") : nothing
linestatus&FE == FE ? println("Framing Error") : nothing
linestatus&BI == BI ? println("Break Interupt") : nothing
(devicetype, id, serialnumber, description) = FT_GetDeviceInfo(h)
vid = convert(UInt16, (0xffff0000&id)>>16)
pid = convert(UInt16, 0x0000ffff&id)
println("Device info from FT_GetDevice_Info")
println("device type= $devicetype")
print("id = 0x")
@printf("%X",id)
print("    vid = 0x")
@printf("%X",vid)
print("    pid = 0x")
@printf("%X",pid)
println()
println("serial number = $serialnumber")
println("description = $description")

if iswindows
  driverversion = FT_GetDriverVersion(h)
  println("FT_GetDriverVersion = ",driverversion)
  libraryversion = FT_GetLibraryVersion()
  println("FT_GetLibraryVersion = $libraryversion")
  comportnumber = FT_GetComPortNumber(h)
  println("FT_GetComPortNumber = $comportnumber")
end
(rxqueue, txqueue, eventstatus) = FT_GetStatus(h)
println("FT_GetStatus")
println("in Rx queue = $rxqueue")
println("in Tx queue = $txqueue")
println("event status = $eventstatus")


eventcharacter = 0x01
enableevent = false
errorcharacter = 0x02
enableerror = false
FT_SetChars(h,eventcharacter,enableevent, errorcharacter, enableerror)

FT_SetBreakOn(h)
FT_SetBreakOff(h)
FT_Purge(h, FT_PURGE_RX & FT_PURGE_TX)



FT_ResetDevice(h)
if iswindows
  FT_ResetPort(h)
  FT_CyclePort(h)
  FT_Rescan(h)
  if ~iswindows10  # problem with windows 10
    FT_SetResetPipeRetryCount(h,100)
    FT_SetResetPipeRetryCount(h,50)  # back to default
  end
end
if ~iswindows10 # problem with windows 10
  FT_StopInTask(h) 
  FT_RestartInTask(h)
  FT_SetDeadmanTimeout(h,6000)
  FT_SetDeadmanTimeout(h,5000)  # back to default
end
print("reloading vid=0x")
@printf("%X",vid)
print("    pid=0x")
@printf("%X",pid)
println()
if iswindows & ~iswindows10
  if ~iswindows10 # problem with windows10
    FT_Reload(vid,pid)
  end
  FT_ResetPort(h)
end


FT_Close(h)
wait(Timer(5))

####################################
#
# EEPROM Functions
#
####################################
println()
println("EEPROM testing")
println("opening serial number FTXRNZUJ")
h = FT_OpenEx(FT_SerialNumber("FTXRNZUJ"))  # cable with external loopback
# factory description = "C232HM-EDHSL-0"
#
# h = FT_OpenEx(FT_SerialNumber("FTX2GPSJ"))  # cable with external loopback
# factory description = "UM232H-B"

word0x00000001 = FT_ReadEE(h,0x00000001)
print("word at EE address 0x00000001 = 0x")
@printf("%X",word0x00000001)
println()

userareasize = FT_EE_UASize(h)
print("user area size = 0x")
@printf("%X",userareasize)
println()

userarea = zeros(UInt8, userareasize)
FT_EE_UARead!(h,userarea)
show(userarea)
println()

for (index,byte) in enumerate(userarea)
  if byte == 255
    userarea[index] = 0
  else
    userarea[index] = byte + 1
  end
end

FT_EE_UAWrite(h,userarea)
userarea = zeros(UInt8, userareasize)
FT_EE_UARead!(h,userarea)
show(userarea)
println()
println()


latencytime_ms = FT_GetLatencyTimer(h)
ltold = latencytime_ms
println("latency time is $latencytime_ms ms")
FT_SetLatencyTimer(h,10)
latencytime_ms = FT_GetLatencyTimer(h)
println("latency time is $latencytime_ms ms")
if (ltold>1) & (ltold<256)
  FT_SetLatencyTimer(h,ltold)
elseif ltold>1
  FT_SetLatencyTimer(h,256)
else
  FT_SetLatencyTimer(h,2)
end
latencytime_ms = FT_GetLatencyTimer(h)
println("latency time is $latencytime_ms ms")

println()
FT_SetBitMode(h, 0x00, 0x02)  # mode = MPSSE
FT_SetBitMode(h, 0x00, 0x00)  # reset mode
println("FT_SetBitMode test complete")

println()
idbv = FT_GetBitMode(h)
print("instaneous data bus value = 0x")
@printf("%X",idbv)

println()
intransfersize = 100 * 64
outtransfersize = 101 * 64
FT_SetUSBParameters(h, intransfersize, outtransfersize)
FT_SetUSBParameters(h, 4096, 4096)  # back to default
println("FT_SetUSBParameters test complete")

programdata = FT_EE_Read(h)
println("PowerSaveEnableH = ",programdata.PowerSaveEnableH)
programdata.PowerSaveEnableH = 0x00 # turn off power save 
FT_EE_Program(h,programdata)
pd2 = FT_EE_Read(h)
println("PowerSaveEnableH = ",pd2.PowerSaveEnableH)
pd2.PowerSaveEnableH = 0x01 # turn on power save
FT_EE_Program(h,pd2)
pd3 = FT_EE_Read(h)
println("PowerSaveEnableH = ",pd3.PowerSaveEnableH)
print(programdata)

FT_EraseEE(h) # erase the EEPROM
FT_EE_Program(h,pd2) # put data back

word1 = FT_ReadEE(h,0x0001)  # read a byte
FT_WriteEE(h,0x0001,0x5555)  # write some data
@assert 0x5555 == FT_ReadEE(h,0x0001)
FT_WriteEE(h,0x0001,word1) # write original value back

if iswindows
  println()
  println("test FT_EEPROM_Read, FT_EEPROM_Program start")
  ee = ft_eeprom_232h()
  (mfg,mfgid,d,sn,eepromdata) = FT_EEPROM_Read(h,ee)
  println("mfg=",mfg)
  println("mfgid=",mfgid)
  println("d=",d)
  println("sn=",sn)
  show(eepromdata)
  FT_EEPROM_Program(h,eepromdata,mfg,mfgid,d,sn)
  println("test FT_EEPROM_Read, FT_EEPROM_Program end")
  println()
end

FT_Close(h)

if isunix
  (vid,pid) = FT_GetVIDPID() 
  f()=@printf("VendorId = 0x%04x   ",vid);f() 
  f()=@printf("ProductId = 0x%04x \n",pid);f() 
  FT_SetVIDPID(0xaaaa,0x5555)
  (vid2,pid2) = FT_GetVIDPID() 
  f()=@printf("VendorId = 0x%04x   ",vid2);f() 
  f()=@printf("ProductId = 0x%04x \n",pid2);f() 
  FT_SetVIDPID(vid,pid)
  (vid,pid) = FT_GetVIDPID() 
  f()=@printf("VendorId = 0x%04x   ",vid);f() 
  f()=@printf("ProductId = 0x%04x \n",pid);f() 
end


