module Shelling
export Agent, simulate, simulate_random

using Distances
using Gadfly
using StatsBase

immutable Agent
  kind::Integer
  position::Vector{Real}
end

"""
Given a kind, constructs a random agent
"""
random_agent(kind::Integer; k::Integer = 2) = Agent(kind, rand(k))

"""
Given an agent, returns a predicate that compares whether an agent is similar
to the given agent
"""
similarto(agent::Agent) = other -> agent.kind == other.kind

"""
Given an agent and a vector of potential neighbors, returns a vector of the
k-closest neighbors
"""
function closest_neighbors(agent::Agent, agents::Vector{Agent}; neighborhood_size::Integer = 10)
  n = length(agents)
  indices_by_distance = [(Distances.euclidean(agent.position, agents[i].position), i) for i in 1:n]
  sorted_indices_by_distance = sort(indices_by_distance)
  return [agents[index_by_distance[2]] for index_by_distance in sorted_indices_by_distance[1:neighborhood_size]]
end

"""
Given an agent and a vector of potential neighbors, returns true if the given
agent is within the vicinity of ten other similar agents
"""
function ishappy(person::Agent, people::Vector{Agent}; neighborhood_size::Integer = 10, similarity_threshold::Real = 0.6)
  return sum(similarto(person), closest_neighbors(person, people; neighborhood_size = neighborhood_size)) >= similarity_threshold * neighborhood_size
end

"""
Given an agent and a vector of other agents, returns a new agent with the
position changed such that the new agent is either happy with the new position
or a maximum number of moves have been reached
"""
function attempt_move(agent::Agent, agents::Vector{Agent}; max_moves::Integer = 100, neighborhood_size::Integer = 10, similarity_threshold::Real = 0.6)
  num_moves = 0
  # Attempt assigning this agent to another location until they are happy
  kind = agent.kind
  position = agent.position
  while !ishappy(Agent(agent.kind, position), agents; neighborhood_size = neighborhood_size, similarity_threshold = similarity_threshold) && num_moves < max_moves
    position = rand(length(agent.position))
    num_moves += 1
  end
  return Agent(kind, position)
end

"""
Simulate the segregation of agents
"""
function simulate(
    agents::Vector{Agent},
    neighborhood_size::Integer,
    similarity_threshold::Real;
    max_iterations::Integer = 100,
    max_moves::Integer = 100)
  @assert 0 < similarity_threshold < 1
  info("Starting simulation")
  n = length(agents)
  num_iterations = 0
  unhappy_agents = Int64[]
  num_unhappy_agents = n

  old_agents = Vector{Agent}(n)
  while num_unhappy_agents > 0 && num_iterations < max_iterations
    num_unhappy_agents = 0

    old_agents, agents = agents, old_agents
    for i in 1:n
      if !ishappy(old_agents[i], old_agents; neighborhood_size = neighborhood_size, similarity_threshold = similarity_threshold)
        num_unhappy_agents += 1
        agents[i] = attempt_move(old_agents[i], old_agents; max_moves = max_moves, neighborhood_size = neighborhood_size, similarity_threshold = similarity_threshold)
      else
        agents[i] = old_agents[i]
      end
    end
    push!(unhappy_agents, num_unhappy_agents)
    num_iterations += 1
    info("Iteration $num_iterations: $num_unhappy_agents unhappy agents")
  end
  info("Converged at $num_iterations iterations")

  # Print summary statistics
  info("Unhappy agents:")
  StatsBase.describe(unhappy_agents)
end

"""
Plot agents by projecting their positions to 2D using the first two components
of their position vectors
"""
function plot(agents::Vector{Agent})
  xs = [agent.position[1] for agent in agents]
  ys = [agent.position[2] for agent in agents]
  kinds = [agent.kind for agent in agents]
  Gadfly.plot(x = xs, y = ys, color = kinds)
end

"""
Given the number of agents per kind, a neighborhood size, and a happiness
threshold, constructs and executes a random simulation of segregation
"""
function simulate_random{T <: Integer}(
    num_per_kind::Vector{T},
    neighborhood_size::Integer = 10, 
    similarity_threshold::Real = 0.6;
    max_iterations::Integer = 100, 
    max_moves::Integer = 100)
  agents = Agent[]
  for (kind, num_kind) in enumerate(num_per_kind)
    append!(agents, [random_agent(kind) for i in 1:num_kind])
  end
  info("Simulating Shelling's segregation model")
  for (kind, num_kind) in enumerate(num_per_kind)
    info("\t$num_kind agents of kind $kind")
  end
  info("\t$neighborhood_size neighborhood size")
  info("\t$similarity_threshold similarity threshold")
  simulate(agents, neighborhood_size, similarity_threshold; max_iterations = max_iterations, max_moves = max_moves)
  plot(agents)
end

end
