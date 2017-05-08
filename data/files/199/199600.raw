# ps3000_close_unit

export ps3000_close_unit

function ps3000_close_unit(handle::Int16)
  ps_status = ccall((:ps3000_close_unit, ps3000driver),
                  UInt16,
                  (Int16,),
                  handle)
  if ps_status == 0
    error("ps3000 Error: Handle Not Valid")
  end
  return nothing
end
