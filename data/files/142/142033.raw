## Utils

function length_eq(a::AbstractArray, b::AbstractVector)
  length(a) == length(b)
end

function normalise(v::Vector)
  total = sum(v)
  map(x->x/total, v)
end

## ===========
## Printing

function printy(d::Delta)
  println("DeltaValue:", d.value)
end

function printy(d::NoDistribution)
  println("No Distribution")
end

function printy(b::Belief)
  println("weight: ", b.weight)
  println("distribution: ")
  printy(b.distribution)
end

function printy(s::Socket)
  println("basin: ")
  map(printy, s.basin)
  println("distribution: ")
  printy(s.distribution)
  println("")
end

function printy(m::Machine)
  map(printy, m.sockets)
  println("")
  map(printy, m.machines)
end

