using JuMP

type Node
  name
  lat
  lon
  demand
end

type Route
  cost
  visits
  x
end

#####################################################################
# LoadData
# Loads the demand and location data from a .csv file
function LoadData(filepath)
  # Build up list of nodes
  nodes = Node[]
  # Open file
  fp = open(filepath, "r")
  # Skip first line (header)
  readline(fp)
  # While there are lines left to read
  while !eof(fp)
    # Read in the line
    line = readline(fp)
    # Split it on the commas
    spl = split(line,",")
    # Extract useful features
    new_node = Node(spl[1],          # Name
                    float(spl[2]),   # Lat
                    float(spl[3]),   # Lon
                    int(spl[4:27]))  # Demand (hourly)
    # Add it to the list
    push!(nodes, new_node)
  end
  return nodes
end

#####################################################################
# CalculatePairwise
# Given the node list, calculates the pairwise distance matrix
# between them all. Returns a NxN symmetrical matrix
function CalculatePairwise(nodes)
  N = length(nodes)
  dists = zeros(N,N)
  for i = 1:N
    for j = (i+1):N
      dists[i,j] = sqrt((nodes[i].lat - nodes[j].lat)^2 
                      + (nodes[i].lon - nodes[j].lon)^2)
      dists[j,i] = dists[i,j]
    end
  end
  return dists
end


#####################################################################
# SolveMaster
# Given a set of routes, select a subset that takes all demand 
# for minimum cost.
function SolveMaster(routes, nodes)
  # Solve the master problem, returns the duals
  num_routes = length(routes)
  num_nodes = length(nodes)

  # Create the master model
  m = Model(:Min)

  # Create a variable for every route
  @defVar(m, 0 <= x[1:num_routes] <= 1)

  # Minimize cost of selected routes
  @setObjective(m, sum{routes[r].cost * x[r], r=1:num_routes})

  # All locations at all times must be visited at least once if
  # it has non-zero demand
  @defConstrRef node_visits[1:num_nodes, 1:24]
  # For every node...
  for i = 1:num_nodes
    # For every hour of the day...
    for t = 1:24
      # If there is demand, add a constraint
      if nodes[i].demand[t] > 0
        node_visits[i,t] = @addConstraint(m, 
                             sum{routes[r].visits[i,t]*x[r], r=1:num_routes} >= 1)
      end
    end
  end

  # Solve LP
  println("  MASTER: Solving...")
  status = solve(m)
  if status == :Infeasible
    error("Master was infeasible somehow!")
  end
  println("  MASTER: Solved, objective = $(getObjectiveValue(m))")

  # Get duals out of solution
  node_duals = zeros(num_nodes, 24)
  for i = 1:num_nodes
    for t = 1:24
      if nodes[i].demand[t] > 0
        node_duals[i,t] = getDual(node_visits[i,t])
      end
    end
  end

  # Get selected routes
  sel_routes = Route[]
  for r = 1:num_routes
    routes[r].x = getValue(x[r])
    if routes[r].x > 1e-5
      push!(sel_routes, routes[r])
    end
  end

  return node_duals, sel_routes

end


#####################################################################
# SolveSubproblem
# Given duals, calculate a minimum cost route
function SolveSubproblem(node_duals, nodes, dists, depot_dists)

  num_nodes = length(nodes)
  depot = num_nodes+1
  # Define a function-in-a-function that calculates the distance
  # between two locations adjusted for the duals and the time slice
  # that virtual node refers to
  # Depot is the (n+1)th location
  function adjDist(i,t_i, j,t_j)
    if i == depot
      if j == depot
        # Depot to depot
        return 0
      else
        # Depot to non-depot
        return depot_dists[j] - node_duals[j,t_j]
      end
    else
      if j == depot
        # Non-depot to depot
        return depot_dists[i]
      else
        # Non-depot to non-depot
        if i == j
          if t_j <= t_i
            return 10000.0
          else
            # No travel distance
            return -node_duals[j,t_j] + 1e-6
          end
        else
          return dists[i,j] - node_duals[j,t_j]
        end
      end
    end
  end

  m = Model(:Min, mipsolver=MIPSolver(:Gurobi))

  # Whether to travel between (i,t_i) and (j,t_j)
  @defVar(m, 0 <= x[i=1:depot, t_i=1:24, j=1:depot, t_j=1:24] <= 1, Int)

  # Arrival time at (i,t_i) (day starts at 0, so can arrival at (i,t_i) from t_i-1
  @defVar(m, t_i - 1 <= A[i=1:depot, t_i=1:24] <= 24)

  # Min cost of route
  @setObjective(m, sum{adjDist(i,t_i,j,t_j)*x[i,t_i,j,t_j], i=1:depot, t_i=1:24,
                                                            j=1:depot, t_j=1:24})

  # No self-visits
  for i = 1:depot
    for t_i = 1:depot
      @addConstraint(m, x[i,t_i,i,t_i] == 0)
    end
  end

  # Must leave from depot
  @addConstraint(m, sum{x[depot,t_i, j,t_j], t_i=1:24, j=1:depot, t_j=1:24} == 1)
  
  # Must return to depot
  @addConstraint(m, sum{x[i,t_i, depot,t_j], i=1:depot, t_i=1:24, t_j=1:24} == 1)

  # Must enter and leave every (virtual) node same number of times
  for k = 1:num_nodes
    for t_k = 1:24
      @addConstraint(m, sum{x[i,t_i, k,t_k], i=1:depot, t_i=1:24} ==
                        sum{x[k,t_k, j,t_j], j=1:depot, t_j=1:24})
    end
  end

  # Capacity limits (what is reasonable?!)
  const CAP_LIMIT = 2500.0
  @addConstraint(m, sum{nodes[j].demand[t_j]*x[i,t_i,j,t_j], i=1:depot, t_i=1:24,
                                                             j=1:num_nodes, t_j=1:24} <= CAP_LIMIT)

  # Time windows
  # How to turn the lat-lon distance into travel times?!
  const SCALE = 0.1
  const BIGM = 50.0
  for i = 1:depot
    for t_i = 1:24
      for j = 1:num_nodes  # Can return home anytime
        if i == depot
          d = depot_dists[j]*SCALE
        else
          d = dists[i,j]*SCALE
        end
        for t_j = 1:24
          @addConstraint(m, A[i,t_i] + d*SCALE <= A[j,t_j] + BIGM*(1.0 - x[i,t_i,j,t_j]))
        end
      end
    end
  end

  println("  SUB: Finding route")
  solve(m)
  println("  SUB: Solved, objective = $(getObjectiveValue(m))")
  if getObjectiveValue(m) < -1e-6
    println("  SUB: Found route")
    visits = zeros(num_nodes, 24)
    cost = 0.0
    cap_used = 0
    for i = 1:depot
      for t_i = 1:24
        #println("A[$i,$t_i] = $(getValue(A[i,t_i]))")
        for j = 1:depot
          for t_j = 1:24
            if getValue(x[i,t_i,j,t_j]) > 1-1e-4
              #println("x[$i,$t_i, $j,$t_j] = $(getValue(x[i,t_i,j,t_j]))")
              #if j < depot
              #  println("cap used up $(nodes[j].demand[t_j])")
              #end
              if i == depot && j == depot
                # Depot to depot...!
              elseif i == depot
                # Depot to not-depot
                cost += depot_dists[j]
              elseif j == depot
                # Non-depot to depot
                cost += depot_dists[i]
              else
                cost += dists[i,j]
              end
              if j < depot
                # Visited j
                visits[j,t_j] = 1
              end
            end
          end
        end
      end
    end
    return Route(cost, visits, 0.0)
  else
    # no new route
    println("  SUB: Didn't find route")
    return nothing
  end
end



#####################################################################
# PrintRoutes
function PrintRoutes(routes, nodes, thresh=0.1)
  num_nodes = length(nodes)
  
  println( "R#  | \$     | Visits | Picked up")
  for r in 1:length(routes)
    route = routes[r]
    if route.x < thresh
      continue
    end
    cap_used = 0
    #@printf("%3d | %10.5f | ", r, route.cost)
    print("$r | $(route.cost) | ")
    for i = 1:num_nodes
      for t_i = 1:24
        if route.visits[i,t_i] >= 1
          @printf("(%3d,%2d) ", i, t_i)
          cap_used += nodes[i].demand[t_i]
        end
      end
    end
    println("| $cap_used | $(route.x)")
  end
end

function SolveVRP()
  nodes = LoadData("demand.csv")
  # Truncate nodes for testing purposes
  nodes = nodes[1:1]
  num_nodes = length(nodes)
  dists = CalculatePairwise(nodes)
  println(dists)

  # Not sure where the main depot is so just take average of all nodes
  # lat/lon for now
  depot_lat = 0
  depot_lon = 0
  for node in nodes
    depot_lat += node.lat + 5
    depot_lon += node.lon + 5
  end
  depot_lat /= num_nodes
  depot_lon /= num_nodes
  depot_dists = zeros(num_nodes)
  for i = 1:num_nodes
    depot_dists[i] = sqrt((depot_lat - nodes[i].lat)^2 + (depot_lon - nodes[i].lon)^2)
  end
  println(depot_dists)

  # Provide default set of routes
  # Initially just use one truck for every location and time of day
  routes = Route[]
  for i = 1:num_nodes
    for t = 1:24
      if nodes[i].demand[t] > 0
        visits = zeros(num_nodes, 24)
        visits[i,t] = 1
        new_route = Route(depot_dists[i]*2, visits, 1.0)
        push!(routes, new_route)
      end
    end
  end
  PrintRoutes(routes, nodes)

  # Iterate until no new routes generated
  # (except for now, just do 10 passes)
  for iter = 1:20
    println("ITER $iter")
    # Solve master problem to get duals
    node_duals, sel_routes = SolveMaster(routes, nodes)
    # Solve sub problem to get a new route (maybe)
    new_route = SolveSubproblem(node_duals, nodes, dists, depot_dists)

    if new_route == nothing
      # Done!
      println("Done")
      break
    else
      # Add route
      push!(routes, new_route)
    end
  end
  println("Selected routes:")
  PrintRoutes(routes, nodes)

end

SolveVRP()
