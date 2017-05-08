# ps3000setadvtriggerchannelconditions

export ps3000setadvtriggerchannelconditions, PS3000TriggerState, TriggerConditions

baremodule PS3000TriggerState
  const CONDITION_DONT_CARE = 0x0000
  const CONDITION_TRUE = 0x0001
  const CONDITION_FALSE = 0x0002
end

immutable TriggerConditions
    a :: Int16
    b :: Int16
    c :: Int16 
    d :: Int16 
    pulsewidthqualifier :: Int16
end

function ps3000setadvtriggerchannelconditions(handle     :: Int16,
                                              conditions :: TriggerConditions)
  nconditions = 1
  ps_status = ccall((:ps3000SetAdvTriggerChannelConditions, ps3000driver), Int16,
    (Int16, Ref{TriggerConditions}, Int16),
    handle, Ref{TriggerConditions}(conditions), nconditions)
  if ps_status == 0
    error("ps3000 Error: one of the parameters is out of range")
  end
  return nothing
end

function ps3000setadvtriggerchannelconditions(handle     :: Int16)
  # call with no conditions to turn trigger off
  nconditions = 0
  ps_status = ccall((:ps3000SetAdvTriggerChannelConditions, ps3000driver), Int16,
    (Int16, Ptr{Void}, Int16),
    handle, Ptr{Void}(C_NULL), nconditions)
  if ps_status == 0
    error("ps3000 Error: one of the parameters is out of range")
  end
  return nothing
end