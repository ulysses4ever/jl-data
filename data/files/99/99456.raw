###############################################################################
# SolveMaster
# Given a set of routes, select a subset that takes all demand
# for minimum cost.
# Inputs:
#  routes
#  nodes
# Outputs:
#  node_duals
#  sel_routes
function SolveMaster(routes, nodes)
  # Solve the master problem, returns the duals
  num_routes = length(routes)
  num_nodes = length(nodes)

  # Create the master model (See VRPDP.pdf for model definition)
  m = Model()

  # Create a variable for every route
  @defVar(m, 0 <= x[1:num_routes] <= 1)

  # Minimize cost of selected routes
  @setObjective(m, Min, sum{routes[r].cost * x[r], r=1:num_routes})

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


###############################################################################
# SolveMasterMIP
# Given a set of routes, select a subset that takes all demand
# for minimum cost AND IS INTEGER
# Inputs:
#  routes
#  nodes
# Outputs:
#  node_duals
#  sel_routes
function SolveMasterMIP(routes, nodes)
  # Solve the master problem, returns the duals
  num_routes = length(routes)
  num_nodes = length(nodes)

  # Create the master model (See VRPDP.pdf for model definition)
  m = Model()

  # Create a variable for every route
  @defVar(m, 0 <= x[1:num_routes] <= 1, Int)

  # Minimize cost of selected routes
  @setObjective(m, Min, sum{routes[r].cost * x[r], r=1:num_routes})

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

  # Solve MILP
  status = solve(m)

  # Get selected routes
  sel_routes = Route[]
  for r = 1:num_routes
    routes[r].x = getValue(x[r])
    if routes[r].x > 1e-5
      push!(sel_routes, routes[r])
    end
  end

  return sel_routes, getObjectiveValue(m)
end
