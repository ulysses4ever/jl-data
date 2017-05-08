export FT_SetBitMode
export FT_BITMODE_RESET, FT_BITMODE_ASYNC_BITBANG
export FT_BITMODE_MPSSE, FT_BITMODE_SYNC_BITBANG
export FT_BITMODE_MCU_HOST, FT_BITMODE_FAST_SERIAL
export FT_BITMODE_CBUS_BITBANG, FT_BITMODE_SYNC_FIFO

#Bit Modes (see FT_SetBitMode) 
const FT_BITMODE_RESET = 0x00 
const FT_BITMODE_ASYNC_BITBANG = 0x01 
const FT_BITMODE_MPSSE = 0x02 
const FT_BITMODE_SYNC_BITBANG = 0x04 
const FT_BITMODE_MCU_HOST = 0x08 
const FT_BITMODE_FAST_SERIAL = 0x10
const FT_BITMODE_CBUS_BITBANG = 0x20 
const FT_BITMODE_SYNC_FIFO = 0x40

function FT_SetBitMode(ft_handle::UInt32, mask::UInt8, mode::UInt8)
  @assert mode in keys(ftbitmodedict)
  ft_status = ccall((:FT_SetBitMode, d2xx),
                     Cuint,
                     (Cuint, Cuchar, Cuchar),
                     ft_handle, mask, mode)
  checkstatus(ft_status)
  return nothing
end