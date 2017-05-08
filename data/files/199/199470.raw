# ps3000setpulsewidthqualifier.jl

export ps3000setpulsewidthqualifier, PWType, PWQConditions 

immutable PWQConditions
  a :: Int16
  b :: Int16
  c :: Int16 
  d :: Int16
  ext :: Int16
end

baremodule PWType
  const NONE = 0x0000
  const LESS_THAN = 0x0001
  const GREATER_THAN = 0x0002 
  const IN_RANGE = 0x0003
  const OUT_OF_RANGE = 0x0004
end

# use PS3000TriggerState for a,b,c,d,ext
#=
CONDITION_DONT_CARE (0)
CONDITION_TRUE (1)
CONDITION_FALSE (2)
=#

function ps3000setpulsewidthqualifier(handle :: Int16,
                                      conditions :: PWQConditions,
                                      direction,
                                      lower,
                                      upper,
                                      pwtype)
  nconditions = 1
  ps_status = ccall((:ps3000SetPulseWidthQualifier, ps3000driver), Int16,
    (Int16, Ref{PWQConditions}, Int16, Int16, UInt32, UInt32, Int16),
    handle, Ref{PWQConditions}(conditions), nconditions,
    direction, lower, upper, pwtype)
  if ps_status == 0
    error("ps3000 Error: one of the parameters is out of range")
  end
  return nothing
end

function ps3000setpulsewidthqualifier(handle :: Int16)
  nconditions = 0
  direction = 0
  lower = 0
  upper = 0
  pwtype = 0
  ps_status = ccall((:ps3000SetPulseWidthQualifier, ps3000driver), Int16,
    (Int16, Ptr{Void}, Int16, Int16, UInt32, UInt32, Int16),
    handle, Ptr{Void}(C_NULL), nconditions,
    direction, lower, upper, pwtype)
  if ps_status == 0
    error("ps3000 Error: one of the parameters is out of range")
  end
  return nothing
end