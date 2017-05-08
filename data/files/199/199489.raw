# ps3000_set_trigger.jl

export ps3000_set_trigger, ps3000_set_trigger2

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
return

baremodule PS3000Source
  const PS3000_CHANNEL_A = 0
  const PS3000_CHANNEL_B = 1
  const PS3000_CHANNEL_C = 2
  const PS3000_CHANNEL_D = 3
  const PS3000_EXTERNAL  = 4
  const PS3000_NONE      = 5
end # module

baremodule PS3000Direction
  const PS3000_RISING = 0
  const PS3000_FALLING = 1
end
