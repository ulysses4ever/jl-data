export FT_SetEventNotification
export FT_EVENT_RXCHAR, FT_EVENT_MODEM_STATUS
export FT_EVENT_LINE_STATUS

#Notification Events (see FT_SetEventNotification) 
const FT_EVENT_RXCHAR = 1 
const FT_EVENT_MODEM_STATUS = 2 
const FT_EVENT_LINE_STATUS = 4


function FT_SetEventNotification(ft_handle::Culong, eventmask::Integer)
#=
What do I do here ????

const _k32 = "Kernel32.dll"
hevent = ccall((:CreateEventW,_k32),
              Culonglong, 
              (Cchar, Cchar, Cchar, Ptr{UInt8}),
              C_NULL,0x00,0x00,"")


=#
end