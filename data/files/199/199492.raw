# ps3000_stop.jl

export ps3000_stop

function ps3000_stop(handle:: Int16)
  ps_status = ccall((:ps3000_stop, ps3000driver), Int16,(Int16,),handle)
  if ps_status == 0
    error("ps3000 Error: Handle Not Valid")
  end
  return nothing
end