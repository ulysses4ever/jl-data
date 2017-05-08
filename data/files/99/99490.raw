using JuMP

const DISTTIME = 1/50  # Assume 50mph
const CAPACITY = 2500
const MAXTRUCKTIME = 8  # From first pickup
const TOL = 1e-6
const TRUCKFIXED = 0.5


# INPUT PARAMETERS
const DEMAND_INPUT_FILE = "new_demand.csv"
const LAMBDA = 0.8
const PRINT_LEVEL = 0 # true - full printf on false - off

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
  rc::Float64           # reduced cost so far
  dist::Float64         # true distance so far
  res_used::Int         # resources used so far
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

###############################################################################
# CalculatePairwise
# Use great-circle distance to calculate pairwise node distances
# Inputs:
#  nodes        List of nodes
# Outputs:
#  dmat         Pairwise distance matrix in km
function CalculatePairwise(nodes)
  N = length(nodes)
  latlon = zeros(N,2)
  for i = 1:N
    latlon[i,1] = nodes[i].lat
    latlon[i,2] = nodes[i].lon
  end
  return buildDistanceMatrix(latlon)
end

###############################################################################
# LoadData
# Loads the demand and location data from a .csv file
# Inputs:
#  filepath     filepath to demand dataset
# Outputs:
#  nodes        Array of Nodes structure
function LoadData!(filepath, nodes)
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
end


###############################################################################
# PrintRoutes
#  Prints the routes in the form of the route number, cost, # of Visits, and Demand
#  picked up at that node during the visit
# Inputs:
#  routes
#  nodes
#  thresh
# Outputs:
#  none
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


# Function:  SolveVRP
# --------------------
#   description:    solves vehicle route problem
#   inputs:         the weight to apply to the minimum cost portion of the object function
#   outputs:        Optimal routes in printf form
function SolveVRP(lambda)
  # load in demand data for the nodes in consideration
  # Build up list of nodes
  nodes = Node[]
  LoadData!(DEMAND_INPUT_FILE, nodes)
  println("Loaded demand file: ", DEMAND_INPUT_FILE)

  # Truncate nodes for testing purposes
  nodes = nodes[2:2]

  # for every node calculate the pairwise greater circle distance
  num_nodes = length(nodes)
  dists = CalculatePairwise(nodes)
  if PRINT_LEVEL == 1
    println(dists)
  end
  println("Calculated pairwise greater circle distances")

  # Depot location is in Central Square
  depot_lat = 42.36376 #0
  depot_lon = -71.10028 #0

  #for node in nodes
  #  depot_lat += node.lat + 0.1
  #  depot_lon += node.lon + 0.1
  #end
  #depot_lat /= num_nodes
  #depot_lon /= num_nodes
  depot_dists = zeros(num_nodes)
  for i = 1:num_nodes
    depot_dists[i] = haversine(nodes[i].lat, nodes[i].lon, depot_lat, depot_lon)
  end
  depot_dists .*= 0.621371  # km to miles
  if PRINT_LEVEL == 1
    println(depot_dists)
  end

  # Provide default set of routes
  # Initially just use one truck for every location and time of day
  routes = GenerateInitialRoutes(nodes, dists, depot_dists, lambda)
  println("Generated initial routes")
  if PRINT_LEVEL == 1
    PrintRoutes(routes, nodes)
  end

  println("Hit enter to start solving")
  a = readline(STDIN)

  # Iterate until no new routes generated
  # (except for now, just do 10 passes)
  total_master_time = 0.0
  total_routegen_time = 0.0
  for iter = 1:100
    println("ITER $iter")
    # start timer
    tic()
    # Solve master problem to get duals
    node_duals, sel_routes = SolveMaster(routes, nodes)
    total_master_time += toq()
    # Solve sub problem to get a new route (maybe)
    tic()
    new_route = SolveSubproblem(node_duals, nodes, dists, depot_dists, lambda)
    total_routegen_time += toq()
    if new_route == nothing
      # Done!
      println("Done")
      break
    else
      # Add route
      println("New route:")
      PrintRoutes([new_route], nodes, -0.1)
      push!(routes, new_route)
    end
  end
  println("Selected routes:")
  PrintRoutes(routes, nodes)
  println("Run time:")
  println("Master: $total_master_time")
  println("Routegen: $total_routegen_time")
  println("Total: $(total_master_time + total_routegen_time)")

  #Profile.print(format=:flat)
end

SolveVRP(LAMBDA)
