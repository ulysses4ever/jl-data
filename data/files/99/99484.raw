using JuMP

const DISTTIME = 1/50  # Assume 50mph
const CAPACITY = 2500
const MAXTRUCKTIME = 8  # From first pickup
const TOL = 1e-6

# Distance calculations
include("distance.jl")
# Initial route generation
include("initial.jl")
# VRP master problem
include("master.jl")
# VRP subproblem (route generation)
include("routegen.jl")
#include("old_code/old_routegen.jl")

#####################################################################
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

type Path
  rc            # reduced cost so far
  dist          # true distance so far
  res_used      # resources used so far
  order         # order of virtual nodes visited
  early_time    # earliest possible time to be at end of path
  first_time    # time of first pickup
  dead          # Hack for now
  generation    # Hack for now
  visited       # Boolean matrix of previously visited nodes
end
function print(io::IO, p::Path)
  print(io,"Path(")
  print(io,"RC:",round(p.rc,2))
  print(io,",D:",round(p.dist,2))
  print(io,",RES:",p.res_used,",[")
  for o in p.order
    print(io,"(",o[1],"-",o[2],")")
  end
  print(io,"],ET:",int(p.early_time))
  print(io,",FT:",int(p.first_time))
  print(io,")")
end

#####################################################################
# CalculatePairwise
# Use great-circle distance to calculate pairwise node distances
function CalculatePairwise(nodes)
  N = length(nodes)
  latlon = zeros(N,2)
  for i = 1:N
    latlon[i,1] = nodes[i].lat
    latlon[i,2] = nodes[i].lon
  end
  return buildDistanceMatrix(latlon)
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
  nodes = nodes[1:4]
  num_nodes = length(nodes)
  dists = CalculatePairwise(nodes)
  println(dists)

  # Not sure where the main depot is so just take average of all nodes
  # lat/lon for now
  depot_lat = 0
  depot_lon = 0
  for node in nodes
    depot_lat += node.lat + 0.1
    depot_lon += node.lon + 0.1
  end
  depot_lat /= num_nodes
  depot_lon /= num_nodes
  depot_dists = zeros(num_nodes)
  for i = 1:num_nodes
    depot_dists[i] = haversine(nodes[i].lat, nodes[i].lon, depot_lat, depot_lon)
  end
  depot_dists .*= 0.621371  # km to miles
  println(depot_dists)

  # Provide default set of routes
  # Initially just use one truck for every location and time of day
  routes = GenerateInitialRoutes(nodes, dists, depot_dists)
  #routes = NaiveInitialRoutes(nodes, dists, depot_dists)
  PrintRoutes(routes, nodes)
  a = readline(STDIN)

  # Iterate until no new routes generated
  # (except for now, just do 10 passes)
  total_master_time = 0.0
  total_routegen_time = 0.0
  for iter = 1:10
    println("ITER $iter")
    # Solve master problem to get duals
    tic()
    node_duals, sel_routes = SolveMaster(routes, nodes)
    total_master_time += toq()
    # Solve sub problem to get a new route (maybe)
    tic()
    new_route = SolveSubproblem(node_duals, nodes, dists, depot_dists)
    total_routegen_time += toq()

    @profile SolveSubproblem(node_duals, nodes, dists, depot_dists)
    

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
  println("Run time:")
  println("Master: $total_master_time")
  println("Routegen: $total_routegen_time")
  println("Total: $(total_master_time + total_routegen_time)")

  Profile.print(format=:flat)
end

SolveVRP()
