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
function GenerateInitialRoutes(nodes, dists, depot_dists, lambda)
  num_nodes = length(nodes)
  
  routes = Route[]

  # Set 1: Take everything from a node in one go, as well as
  #        every split in between
  for i = 1:num_nodes
    # Figure out times with demand
    demand_ts = Int[]
    for t_i = 1:24
      if nodes[i].demand[t_i] > 0
        push!(demand_ts, t_i)
      end
    end
    if length(demand_ts) == 0
      continue
    end
    # For every possible split
    for split = 1:length(demand_ts)
      part_a = demand_ts[1:split]
      part_a_T = maximum(part_a) + depot_dists[i]*DISTTIME
      route_a = Route(TRUCKFIXED + depot_dists[i]*2*lambda, zeros(num_nodes,24), 1.0)
      for t_i in part_a
        route_a.visits[i,t_i] = 1
        route_a.cost += (1-lambda)*(part_a_T - t_i)*nodes[i].demand[t_i]
      end
      push!(routes, route_a)

      part_b = demand_ts[(split+1):end]
      if length(part_b) == 0
        continue
      end
      part_b_T = maximum(part_b) + depot_dists[i]*DISTTIME
      route_b = Route(TRUCKFIXED + depot_dists[i]*2*lambda, zeros(num_nodes,24), 1.0)
      for t_i in part_b
        route_b.visits[i,t_i] = 1
        route_b.cost += (1-lambda)*(part_b_T - t_i)*nodes[i].demand[t_i]
      end
      push!(routes, route_b)
    end
  end

  # Set 2: One truck per time
  for i = 1:num_nodes
    for t_i = 1:24
      cur_demand = nodes[i].demand[t_i]
      if cur_demand > 0
        cur_route = Route(0, zeros(num_nodes,24), 1.0)
        cur_route.visits[i,t_i] = 1
        cur_route.cost = TRUCKFIXED +
                            lambda *depot_dists[i]*2 +
                         (1-lambda)*depot_dists[i]*DISTTIME*cur_demand
        push!(routes, cur_route)
      end
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

