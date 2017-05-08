# ps3000_open_unit_async.jl

export ps3000_open_unit_async

function ps3000_open_unit_async()
  open_unit_async_status = ccall(:ps3000_open_unit_async, ps3000driver), Int16, ())
  return open_unit_async_status
end

#=
open_unit_async_status
0 if there is a previous open operation in progress
1 if the call has successfully initiated an open operation
=#
