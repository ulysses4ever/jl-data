# ps3000_open_unit.jl

export ps3000_open_unit

function ps3000_open_unit()
  ps_status = ccall((:ps3000_close_unit, ps3000driver),Int16,(),) 
  if ps_status == -1
    error("ps3000 Error: Failed To Open")
  end
  return ps_status 
end