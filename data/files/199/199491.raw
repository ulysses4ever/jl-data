# ps3000_set_trigger.jl

export ps3000_set_trigger, ps3000_set_trigger2, PS3000Source, PS3000Direction

function ps3000_set_trigger(handle::Int16, source, threshold, direction, 
                             delay::Int, auto_trigger_ms)
  ps_status = ccall((:ps3000_set_trigger, ps3000driver), Int16,
    (Int16, Int16, Int16, Int16, Int16, Int16),
    handle, source, threshold, direction, delay, auto_trigger_ms)
  if ps_status == 0
    error("ps3000 Error: one of the parameters is out of range")
  end
  return nothing
end


function ps3000_set_trigger(handle::Int16, source, threshold, direction, 
                             delay, auto_trigger_ms)
  ps_status = ccall((:ps3000_set_trigger2, ps3000driver), Int16,
    (Int16, Int16, Int16, Int16, Cfloat, Int16),
    handle, source, threshold, direction, delay, auto_trigger_ms)
  if ps_status == 0
    error("ps3000 Error: one of the parameters is out of range")
  end
  return nothing
end

function ps3000_set_trigger2(handle::Int16, source, threshold, direction, 
                             delay, auto_trigger_ms)
  ps3000_set_trigger(handle::Int16, source, threshold, direction, 
                     delay, auto_trigger_ms)
end

baremodule PS3000Source
  const CHANNEL_A = 0
  const CHANNEL_B = 1
  const CHANNEL_C = 2
  const CHANNEL_D = 3
  const EXTERNAL  = 4
  const NONE      = 5
end # module

baremodule PS3000Direction
  const RISING = 0
  const FALLING = 1
end
