# ps4000enumerateunits.jl

export ps4000enumerateunits

function ps4000enumerateunits()
  count = Ref{UInt16}()
  serials = Array(UInt8, 32)
  serials[1] = 1  # make sure not null 
  seriallength = Ref{UInt16}(32)
  ps_status = ccall((:ps4000EnumerateUnits, ps4000driver),
          PicoStatus,
          (Ref{UInt16},Ptr{UInt8},Ref{UInt16}),
          count,serials,seriallength)
  checkps_status(ps_status)
  serials[end] = 0
  return (count[], serials, seriallength[])
end