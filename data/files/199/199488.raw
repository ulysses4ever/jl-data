# ps3000setadvtriggerchanneldirections.jl

export ps3000setadvtriggerchanneldirections, PS3000ThresholdDirection

function ps3000setadvtriggerchanneldirections(handle:: Int16, dira, dirb,
                                              dirc, dird, dirext)
  ps_status = ccall((:ps3000SetAdvTriggerChannelDirections, ps3000driver), Int16,
    (Int16, Int16, Int16, Int16, Int16, Int16),
    handle, dira, dirb, dirc, dird, dirext)
  if ps_status == 0
    error("ps3000 Error: one of the parameters is out of range")
  end
  return nothing
end

baremodule PS3000ThresholdDirection
  # for gated triggers
  const ABOVE   = 0x0000 # above a threshold
  const BELOW   = 0x0001 # below a threshold

  # for threshold triggers
  const RISING  = 0x0002 # rising edge
  const FALLING = 0x0003 # falling edge
  const RISING_OR_FALLING = 0x0004 # either edge

  # for window qualified triggers
  const INSIDE  = ABOVE # inside window
  const OUTSIDE = BELOW # outside window

  # For window triggers
  const ENTER   = RISING  # entering the window
  const EXIT    = FALLING # leaving the window
  const ENTER_OR_EXIT = RISING_OR_FALLING # either entering or leaving the window
  const NONE    = RISING # no trigger
end
