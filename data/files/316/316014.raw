# tests require FTDI devices attached to computer

using FTD2XX
using Base.Test 

lpdwnumdevs = FT_CreateDeviceInfoList()
println("$lpdwnumdevs devices found")
dil = FT_GetDeviceInfoList(lpdwnumdevs)
