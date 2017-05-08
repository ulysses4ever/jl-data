# Sugarscape
# Chapter II
module ChapterII

using StatsBase: sample
import PyPlot
import Colors


## Types ##
type Place{T}
    x :: Int
    y :: Int
    agent :: Nullable{T}
    sugar :: Int      
    capacity :: Int
end

type Agent
    id :: Int
    place :: Place{Agent}
    vision :: Int
    metabolism :: Int
    stash :: Int
end
# We only keep in this version the current lattice and agents in memory, not the
# history.
type Scape
    lattice :: Matrix{Place{Agent}}
    agents :: Vector{Agent}
    steps :: Int
end

# convenience functions
Base.show(io::IO, scape::Scape) = println(io, "Sugarscape with $(length(scape.agents)) agents over $(scape.steps) steps.")
Base.isempty(place::Place) = isnull(place.agent)


## Initialization ##

# We define a sugarscape capacity similar to graphs in the book.
function init_capacity()
    grid = 50
    hump1 = [15, 15]
    hump2 = [40, 40]
    dist(xy, hump) = hypot(xy[1]-hump[1], xy[2]-hump[2])
    capacity = Int[max(0, 4 - floor(min(dist([i,j], hump1), dist([i,j], hump2))/5)) for i=1:grid,j=1:grid]
end

# Keyword arguments still have a performance penalty if not type defined.
function init_scape(capacity; N_agents::Int=400, init_stash=10, 
                    init_vision=()->rand(1:6), init_metabolism=()->rand(1:4))
    gridx, gridy = size(capacity)
    # create empty lattice with sugar levels at full capacity
    lattice = [Place(i, j, Nullable{Agent}(), capacity[i,j], capacity[i,j]) for i=1:gridx, j=1:gridy]

    #populate with agents
    agents = Agent[]
    for (id, place) in enumerate(sample(lattice, N_agents, replace=false))
        vision = init_vision()
        metabolism = init_metabolism()
        stash = init_stash
        agent = Agent(id, place, vision, metabolism, stash)
        push!(agents, agent)

        place.agent = agent
    end
    Scape(lattice, agents, 0)
end


## Movement ##

# (function input annotations are not necessary (not even for speed), just for type checks)

#step functions to select neighbouring place with circular boundaries
left( p::Place, lat::Matrix) = lat[p.x==1 ? end : p.x-1, p.y]
right(p::Place, lat::Matrix) = lat[p.x==end ? 1 : p.x+1, p.y]
up(   p::Place, lat::Matrix) = lat[p.x, p.y==1 ? end : p.y-1]
down( p::Place, lat::Matrix) = lat[p.x, p.y==end ? 1 : p.y+1]

# function to move an agent to a destination place
function move(agent::Agent, dest_place::Place)
    agent.place === dest_place && return
    isempty(dest_place) || error("destination place occupied")

    agent.place.agent = Nullable{Agent}()
    dest_place.agent = agent
    agent.place = dest_place
    return nothing
end

# function to select best next step in view of agent.
function view_place(agent::Agent, step_function::Function, lattice::Matrix{Place{Agent}})
    p = agent.place

    p_out = pstep = p #if no unoccupied place in sight, stay put
    best_sugar = -1 #Agent will move to empty place rather than stay put
    for _ in 1:agent.vision
        pstep = step_function(pstep, lattice)
        # Only move further if more sugar, not on equal sugar level.
        # As in book, agents will take steps of size=1 when far from sugar 
        # mountains, but this could be improved to larger steps.
        # It seems from Animation II-1 that agents do not jump over other agents
        # (as a horse), but only slide like a rook.

        if isempty(pstep) 
            if pstep.sugar > best_sugar
                best_sugar = pstep.sugar
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
    #agent.place.sugar == 0 && return(nothing)
    agent.stash += agent.place.sugar
    agent.place.sugar = 0
    nothing
end

# move all agents and harvest
function move_harvest(scape::Scape)
    lat = scape.lattice
    direction = [left, right, up, down]
    view_places = Array(Place, 4)

    @inbounds for agent in shuffle(scape.agents)
        # Randomize search directions in case of equal sugar place, as in book.
        shuffle!(direction)
        for i = 1:4
            view_places[i] = view_place(agent, direction[i], lat)
        end
        move(agent, maximum(view_places))
        harvest(agent)
    end
end


## Evolve ##

function grow(scape::Scape; α::Int=1)    
    for place in scape.lattice
        place.sugar = min(place.capacity, place.sugar + α)
    end
end

function eat(scape::Scape)
    for agent in scape.agents
        agent.stash -= agent.metabolism
    end
end

function die(scape::Scape)
    agents = scape.agents
    zombies = Int[]
    for (i, agent) in enumerate(agents)
        if agent.stash < 0
            agent.place.agent = Nullable{Agent}()
            push!(zombies, i)
        end
    end
    #need to delete all at once to keep index consistency
    deleteat!(agents, zombies)
    nothing
end

function timestep(scape::Scape; α::Int=1, args...)
    grow(scape, α=α)
    move_harvest(scape) #includes harvestig
    eat(scape)
    die(scape)
    scape.steps += 1
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

function plot(scape::Scape)
    lattice = scape.lattice
    gridx, gridy = size(lattice)
    sugar = reshape([p.sugar for p in lattice], gridx, gridy)
    s_i, s_j = collect(ind2sub(size(lattice), 1:length(lattice)))
    colmap = PyPlot.ColorMap([Colors.RGB(1,1,1), Colors.RGB(1,1,0)],5,1.5)
    PyPlot.scatter(s_i, s_j, s=20*sugar, c=sugar, cmap=colmap, marker="o", lw=0)

    agents = scape.agents
    a_i = [a.place.x for a in agents]
    a_j = [a.place.y for a in agents]
    PyPlot.scatter(a_i, a_j, c="red", lw=0)
    
    PyPlot.xlim(0, gridx+1); PyPlot.ylim(0, gridy+1)
    PyPlot.title("Sugarscape step $(scape.steps)")
end


end #module