# ps3000setadvtriggerdelay.jl

export ps3000setadvtriggerdelay

function ps3000setadvtriggerdelay(handle::Int16, delay, pretriggerdelay)
  ps_status = ccall((:ps3000SetAdvTriggerDelay,ps3000driver), Int16,
    (Int16, UInt32, Cfloat),
    handle, delay, pretriggerdelay)
  if ps_status == 0
    error("ps3000 Error: one of the parameters is out of range")
  end
  return nothing
end
