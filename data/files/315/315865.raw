export FT_GetModemStatus
export CTS,DSR,RI,DCD
export OE,PE,FE,BI

#Modem Status (see FT_GetModemStatus) 
const CTS = 0x10 
const DSR = 0x20 
const RI = 0x40 
const DCD = 0x80

#Line Status (see FT_GetModemStatus) 
const OE = 0x02 
const PE = 0x04 
const FE = 0x08 
const BI = 0x10

function FT_GetModemStatus(ft_handle::UInt32)
  modemstatus = Ref{Culong}()
  ft_status = ccall((:FT_GetModemStatus, "ftd2xx.dll"),
                     Culong,
                     (Culong, Ref{Culong}),
                     ft_handle, modemstatus)
  checkstatus(ft_status)
  return convert(UInt32,modemstatus[])
end 