using Gurobi

###############################################################################
# CheckVisitedBefore
# Checks if a partial path includes a node
function CheckVisitedBefore(partial, j, t_j)
  #for prev_node in partial.order
  #  if prev_node[1] == j && prev_node[2] == t_j
  #    # Visited before, skip
  #    return true
  #  end
  #end
  #return false
  return partial.visited[j,t_j]
end

###############################################################################
# CleanPaths
# Cleans out dead paths from a node
function CleanPaths(partial_paths)
  new_paths = Path[]
  for partial in partial_paths
    if !partial.dead
      push!(new_paths, partial)
    end
  end
  return new_paths
end

###############################################################################
# ExtendPath
# Takes a Path and adds on the desired node
function ExtendPath(partial, rc, dist, demand, arrival_time, j, t_j, counter)
  new_path = Path(partial.rc + rc,
                  partial.dist + dist,
                  partial.res_used + demand,
                  copy(partial.order),
                  arrival_time,
                  partial.first_time,
                  false,
                  counter + 1,
                  copy(partial.visited))
  push!(new_path.order, (j,t_j))
  new_path.visited[j,t_j] = true
  return new_path
end

###############################################################################
# DebugPrintRoutes
# Displays the current set of routes
# Input:
#  partial_paths        Dictionary of lists, keyed by (i,t_i)
#  num_nodes            Number of nodes in graph
# Output:
#  Prints to STDOUT
function DebugPrintRoutes(partial_paths, num_nodes)
  count = 0
  for i = 1:(num_nodes+1)
    for t_i = 1:24
      if length(partial_paths[(i,t_i)]) == 0
        continue
      end
      println("$(i<=num_nodes ? i : :Depot) $t_i")
      for partial in partial_paths[(i,t_i)]
        println("  ", partial)
        count += 1
      end
    end
  end
  println("Count: $count")
end


###############################################################################
# SeedPaths
# Creates initial lists of partial paths at each node
# Input:
#  nodes                List of nodes
#  node_duals           Dual value for each (i,t_i)
#  depot_dists          Distances from depot to nodes
# Output:
#  partial_paths        Dictionary of lists, keyed by (i,t_i)
function SeedPaths(nodes, node_duals, depot_dists)
  num_nodes = length(nodes)
  partial_paths = Array(Vector{Path},(num_nodes+1,24))

  for i = 1:num_nodes
    for t_i = 1:24
      # Create empty array
      partial_paths[i,t_i] = Path[]
      # OPT: Don't seed routes to nodes without demand - never need to visit
      demand = nodes[i].demand[t_i]
      if demand == 0
        continue
      end
      # OPT: Don't consider non-neg arcs - don't improve objective, and we go
      #      anywhere from anywhere so not considering doesn't block access.
      rc = depot_dists[i] - node_duals[i,t_i]
      if rc >= -TOL
        continue
      end
      # Seed new path to this node
      visited = zeros(Bool, num_nodes, 24)
      visited[i,t_i] = true
      newPath = Path(rc,                # Reduced cost so far (goal is for negative)
                     depot_dists[i],    # True miles travelled
                     demand,            # Resources used so far
                     [(i,t_i)],         # Path so far (just this node)
                     max(depot_dists[i]*DISTTIME, t_i),  # cur end of path time
                     t_i,               # First pickup time
                     false,             # Mark route as not-dead
                     1,                 # Generation
                     visited)           # Nodes visited
      push!(partial_paths[i,t_i], newPath)
    end
  end

  # Routes end at depot
  for t_depot = 1:24
    partial_paths[num_nodes+1, t_depot] = Path[]
  end

  return partial_paths
end


###############################################################################
# SolveSubproblem
# Given duals, calculate a minimum cost route
function SolveSubproblem(node_duals, nodes, dists, depot_dists)

  num_nodes = length(nodes)
  # Depot is the (n+1)th location
  depot = num_nodes+1

  # Initiliaze paths by starting a route to all contender nodes
  partial_paths = SeedPaths(nodes, node_duals, depot_dists)
  
  # Build paths!
  println("  SUB: Finding route")
  for arbitrary_counter = 1:10
    print(" $arbitrary_counter")
    # Phase 1 - Extend paths
    for i = 1:num_nodes
      for t_i = 1:24
        for partial_ind in 1:length(partial_paths[i,t_i])
          partial = partial_paths[i,t_i][partial_ind]
          # TODO: Does it make a difference if we do things "generationally"
          #       or should we just do them as fast as we can?
          #if partial.generation > arbitrary_counter
          #  continue
          #end
          
          # Consider any extension that
          #  - Wouldn't be a revisit of an existing node
          #    TODO: tradeoff memory for speed by caching visited list?
          #  - Wouldn't result in capacity used going over CAPACITY
          #  - Wouldn't result in total time out going over MAXTRUCKTIME
          
          # SPECIAL CASE: DEPOT
          # j = depot
          # Only worth coming back straight away, why come back later?
          # Need to check we won't get back too late though
          arrival_time = partial.early_time + depot_dists[i]*DISTTIME
          if arrival_time - partial.first_time >= MAXTRUCKTIME
            # OPT: This path can not make it back to the depot
            # As a result any further extension of this path is pointless -
            # kill it now.
            partial.dead = true
            continue  # Move onto next partial at this node
          end
          # Made it back in time, add to depots list
          # TODO: Because we never extend these, perhaps shouldn't even bother with
          #       this churn? Probably not time critical
          new_path = Path(partial.rc + depot_dists[i],
                          partial.dist + depot_dists[i],
                          partial.res_used,
                          copy(partial.order),
                          arrival_time,
                          partial.first_time,
                          false,
                          arbitrary_counter + 1,
                          copy(partial.visited))
          push!(new_path.order, (depot, t_i))  # PERF: 10% (this and prev)
          push!(partial_paths[depot,t_i], new_path)

          # OTHER NODES
          for j = 1:num_nodes
            # Only move forward in time at individual nodes - i.e. can't go from
            # (i=5,t_i=4) to (i=5,t_i=3)
            min_t_j = (i == j) ? (t_i + 1) : 1
            max_t_j = 24

            for t_j = min_t_j:max_t_j
              extension_rc = dists[i,j] - node_duals[j,t_j]

              # OPT: Don't go here if it isn't going to help
              if extension_rc >= -TOL
                continue
              end
              demand_j_t_j = nodes[j].demand[t_j]  # PERF 7%
              if demand_j_t_j == 0
                continue
              end

              # Check - Visited before (elementary-ness)
              if CheckVisitedBefore(partial, j, t_j)  # PERF 3%
                continue
              end

              # Check Would going here violate capacity? Is there demand there?
              if demand_j_t_j + partial.res_used > CAPACITY  # PERF 5%
                continue
              end

              # Check Would going here violate time limit?
              arrival_time = max(partial.early_time + dists[i,j]*DISTTIME, t_j)
              if arrival_time - partial.first_time >= MAXTRUCKTIME
                 continue
              end

              # This path is OK then
              # Add (j,t_j) to it and move it to that node
              push!(partial_paths[j,t_j], ExtendPath(partial, extension_rc, dists[i,j],
                                                     demand_j_t_j, arrival_time, j, t_j,
                                                     arbitrary_counter))  # PERF 12%
            end  # t_j
          end  # j
          partial.dead = true
        end  # for partial in partial_paths
        
        # Clear out the now-extended paths and only keep new ones
        partial_paths[i,t_i] = CleanPaths(partial_paths[i,t_i])
      end  # t_i
    end  # i

    # Phase 2 - Dominate
    # Only at depot for now
    #DebugPrintRoutes(partial_paths, num_nodes)
  end  # while
  #DebugPrintRoutes(partial_paths, num_nodes)

  # Pick path at depot with lowest RC
  best_rc = Inf
  best_dist = Inf
  best_path = nothing
  for t_i = 1:24
     for path in partial_paths[depot,t_i]
       # Strictly better RC?
       if path.rc < best_rc - 1e-6
         best_rc = path.rc
         best_dist = path.dist
         best_path = path
       # Same RC but shorter dist
       elseif path.rc <= best_rc + 1e-6
         if path.dist < best_dist - 1e-6
           best_rc = path.rc
           best_dist = path.dist
           best_path = path
         end
       end
     end
   end

  if best_rc < -1e-6
    # New route!
    println("  SUB: Found route")
    visits = zeros(num_nodes, 24)
    for visited in best_path.order
      i,t_i = visited
      if i == depot
        continue
      end
      visits[i,t_i] = 1
    end
    return Route(best_dist, visits, 0.0)
  else
    # no new route
    println("  SUB: Didn't find route")
    return nothing
  end
end

