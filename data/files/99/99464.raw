# Test code to solve simplest possible VRP
# - No time windows
# - Just vehicle capacities

# N1-------N2
# |       / |
# |    /    |
# Depot----N3
# |       /
# N4------


const NODES = 4
                   #D  N1  N2  N3  N4
const NODEDISTS = [0.0 3.0 5.0 4.0 2.0;  # D
                   3.0 0.0 4.0 Inf Inf;  # N1
                   5.0 4.0 0.0 3.0 Inf;  # N2
                   4.0 Inf 3.0 0.0 5.0;  # N3
                   2.0 Inf Inf 5.0 0.0]  # N4
                    #D   N1   N2   N3   N4
const NODEDEMANDS = [0.0 30.0 30.0 30.0 30.0]
const CAPACITY = 80.0
const MAXVEHICLES = 4

using JuMP

# Master problem
function SolveMaster(routes)
  # Solves the master problem
  # Returns the duals
  m = Model(:Min)
  num_routes = length(routes)
  
  @defVar(m, 0 <= x[1:num_routes] <= 1)
  
  # Minimize cost of selected routes
  @setObjective(m, sum{routes[r][NODES+1]*x[r], r=1:num_routes})

  # All locations must be visited at least once
  @defConstrRef node_visits[1:NODES]
  for i = 1:NODES
    node_visits[i] = @addConstraint(m, sum{routes[r][i]*x[r], r=1:num_routes} >= 1)
  end

  # Max vehicles
  max_vehicle = @addConstraint(m, sum{x[r], r=1:num_routes} <= MAXVEHICLES)

  # Solve LP
  status = solve(m)
  if status == :Infeasible
    error("Solve was Infeasible somehow?!")
  end

  # Get duals
  duals = getDual(node_visits)
  println(duals)
  println(getDual(max_vehicle))
end

routes = [(1,0,0,0,6),
          (0,1,0,0,10),
          (0,0,1,0,8),
          (0,0,0,1,4)]
println(routes)
SolveMaster(routes)
