# a source is a machine which continually outputs its
# intrinsic value to a single socket
type Source <: Machine
  value::Belief #FIXME, this should be a distribution
  sockets::Vector{Socket}
  machines::Vector{Machine} # FIXME: Remove this waste-o-space
  id::Machine

  # FIXME: Should a source belief,
  # 1. have a constant specified weight at contruction
  # 2. have weight 1.0
  # 4. gave a weight specified in another socket
  # 5. have its weight be unimportant since it will override
  # 6. CURRENTLY doing 1
  function Source(belief::Belief)
    m = new(belief, [Socket(belief)], no_machines())
    m.id = m
  end
end

# Convenience
socket_id(m::Source) = m.sockets[1]

function work!(m::Source)
  concatBasin!(m.sockets[1], m.value)
  map!(work!, m.machines) # Go recursively
  m
end