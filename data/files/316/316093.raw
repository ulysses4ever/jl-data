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
  ft_setvidpid(vid,pid)
end

lpdwnumdevs = ft_createdeviceinfolist()
println("$lpdwnumdevs devices found")
dil = ft_getdeviceinfolist(lpdwnumdevs)
println(dil)
println()
show(dil[1])
println()
show(dil)
println()

@test length(dil) > 0

h = ft_open(0)
ft_close(h)

locid = dil[1].locid
h = ft_openex(locid)
ft_close(h)

ftsn = ft_serialnumber(dil[1].serialnumber)
h = ft_openex(ftsn)
ft_close(h)

ftd = ft_description(dil[1].description)
h = ft_openex(ftd)
ft_close(h)

h = ft_openex(ft_serialnumber("FTXRNZUJ"))  # cable with external loopback
ft_setbaudrate(h,9600)
ft_setdatacharacteristics(h, FT_BITS_7, FT_STOP_BITS_1, FT_PARITY_NONE)
ft_settimeouts(h, 1000, 1000)
ft_setflowcontrol(h,FT_FLOW_NONE)
byteswritten = ft_write(h,convert(Array{UInt8,1},"abcd"))
println("$byteswritten bytes written")
bytesinqueue = ft_getqueuestatus(h)
println("$bytesinqueue bytes in queue")
const buffer = Array(UInt8,byteswritten)
bytesreturned = ft_read!(h,buffer,byteswritten)
println("$bytesreturned bytes read")
println(convert(ASCIIString,buffer))

ft_setdtr(h)
ft_clrdtr(h)
ft_setrts(h)
ft_clrrts(h)

ms = ft_getmodemstatus(h)
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
(devicetype, id, serialnumber, description) = ft_getdeviceinfo(h)
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
  driverversion = ft_getdriverversion(h)
  println("ft_getdriverversion = ",driverversion)
  libraryversion = ft_getlibraryversion()
  println("ft_getlibraryversion = $libraryversion")
  comportnumber = ft_getcomportnumber(h)
  println("ft_getcomportnumber = $comportnumber")
end
(rxqueue, txqueue, eventstatus) = ft_getstatus(h)
println("ft_getstatus")
println("in Rx queue = $rxqueue")
println("in Tx queue = $txqueue")
println("event status = $eventstatus")


eventcharacter = 0x01
enableevent = false
errorcharacter = 0x02
enableerror = false
ft_setchars(h,eventcharacter,enableevent, errorcharacter, enableerror)

ft_setbreakon(h)
ft_setbreakoff(h)
ft_purge(h, FT_PURGE_RX & FT_PURGE_TX)



ft_resetdevice(h)
if iswindows
  ft_resetport(h)
  ft_cycleport(h)
  ft_rescan(h)
  if ~iswindows10  # problem with windows 10
    ft_setresetpiperetrycount(h,100)
    ft_setresetpiperetrycount(h,50)  # back to default
  end
end
if ~iswindows10 # problem with windows 10
  ft_stopintask(h) 
  ft_restartintask(h)
  ft_setdeadmantimeout(h,6000)
  ft_setdeadmantimeout(h,5000)  # back to default
end
print("reloading vid=0x")
@printf("%X",vid)
print("    pid=0x")
@printf("%X",pid)
println()
if iswindows & ~iswindows10
  if ~iswindows10 # problem with windows10
    ft_reload(vid,pid)
  end
  ft_resetport(h)
end


ft_close(h)
if iswindows10
  wait(Timer(5))
end

####################################
#
# EEPROM Functions
#
####################################
println()
println("EEPROM testing")
println("opening serial number FTXRNZUJ")
h = ft_openex(ft_serialnumber("FTXRNZUJ"))  # cable with external loopback
# factory description = "C232HM-EDHSL-0"
#
# h = ft_openex(ft_serialnumber("FTX2GPSJ"))  # cable with external loopback
# factory description = "UM232H-B"

word0x00000001 = ft_readee(h,0x00000001)
print("word at EE address 0x00000001 = 0x")
@printf("%X",word0x00000001)
println()

userareasize = ft_ee_uasize(h)
print("user area size = 0x")
@printf("%X",userareasize)
println()

userarea = zeros(UInt8, userareasize)
ft_ee_uaread!(h,userarea)
show(userarea)
println()

for (index,byte) in enumerate(userarea)
  if byte == 255
    userarea[index] = 0
  else
    userarea[index] = byte + 1
  end
end

ft_ee_uawrite(h,userarea)
userarea = zeros(UInt8, userareasize)
ft_ee_uaread!(h,userarea)
show(userarea)
println()
println()


latencytime_ms = ft_getlatencytimer(h)
ltold = latencytime_ms
println("latency time is $latencytime_ms ms")
ft_setlatencytimer(h,10)
latencytime_ms = ft_getlatencytimer(h)
println("latency time is $latencytime_ms ms")
if (ltold>1) & (ltold<256)
  ft_setlatencytimer(h,ltold)
elseif ltold>1
  ft_setlatencytimer(h,256)
else
  ft_setlatencytimer(h,2)
end
latencytime_ms = ft_getlatencytimer(h)
println("latency time is $latencytime_ms ms")

println()
ft_setbitmode(h, 0x00, 0x02)  # mode = MPSSE
ft_setbitmode(h, 0x00, 0x00)  # reset mode
println("ft_setbitmode test complete")

println()
idbv = ft_getbitmode(h)
print("instaneous data bus value = 0x")
@printf("%X",idbv)

println()
intransfersize = 100 * 64
outtransfersize = 101 * 64
ft_setusbparameters(h, intransfersize, outtransfersize)
ft_setusbparameters(h, 4096, 4096)  # back to default
println("ft_setusbparameters test complete")

programdata = ft_ee_read(h)
println("PowerSaveEnableH = ",programdata.PowerSaveEnableH)
programdata.PowerSaveEnableH = 0x00 # turn off power save 
ft_ee_program(h,programdata)
pd2 = ft_ee_read(h)
println("PowerSaveEnableH = ",pd2.PowerSaveEnableH)
pd2.PowerSaveEnableH = 0x01 # turn on power save
ft_ee_program(h,pd2)
pd3 = ft_ee_read(h)
println("PowerSaveEnableH = ",pd3.PowerSaveEnableH)
print(programdata)
ft_eraseee(h) # erase the EEPROM
ft_ee_program(h,pd2) # put data back

word1 = ft_readee(h,0x0001)  # read a byte
ft_writeee(h,0x0001,0x5555)  # write some data
@assert 0x5555 == ft_readee(h,0x0001)
ft_writeee(h,0x0001,word1) # write original value back

if iswindows
  println()
  println("test ft_eeprom_read, ft_eeprom_program start")
  #ee = Fteeprom232h()
  (eepromdata,mfg,mfgid,d,sn) = ft_eeprom_read(h,Fteeprom232h())
  println("mfg=",mfg)
  println("mfgid=",mfgid)
  println("d=",d)
  println("sn=",sn)
  show(eepromdata)
  ft_eeprom_program(h,eepromdata,mfg,mfgid,d,sn)
  println("test ft_eeprom_read, ft_eeprom_program end")
  println()
end

ft_close(h)

if isunix
  (vid,pid) = ft_getvidpid() 
  f()=@printf("VendorId = 0x%04x   ",vid);f() 
  f()=@printf("ProductId = 0x%04x \n",pid);f() 
  ft_setvidpid(0xaaaa,0x5555)
  (vid2,pid2) = ft_getvidpid() 
  f()=@printf("VendorId = 0x%04x   ",vid2);f() 
  f()=@printf("ProductId = 0x%04x \n",pid2);f() 
  ft_setvidpid(vid,pid)
  (vid,pid) = ft_getvidpid() 
  f()=@printf("VendorId = 0x%04x   ",vid);f() 
  f()=@printf("ProductId = 0x%04x \n",pid);f() 
end

# test IO
include("localtestIOftuart.jl")