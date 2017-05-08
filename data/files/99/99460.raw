# Test code to solve simplest possible VRP
# - No time windows
# - Just vehicle capacities

# N1-------N2
# |  \    / |
# |    --   |
# |   /  \  |
# Depot----N3
# |       /
# N4------


const NODES = 4
                   #D  N1  N2  N3  N4
const NODEDISTS = [0.0 3.0 5.0 4.0 2.0;  # D
                   3.0 0.0 4.0 5.0 5.0;  # N1
                   5.0 4.0 0.0 3.0 7.0;  # N2
                   4.0 5.0 3.0 0.0 5.0;  # N3
                   2.0 5.0 8.0 5.0 0.0]  # N4
                    #D   N1   N2   N3   N4
const NODEDEMANDS = [0.0 30.0 30.0 30.0 30.0]
const TIMEWINDOWS = [(0.0, 20.0), # D
                     (0.0, 20.0), # N1
                     (0.0, 20.0), # N2
                     (0.0, 20.0), # N3
                     (0.0, 20.0)] # N4
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
  @setObjective(m, sum{routes[r][2]*x[r], r=1:num_routes})

  # All locations must be visited at least once
  @defConstrRef node_visits[1:NODES]
  for i = 1:NODES
    node_visits[i] = @addConstraint(m, sum{routes[r][1][i]*x[r], r=1:num_routes} >= 1)
  end

  # Max vehicles
  max_vehicle = @addConstraint(m, sum{x[r], r=1:num_routes} <= MAXVEHICLES)

  # Solve   LP
  println("  MASTER: Solving...")
  status = solve(m)
  if status == :Infeasible
    error("  MASTER: Solve was Infeasible somehow?!")
  end

  # Get duals
  node_visits_dual = getDual(node_visits)
  max_vehicle_dual = getDual(max_vehicle)
  dual = zeros(NODES+1)
  dual[1] = max_vehicle_dual
  for j = 1:NODES
    dual[j+1] = node_visits_dual[j]
  end
  println("  MASTER: Solved, returning dual")
  return dual
end

# Subproblem
function SolveSubproblem(dual)
  # Solves the subproblem
  # Returns a new route or nothing
  m = Model(:Min)

  # Calculate adjusted costs
  cbar = zeros(NODES+1,NODES+1)
  for i = 0:NODES
    for j = 0:NODES
      cbar[i+1,j+1] = NODEDISTS[i+1,j+1] - dual[j+1]
    end
  end

  # x[i,j] == 1 means we travel between i and j
  @defVar(m, 0 <= x[0:NODES,0:NODES] <= 1, Int)

  # A[i] is the arrival time at i
  @defVar(m, TIMEWINDOWS[i+1][1] <= A[i=0:NODES] <= TIMEWINDOWS[i+1][2])

  # Minimize cost of route (ideally will be negative)
  @setObjective(m, sum{cbar[i+1,j+1]*x[i,j], i=0:NODES, j=0:NODES})

  # Must leave from depot
  @addConstraint(m, sum{x[0,j], j=1:NODES} == 1)
  # Must return to depot
  @addConstraint(m, sum{x[i,0], i=1:NODES} == 1)
  # Must enter and leave nodes same number of times
  # No diagnoals
  for k = 1:NODES
    @addConstraint(m, sum{x[i,k], i=0:NODES} == sum{x[k,j], j=0:NODES})
    @addConstraint(m, x[k,k] == 0)
  end
  # Must respect capacity limits
  @addConstraint(m, sum{NODEDEMANDS[j+1]*x[i,j], i=0:NODES, j=0:NODES} <= CAPACITY)
  # Must respect time windows
  const BIGM = 1000.0
  for i = 0:NODES
    for j = 1:NODES # Don't worry about arcs into depot just yet
      @addConstraint(m, A[i] + NODEDISTS[i+1,j+1] <= A[j] + M*(1.0 - x[i,j]))
    end
  end


  println("  SUB: Finding route")
  solve(m)
  println("  SUB: Solved")
  println("    TODO: Subtour elimination..."

  if getObjectiveValue(m) < -1e-6
    # New route
    #println(getValue(x))
    # Extract column
    r = zeros(Int, NODES)
    c = 0
    for i = 0:NODES
      for j = 0:NODES
        if getValue(x[i,j]) > 1-1e-6
          c += NODEDISTS[i+1,j+1]
          if j > 0
            r[j] = 1
          end
        end
      end
    end
    print("  SUB: Found new route ")
    println(sub)
    return (r,c)
  else
    # No new route
    println("  SUB: No new route (obj = $(getObjectiveValue(m))")
    return nothing
  end
end

routes = [([1,0,0,0],6),
          ([0,1,0,0],10),
          ([0,0,1,0],8),
          ([0,0,0,1],4)]
for iter = 1:10
  println("ITER $iter")
  dual = SolveMaster(routes)
  sub = SolveSubproblem(dual)
  if sub == nothing
    # Done
    println("DONE")
    break
  else
    # Add route
    push!(routes, sub)
  end
end
