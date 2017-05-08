# A worker machine has a single socket with tuple input
type Worker <: Machine
  fun::Function
  sockets::Vector{Socket}
  machines::Vector{Machine}
  exposed::AbstractVector{Bool}
  id::Machine

  function Worker(fun, sockets, machines)
    m = new(fun, sockets, machines)
    m.id = m
  end
end

function work!(m::Worker)
  params = rand(m.machines[1].sockets[1].distribution)
  arg_sockets = params[1:end-1]
  args = map(rand, arg_sockets)
  dest::Socket = last(params)
  value = Delta(apply(m.fun, args)) # FIXME: arbitrary weight choice
  concatBasin!(dest, hard(value))
  map!(work!, m.machines)
  m
end