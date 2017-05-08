# tests require FTDI devices attached to computer

using FTD2XX
using Base.Test 

lpdwnumdevs = FT_CreateDeviceInfoList()
println("$lpdwnumdevs devices found")
dil = FT_GetDeviceInfoList(lpdwnumdevs)
println(dil)

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

driverversion = FT_GetDriverVersion(h)
println("FT_GetDriverVersion = $driverversion")
libraryversion = FT_GetLibraryVersion()
println("FT_GetLibraryVersion = $libraryversion")
comportnumber = FT_GetComPortNumber(h)
println("FT_GetComPortNumber = $comportnumber")
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
FT_ResetPort(h)
FT_CyclePort(h)
FT_Rescan(h)
FT_SetResetPipeRetryCount(h,100)
FT_SetResetPipeRetryCount(h,50)  # back to default
FT_StopInTask(h)
FT_RestartInTask(h)
FT_SetDeadmanTimeout(h,6000)
FT_SetDeadmanTimeout(h,5000)  # back to default

####################################
#
# EEPROM Functions
#
####################################


print("reloading vid=0x")
@printf("%X",vid)
print("    pid=0x")
@printf("%X",pid)
println()
FT_Reload(vid,pid)

FT_ResetPort(h)

FT_Close(h)
