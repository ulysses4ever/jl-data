# ps3000SetAdvTriggerDelay.jl

export ps3000SetAdvTriggerDelay

function ps3000SetAdvTriggerDelay(handle::Int16, delay, pretriggerdelay)
  ps_status = ccall((:ps3000SetAdvTriggerDelay,ps3000driver), Int16,
    (Int16, UInt32, Float64),
    handle, delay, pretriggerdelay)
  if ps_status == 0
    error("ps3000 Error: one of the parameters is out of range")
  end
  return nothing
end
