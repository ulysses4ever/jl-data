using Distributions

"""
Top-level Agent class.
"""
abstract Agent

"""
How I think agents should look
"""
type BasicAgent <: Agent
    observables::Dict{UTF8String, UTF8String} # feature: tag
    capabilities::Dict{UTF8String, Float64} # capacity: strength
    relations::Dict{Agent, Int} # acquaitance: last-time
end

"""
The world in which agents interact.
"""
abstract World

function addagent(world::World, agent::Agent)
    world.agents = [world.agents; agent]
end

function timestep(world::World, tt::Int)
    for agent in world.agents
        timestep(agent, world, tt)
    end
end

"""
Spatial agents have a location and interact with others spatially.
"""
abstract SpatialAgent <: Agent

"""
A world with a certain amount of space and rolling edges.
"""
type DonutWorld <: World
    agents::Vector{Agent}
    nrows::Int
    ncols::Int

    DonutWorld(nrows::Int, ncols::Int) = new(Agent[], nrows, ncols)
end

function getagents(world::DonutWorld, row::Int, col::Int)
    filter(agent -> agent.row % world.nrows == row % world.nrows && agent.col % world.ncols == col % world.ncols, world.agents)
end

"""
PrisonerGameAgents play the Prisoners' dilemma with other PGAs.
"""
type PrisonersGameAgent <: SpatialAgent
    row::Int
    col::Int

    tag::UTF8String
    wealth::Float64

    totalgames::Int
    coopbias::Float64 # utility from playing coop
    history::Dict{UTF8String, Tuple{Int, Int}} # tag: (#coop, #defe)

    PrisonersGameAgent(tag::UTF8String, coopbias::Float64) = new(0, 0, tag, 0., 0, coopbias, Dict{UTF8String, Tuple{Int, Int}}())
end

# The actions and outcomes
@enum PrisonerActions COOPERATE DEFECT

coop2coop = 2.;
coop2defe = 0.;
defe2coop = 3.;
defe2defe = 1.;

# Decide on the optimal action
function prisoneraction(self::PrisonersGameAgent, tag)
    coopdefes = get(self.history, tag, (0, 0))

    coopscore = (coop2coop * coopdefes[1] + coop2defe * coopdefes[2]) / (coopdefes[1] + coopdefes[2]) + self.coopbias
    defescore = (defe2coop * coopdefes[1] + defe2defe * coopdefes[2]) / (coopdefes[1] + coopdefes[2])

    if coopscore >= defescore
        return COOPERATE
    else
        return DEFECT
    end
end

# Resolve the game with scores
function prisonerscore(selfact::PrisonerActions, otheract::PrisonerActions)
    if selfact == COOPERATE && otheract == COOPERATE
        return coop2coop
    elseif selfact == COOPERATE && otheract == DEFECT
        return coop2defe
    elseif selfact == DEFECT && otheract == COOPERATE
        return defe2coop
    else
        return defe2defe
    end
end

function updateprisoner(self::PrisonersGameAgent, other::PrisonersGameAgent, selfact::PrisonerActions, otheract::PrisonerActions, tt::Int)
    # Update history
    coopdefes = get(self.history, other.tag, (0, 0))

    if otheract == COOPERATE
        newcoopdefes = (coopdefes[1] + 1, coopdefes[2])
    else
        newcoopdefes = (coopdefes[1], coopdefes[2] + 1)
    end

    self.history[other.tag] = newcoopdefes

    # Update wealth
    self.wealth = self.wealth + prisonerscore(selfact, otheract)
    self.totalgames += 1
end

function timestep(self::PrisonersGameAgent, world::World, tt::Int)
    # Move in a random direction
    # only move forward because -X % ... < 0!
    self.row += rand(DiscreteUniform(0, 1))
    self.col += rand(DiscreteUniform(0, 1))

    others = filter(agent -> agent != self, getagents(world, self.row, self.col))
    if length(others) > 0
        other = others[rand(1:end)]

        selfact = prisoneraction(self, other.tag)
        otheract = prisoneraction(other, self.tag)

        updateprisoner(self, other, selfact, otheract, tt)
        updateprisoner(other, self, otheract, selfact, tt)
    end
end

# Create a world with some agents

world = DonutWorld(2, 10)

for ii in 1:10
    agent = PrisonersGameAgent(utf8(ii <= 5 ? "lower" : "upper"), rand(Normal(0, 1)))
    addagent(world, agent)
end

for tt in 1:100
    for tt2 in 1:10000
        timestep(world, tt)
    end
    # Calculate average wealth and expectations
    counts = Dict{UTF8String, Int}("lower"=>0, "upper"=>0);
    wealths = Dict{UTF8String, Float64}("lower"=>0., "upper"=>0.);
    biases = Dict{UTF8String, Float64}("lower"=>0., "upper"=>0.);
    expects_lower = Dict{UTF8String, Float64}("lower"=>(0.), "upper"=>(0.));
    expects_upper = Dict{UTF8String, Float64}("lower"=>(0.), "upper"=>(0.));
    for agent in world.agents
        tag = agent.tag
        counts[tag] += 1
        wealths[tag] += agent.wealth
        biases[tag] += agent.coopbias
        expectsbefore_lower = expects_lower[tag]
        expectsbefore_upper = expects_upper[tag]
        lowercoopdefes = get(agent.history, "lower", (0, 0))
        uppercoopdefes = get(agent.history, "upper", (0, 0))
        expectsafter_lower = expectsbefore_lower + convert(Float64, lowercoopdefes[1]) / (lowercoopdefes[1] + lowercoopdefes[2])
        expectsafter_upper = expectsbefore_upper + convert(Float64, uppercoopdefes[1]) / (uppercoopdefes[1] + uppercoopdefes[2])
        expects_lower[tag] = expectsafter_lower
        expects_upper[tag] = expectsafter_upper
    end

    @printf "Avg. Wealth: %f | %f\n" (wealths["lower"] / counts["lower"]) (wealths["upper"] / counts["upper"])
    @printf "Avg. Coop. Bias: %f | %f\n" (biases["lower"] / counts["lower"]) (biases["upper"] / counts["upper"])
    @printf "Chance Coop. vs. Lower: %f | %f\n" (expects_lower["lower"] / counts["lower"]) (expects_lower["upper"] / counts["upper"])
    @printf "Chance Coop. vs. Upper: %f| %f\n" (expects_upper["lower"] / counts["lower"]) (expects_upper["upper"] / counts["upper"])
end
