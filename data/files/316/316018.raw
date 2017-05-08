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
FT_SetBaudRate(h,9600)
byteswritten = FT_Write(h,"abcd")
println("$byteswritten bytes written")
(bytesreturned,buffer) = FT_Read(h,byteswritten)
println("$bytesreturned bytes read")
println(buffer)


FT_Close(h)
