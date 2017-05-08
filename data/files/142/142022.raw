abstract Machine
no_machines() = Machine[]

typealias Weight Float64

# By default a machine does nothing, except map recursively
function work!(m::Machine)
  map!(work!, m.machines)
  m
end

function accumulate!(machine::Machine)
  map!(accumulate!, machine.sockets)
  map!(accumulate!, machine.machines)
  machine
end

## ===============
## Creating worlds
function push!(machine::Machine, socket::Socket)
  push!(machine.sockets, socket)
end

function push!(a::Machine, b::Machine)
  push!(a.machines, b)
end

## ===========
## Simulation
function run!(machine::Machine, steps)
  for i = 1:steps
    println("STEP")
    printy(machine)
    accumulate!(machine)
    work!(machine)
  end
end

# Run fo-eva
run!(m::Machine) = run!(m. Inf)

# Primitive Machines
for finame in ["worker.jl",
               "collection.jl",
               "mover.jl"]
    include(joinpath("machines", finame))
end
