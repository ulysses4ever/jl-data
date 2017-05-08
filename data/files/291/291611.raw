# Sugarscape
# Chapter II
module ChapterII

using StatsBase: sample
import PyPlot
import Color


## Types ##

# We define an abstract type AgentInfo with two subtypes: NoAgent and Agent.
# This allows for removing an agent from the board while keeping his entry in 
# the agent list. Also it allows for recursive type definition, an old 
# unresolved Julia issue #269.

abstract AgentInfo
type NoAgent <: AgentInfo
end

type Place
    x::Int
    y::Int
    agent::AgentInfo
    sugar::Int
    capacity::Int
end

type Agent <: AgentInfo
    place::Place
    vision::Int
    metabolism::Int
    stash::Int
end


# We only keep in this version the current lattice and agents in memory, not the
# history.
type Scape
    lattice::Array{Place}
    agents::Vector{AgentInfo}    
end

# convenience functions
Base.show(io::IO, scape::Scape) = println(io, "Sugarscape with $(length(agents(scape))) agents")
agents(scape::Scape) = scape.agents
Base.isempty(place::Place) = isa(place.agent, NoAgent)
alive(agent::AgentInfo) = isa(agent, Agent)
living(scape) = scape.agents[map(alive, scape.agents)]


## Initialization ##

# We define a sugarscape capacity similar to graphs in the book.
function init_capacity()
    grid = 50
    hump1 = [15, 15]
    hump2 = [40, 40]
    dist(xy, hump) = hypot(xy[1]-hump[1], xy[2]-hump[2])
    capacity = Int[max(0, 4 - ifloor(min(dist([i,j], hump1), dist([i,j], hump2))/5)) for i=1:grid,j=1:grid]
end

# Keyword arguments still have a performance penalty if not type defined.
function init_scape(capacity; N_agents::Int=400, init_stash=10)
    gridx, gridy = size(capacity)
    # create empty lattice with sugar levels at full capacity
    lattice = [Place(i,j, NoAgent(), capacity[i,j], capacity[i,j]) for i=1:gridx, j=1:gridy]

    #populate with agents
    agents = AgentInfo[]
    for place in sample(lattice, N_agents, replace=false)
        vision = rand(1:6)
        metabolism = rand(1:4)
        stash = init_stash
        agent = Agent(place, vision, metabolism, stash)
        push!(agents, agent)

        place.agent = agent
    end
    
    Scape(lattice, agents)
end


## Movement ##

# (function input annotations are not necessary (not even for speed), just for type checks)

#step functions to select neighbouring place with circular boundaries
 left(p::Place, lat::Array{Place}) = lat[p.x==1 ? end : p.x-1, p.y]
right(p::Place, lat::Array{Place}) = lat[p.x==end ? 1 : p.x+1, p.y]
   up(p::Place, lat::Array{Place}) = lat[p.x, p.y==1 ? end : p.y-1]
 down(p::Place, lat::Array{Place}) = lat[p.x, p.y==end ? 1 : p.y+1]

# function to move an agent to a destination place
function move(agent::Agent, dest_place::Place)
    agent.place === dest_place && return
    isempty(dest_place) || error("destination place occupied")

    agent.place.agent = NoAgent()
    dest_place.agent = agent
    agent.place = dest_place
    return nothing
end

# function to select best next step in view of agent.
function view_place(agent::Agent, step_function::Function, lattice::Array{Place})
    p = agent.place

    p_out = pstep = p #if no unoccupied place in sight, stay put
    sugar = -1 #Agent will move to empty place rather than stay put
    for _ in 1:agent.vision
        pstep = step_function(pstep, lattice)
        # Only move further if more sugar, not on equal sugar level.
        # As in book, agents will take steps of size=1 when far from sugar 
        # mountains, but this could be improved to larger steps.
        # It seems from Animation II-1 that agents do not jump over other agents
        # (as a horse), but only slide like a rook.

        if isempty(pstep) 
            if pstep.sugar > sugar
                sugar = pstep.sugar
                p_out = pstep
            end
        else #disallow jumps
            break
        end
    end
    p_out
end

# to sort array of places by sugar, define `isless`
Base.isless(p1::Place, p2::Place) = p1.sugar < p2.sugar

function harvest(agent)
    agent.place.sugar == 0 && return(nothing)
    agent.stash += agent.place.sugar
    agent.place.sugar = 0
    nothing
end

# move all agents and harvest
function move(scape::Scape)
    lat = scape.lattice
    direction = [left, right, up, down]

    @inbounds for agent in shuffle(living(scape))
        view_places = Array(Place, 4)
        # Randomize search directions in case of equal sugar place, as in book.
        shuffle(direction)
        for i = 1:4
            view_places[i] = view_place(agent, direction[i], lat)
        end
        select_place = last(sort!(view_places))
        move(agent, select_place)
        harvest(agent)
    end
end


## Evolve ##

function grow(scape::Scape; α::Int=1)    
    @inbounds for place in scape.lattice
        place.sugar = min(place.capacity, place.sugar + α)
    end
end

function consume(scape::Scape)
    @inbounds for agent in living(scape)
        agent.stash -= agent.metabolism
    end
end

function Base.kill(scape::Scape)
    ag = scape.agents #living(scape) will make copy
    
    @inbounds for i = 1:length(ag)
        if alive(ag[i]) && (ag[i].stash < 0)
            ag[i].place.agent = NoAgent()            
            ag[i] = NoAgent()
        end
    end    
end

function timestep(scape::Scape; α::Int=1)
    grow(scape, α=α)
    move(scape) #includes harvestig
    consume(scape)
    kill(scape)
    nothing
end

function run(N; kwargs...)
    scape = init_scape(init_capacity(); kwargs...)
    for cnt = 1:N
        timestep(scape; kwargs...)
    end
    scape
end


## Plotting ##

plot(scape::Scape) = plot(scape, length(scape.steps))

function plot(scape::Scape)
    lattice = scape.lattice
    gridx, gridy = size(lattice)
    sugar = reshape([p.sugar for p in lattice], gridx, gridy)
    s_i, s_j = collect(ind2sub(size(lattice), 1:length(lattice)))
    colmap = PyPlot.ColorMap([Color.RGB(1,1,1), Color.RGB(1,1,0)],5,1.5)
    PyPlot.scatter(s_i, s_j, s=20*sugar, c=sugar, cmap=colmap, marker="o", lw=0)

    step_agents = living(scape)
    a_i = [a.place.x for a in step_agents]
    a_j = [a.place.y for a in step_agents]
    PyPlot.scatter(a_i, a_j, c="red", lw=0)
    
    PyPlot.xlim(0, gridx+1); PyPlot.ylim(0, gridy+1)
    PyPlot.title("Sugarscape step")
end



end #module