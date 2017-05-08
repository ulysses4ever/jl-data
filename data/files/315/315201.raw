export ft_getmodemstatus
export CTS,DSR,RI,DCD
export OE,PE,FE,BI

#Modem Status (see ft_getmodemstatus) 
const CTS = 0x10 
const DSR = 0x20 
const RI = 0x40 
const DCD = 0x80

#Line Status (see ft_getmodemstatus) 
const OE = 0x02 
const PE = 0x04 
const FE = 0x08 
const BI = 0x10

function ft_getmodemstatus(ft_handle::Culong)
  modemstatus = Ref{Cuint}()
  ft_status = ccall((:FT_GetModemStatus, d2xx),
                     Cuint,
                     (Culong, Ref{Cuint}),
                     ft_handle, modemstatus)
  checkstatus(ft_status)
  return modemstatus[]
end 