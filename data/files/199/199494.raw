# ps3000_set_channel.jl

export ps3000_set_channel

function ps3000_set_channel(handle::Int16, channel, enabled, dc, range)
  ps_status = ccall((:ps3000_set_channel, ps3000driver), Int16,
    (Int16, Int16, Int16, Int16, Int16), handle, channel, enabled, dc, range)
  if ps_status == 0
    error("ps3000 Error: one or more of the arguments are out of range")
  end
  return nothing
end

function ps3000_set_channel(handle::Int16, channel, enabled::Bool, dc::Bool, range)
  ps3000_set_channel(handle::Int16, channel, enabled?0x0001:0x0000,
                     dc?0x0001:0x0000, range)
end

baremodule PS3000Channel
  const PS3000_CHANNEL_A = 0
  const PS3000_CHANNEL_B = 1
  const PS3000_CHANNEL_C = 2
  const PS3000_CHANNEL_D = 3
end # module

baremodule PS3000Range
  const PS3000_20MV = 1  # +/-20mV
  const PS3000_50MV = 2  # +/-50mV
  const PS3000_100MV = 3 # +/- 100mV
  const PS3000_200MV = 4  # +/- 200mV
  const PS3000_500MV = 5  # +/- 500mV
  const PS3000_1V = 6 # +/- 1V
  const PS3000_2V = 7 # +/- 2V
  const PS3000_5V = 8 # +/- 5V
  const PS3000_10V = 9 # +/- 10V
  const PS3000_20V = 10 # +/- 20V
  const PS3000_50V = 11 # +/- 50V
  const PS3000_100V = 12 # +/- 100V
  const PS3000_200V = 13 # +/- 200V
  const PS3000_400V = 14 # +/- 400V
end # module