# tests require FTDI devices attached to computer

# unload VCP driver for linux
try
  @linux? sudo rmmod ftdi_sio : nothing
  @linux? sudo rmmod usbserial : nothing
end

using FTD2XX
using Base.Test 

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
byteswritten = FT_Write(h,"abcd")
println("$byteswritten bytes written")
bytesinqueue = FT_GetQueueStatus(h)
println("$bytesinqueue bytes in queue")
(bytesreturned,buffer) = FT_Read(h,byteswritten)
println("$bytesreturned bytes read")
println(buffer)

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

@windows? driverversion = FT_GetDriverVersion(h) : nothing
@windows? println("FT_GetDriverVersion = $driverversion") : nothing
@windows? libraryversion = FT_GetLibraryVersion() : nothing
@windows? println("FT_GetLibraryVersion = $libraryversion") : nothing
@windows? comportnumber = FT_GetComPortNumber(h) : nothing
@windows? println("FT_GetComPortNumber = $comportnumber") : nothing
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
@windows? FT_ResetPort(h):nothing
@windows? FT_CyclePort(h):nothing
@windows? FT_Rescan(h):nothing
FT_SetResetPipeRetryCount(h,100)
FT_SetResetPipeRetryCount(h,50)  # back to default
FT_StopInTask(h)
FT_RestartInTask(h)
FT_SetDeadmanTimeout(h,6000)
FT_SetDeadmanTimeout(h,5000)  # back to default
print("reloading vid=0x")
@printf("%X",vid)
print("    pid=0x")
@printf("%X",pid)
println()
@windows? FT_Reload(vid,pid):nothing
FT_ResetPort(h)


FT_Close(h)


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
FT_SetLatencyTimer(h,ltold)
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

FT_EraseEE(h) # erase the EEPROM
FT_EE_Program(h,pd2) # put data back

word1 = FT_ReadEE(h,0x0001)  # read a byte
FT_WriteEE(h,0x0001,0x5555)  # write some data
@assert 0x5555 == FT_ReadEE(h,0x0001)
FT_WriteEE(h,0x0001,word1) # write original value back 

FT_Close(h)

(vid,pid) = @unix? FT_GetVIDPID() : (nothing,nothing)
println("vid = ",vid,"   pid = ",pid)
@unix? FT_SetVIDPID(0x5555aaaa,0xaaaa5555) : nothing
(vid2,pid2) = @unix? FT_GetVIDPID() : (nothing,nothing)
println("vid = ",vid2,"   pid = ",pid2)
@unix? FT_SetVIDPID(vid,pid) : nothing


