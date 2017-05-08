###############################################################################
# GenerateInitialRoutes
# Use heuristic to generate not-crazy initial set of routes.
# Inputs:
#  nodes        List of nodes
#  dists        Node-node distance matrix
#  depot_dists  Node-depot distance vector
# Outputs:
#  routes       List of initial routes that satisfies requirement that all
#               demand be picked up.
function GenerateInitialRoutes(nodes, dists, depot_dists)
  num_nodes = length(nodes)
  
  routes = Route[]
  # For every node...
  for i = 1:num_nodes
    # Beginnning at start of time, start picking up demand until
    # fill up capacity
    cur_route = Route(depot_dists[i]*2, zeros(num_nodes,24), 1.0)
    cur_route_cap_left = CAPACITY
    for t = 1:24
      cur_demand = nodes[i].demand[t]
      if cur_demand == 0
        continue
      elseif cur_demand > cur_route_cap_left
        # Can't fit this one in
        # Start new one with it
        push!(routes, cur_route)
        cur_route = Route(depot_dists[i]*2, zeros(num_nodes,24), 1.0)
        cur_route.visits[i,t] = 1
        cur_route_cap_left = CAPACITY - cur_demand
      elseif cur_demand <= cur_route_cap_left
        # Can fit this one in!
        cur_route_cap_left -= cur_demand
        cur_route.visits[i,t] = 1
      end
    end
    if sum(cur_route.visits) > 0
      # Current route has done some visiting, we need to add it
      push!(routes, cur_route)
    end
  end

  return routes
end

###############################################################################
# NaiveInitialRoutes
# The old algorithm for generating initial routes. Simply one truck per time
# slot per location.
# Inputs:
#  nodes        List of nodes
#  dists        Node-node distance matrix
#  depot_dists  Node-depot distance vector
# Outputs:
#  routes       List of initial routes that satisfies requirement that all
#               demand be picked up.
function NaiveInitialRoutes(nodes, dists, depot_dists)
  num_nodes = length(nodes)
  
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

  return routes
end

