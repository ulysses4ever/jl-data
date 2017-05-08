import Distributions.pnormalize!

# Sockets contan beliefs, transiently
type Socket{B <: Belief}
  basin::Vector{B}
  belief::Belief
  id::Socket

  function Socket(basin::Vector{B}, belief::Belief)
    x = new(basin, belief)
    x.id = x
  end
end

function Socket{B <: Belief}(basin::Vector{B}, belief::Belief)
  t = eltype(basin)
  Socket{t}(basin,belief)
end

# rand(s::Socket) = rand(s.distribution)
function push_basin!(s::Socket, b::Belief)
  push!(s.basin,b)
  s
end

function clear_basin!(s::Socket)
  s.basin = []
  s
end

function clear_belief!(s::Socket)
  s.belief = NO_BELIEF
  s
end

function mix!(s::Socket)
  if isempty(s.basin)
    s.belief = NO_BELIEF
  else
    s.belief = mix(s.basin)
  end
  s
end
