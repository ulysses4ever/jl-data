# ps3000setadvtriggerchannelproperties.jl

export ps3000setadvtriggerchannelproperties, TriggerChannelProperties, PS3000ThresholdMode

immutable TriggerChannelProperties
  thresholdmajor  :: Int16  # scaled in 16-bit ADC counts
  thresholdminor  :: Int16  # scaled in 16-bit ADC
  hysteresis      :: UInt16 # scaled in 16-bit ADC
  channel         :: Int16 # A = 0, B = 1, C = 2, D = 3 I assume.
  thresholdmode   :: Int16
end

baremodule PS3000ThresholdMode
  const level = 0x0000
  const window = 0x0001
end

function ps3000setadvtriggerchannelproperties(handle :: Int16,
                                              channelproperties :: TriggerChannelProperties,
                                              autotriggermilliseconds :: Int32)
  nchannelproperties = 1
  ps_status = ccall((:ps3000setadvtriggerchannelproperties, ps3000driver), Int16,
    (Int16, Ref{TriggerChannelProperties}, Int16, Int32),
    handle, Ref{TriggerChannelProperties}(channelproperties),
     nchannelproperties, autotriggermilliseconds)
  if ps_status == 0
    error("ps3000 Error: one of the parameters is out of range")
  end
  return nothing
end

function ps3000setadvtriggerchannelproperties(handle :: Int16)
  # call with no conditions to turn trigger off
  nchannelproperties = 0
  autotriggermilliseconds = 0
  ps_status = ccall((:ps3000setadvtriggerchannelproperties, ps3000driver), Int16,
    (Int16, Ref{Void}, Int16, Int32),
    handle, Ref{Void}(C_NULL),
     nchannelproperties, autotriggermilliseconds)
  if ps_status == 0
    error("ps3000 Error: one of the parameters is out of range")
  end
  return nothing
end