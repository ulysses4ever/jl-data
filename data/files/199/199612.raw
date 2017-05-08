# ps4000closeunit.jl

export ps4000closeunit

function ps4000closeunit(handle::UInt16)
  status = ccall((:ps4000CloseUnit, ps4000driver),
                  PicoStatus,
                  (UInt16,),
                  handle)
  checkstatus(status)
  return nothing
end