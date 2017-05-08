
# Definition of "agent" (network's node)

type Node
	id::Int64   # Index inside the network
	l::Int64    # Hierarchy Level
	c::Float64  # Probability of "soborno" acceptance
	th::Float64  # Threshold as a funciton of hierarchy level
end

# Methods for Node type

# Determines node level based on its id and 
# the network's branching factor
function set_level(id::Int64, branching::Int64)
    l = int(floor(log(id*(branching -1) +1) / log(branching)))
    # println(typeof(l))
    return l
end

#Assigns node's threshold based on its hierarchy level
#th_max is the max threshold of the system
function threshold(l::Int64,th_max::Float64,height::Int64)
    # global height    
    th = -l * ( 2 * th_max - 1 ) / float(height) + th_max
    return th
end

const branching = 3
const height    = 3
const th_max    = 0.9
const N         = 3


R = Array(Node, N)

for i = 1:N
	l    = set_level(i,branching)
	th   = threshold(l,th_max,height)
	R[i] = Node(i,l,rand(),th)
end

println(R)