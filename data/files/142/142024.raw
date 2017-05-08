# A Composite machine is the union of a Collection and a Worker
# With the addition that it has a special socket
# which maps internal sockets, to external sockets
type Composite <: Machine
  sockets::Vector{Socket}
  machines::Vector{Machine}
  id::Machine

  function Composite(sockets, machines)
    m = new(sockets, machines)
    m.id = m
  end
end