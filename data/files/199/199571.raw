# ps3000_flash_led.jl

export ps3000_flash_led

function ps3000_flash_led(handle::Int16)
  ps_status = ccall((:ps3000_flash_led, ps3000driver),
                  UInt16,
                  (Int16,),
                  handle)
  if ps_status == 0
    error("ps3000 Error: Handle Not Valid")
  end
  return nothing
end