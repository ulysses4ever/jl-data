export ft_seteventnotification
export FT_EVENT_RXCHAR, FT_EVENT_MODEM_STATUS
export FT_EVENT_LINE_STATUS

#Notification Events (see ft_seteventnotification) 
const FT_EVENT_RXCHAR = 1 
const FT_EVENT_MODEM_STATUS = 2 
const FT_EVENT_LINE_STATUS = 4


function ft_seteventnotification(ft_handle::Culong,
                                 event_mask::Integer,
                                 event_handle::Culong)
  eh = Ref{Culong}(event_handle)
  ft_status = ccall((:FT_SetEventNotification, d2xx),
                   Cuint,
                   (Culong, Cuint,Ref{Culong}),
                   ft_handle, event_mask, eh)
  checkstatus(ft_status)
  return nothing
end

#=
const _k32 = "Kernel32.dll"
hevent = ccall((:CreateEventW,_k32),
              Culonglong, 
              (Cchar, Cchar, Cchar, Ptr{UInt8}),
              C_NULL,0x00,0x00,"")


=#