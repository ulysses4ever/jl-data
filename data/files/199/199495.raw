# ps3000_set_channel.jl

export ps3000_set_channel, PS3000Channel, PS3000Range

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
  const A = 0
  const B = 1
  const C = 2
  const D = 3
end # module

baremodule PS3000Range
  const mV20 = 1  # +/-20mV
  const mV50 = 2  # +/-50mV
  const mV100 = 3 # +/- 100mV
  const mV200 = 4  # +/- 200mV
  const mV500 = 5  # +/- 500mV
  const V1 = 6 # +/- 1V
  const V2 = 7 # +/- 2V
  const V5 = 8 # +/- 5V
  const V10 = 9 # +/- 10V
  const V20 = 10 # +/- 20V
  const V50 = 11 # +/- 50V
  const V100 = 12 # +/- 100V
  const V200 = 13 # +/- 200V
  const V400 = 14 # +/- 400V
end # module