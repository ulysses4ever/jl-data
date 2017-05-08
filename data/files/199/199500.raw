# ps3000_ready.jl

export ps3000_ready

function ps3000_ready(handle ::Int16)
  # returns true if device is ready
  is_ready = ccall((:ps3000_ready, ps3000driver), Int16, (Int16,),handle)
  if is_ready == -1
    error("ps3000 Error: device not attached")
  end
  return is_ready==0?false:true
end
