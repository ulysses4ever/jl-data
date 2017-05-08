export ft_setflowcontrol

export FT_FLOW_NONE, FT_FLOW_RTS_CTS, FT_FLOW_DTR_DSR, FT_FLOW_XON_XOFF

#Flow Control (see ft_setflowcontrol) 
const FT_FLOW_NONE = 0x0000 
const FT_FLOW_RTS_CTS = 0x0100 
const FT_FLOW_DTR_DSR = 0x0200 
const FT_FLOW_XON_XOFF = 0x0400

function ft_setflowcontrol(ft_handle::Culong, flowcontrol::Integer,
                           xon::UInt8 = 0x11, xoff::UInt8 = 0x13)
  @assert flowcontrol == FT_FLOW_NONE ||
          flowcontrol == FT_FLOW_RTS_CTS ||
          flowcontrol == FT_FLOW_DTR_DSR ||
          flowcontrol == FT_FLOW_XON_XOFF "invalid flow control"
  ft_status = ccall((:FT_SetFlowControl, d2xx),
                     Cuint,
                     (Culong, Cushort, Cuchar, Cuchar),
                     ft_handle, flowcontrol, xon, xoff)
  checkstatus(ft_status)
  return nothing
end 