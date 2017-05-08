# ps4000openunit.jl

export ps4000openunit

function ps4000openunit()
  handle = Ref{UInt16}()
  ps_status = ccall((:ps4000OpenUnit, ps4000driver),
                  PicoStatus,
                  (Ref{UInt16},),
                  handle)
  return handle[]
end