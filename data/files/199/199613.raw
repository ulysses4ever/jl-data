# ps4000closeunit.jl

export ps4000closeunit

function ps4000closeunit(handle::UInt16)
  ps_status = ccall((:ps4000CloseUnit, ps4000driver),
                  PicoStatus,
                  (UInt16,),
                  handle)
  checkps_status(ps_status)
  return nothing
end