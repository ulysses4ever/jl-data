export FT_GetBitMode
export ftbitmodedict

ftbitmodedict = Dict(
  FT_BITMODE_RESET => "FT_BITMODE_RESET",
  FT_BITMODE_ASYNC_BITBANG => "FT_BITMODE_ASYNC_BITBANG",
  FT_BITMODE_MPSSE => "FT_BITMODE_MPSSE",
  FT_BITMODE_SYNC_BITBANG => "FT_BITMODE_SYNC_BITBANG",
  FT_BITMODE_MCU_HOST => "FT_BITMODE_MCU_HOST",
  FT_BITMODE_FAST_SERIAL => "FT_BITMODE_FAST_SERIAL",
  FT_BITMODE_CBUS_BITBANG => "FT_BITMODE_CBUS_BITBANG",
  FT_BITMODE_SYNC_FIFO => "FT_BITMODE_SYNC_FIFO")

function FT_GetBitMode(ft_handle::UInt32)
  mode = Ref{Cuchar}()
  ft_status = ccall((:FT_GetBitMode, "ftd2xx.dll"),
                     Culong,
                     (Culong, Ref{Cuchar}),
                     ft_handle, mode)
  checkstatus(ft_status)
  return convert(UInt8, mode[])
end 