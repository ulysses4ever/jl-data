# A Mover just shuffles beliefs around between sockets
# It has a collection of machines. M1, M2, M3,...
# Each machine must expose a pair of sockets

type Mover <: Machine
  sockets::Vector{Socket}
  machines::Vector{Machine}
  id::Machine

  function Mover(sockets, machines)
    m = new(sockets, machines)
    m.id = m
  end
end

function work!(m::Mover)
  dir::Vector{(Socket,Socket,Weight)} = m.machines[1].sockets[1] #TOOD:Type sys
  belief = Belief(dir[2].distribution, dir[3])
  dir[1].socket.concatBasin!(belief)
end
