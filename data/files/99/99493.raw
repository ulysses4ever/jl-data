using JuMP

const DISTTIME = 1/50  # Assume 50mph
const CAPACITY = 2500
const MAXTRUCKTIME = 8  # From first pickup
const TOL = 1e-6
const TRUCKFIXED = 3.0


# INPUT PARAMETERS
const DEMAND_INPUT_FILE = "new_demand.csv"
const LAMBDA = 0.95
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
#  bunchsize    aggregate demand into bunchsize blocks
#               e.g. =2 -> D(t=2)' = D(t=1)+D(t=2)
# Outputs:
#  nodes        Array of Nodes structure
function LoadData!(filepath, nodes, bunchsize=1)
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
    # Bunch demand, if desired
    new_demand = new_node.demand[:]
    for t_i = bunchsize:bunchsize:24
      accum = 0
      for t_j = (t_i-bunchsize+1):t_i
        accum += new_demand[t_j]
        new_demand[t_j] = 0
      end
      new_demand[t_i] = accum
    end
    new_node.demand = new_demand
    #println(new_demand)
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
  LoadData!(DEMAND_INPUT_FILE, nodes, 4)
  println("Loaded demand file: ", DEMAND_INPUT_FILE)

  # Truncate nodes for testing purposes
  #nodes = nodes[1:]

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
  for iter = 1:50
    println("ITER $iter")
    # start timer
    tic()
    # Solve master problem to get duals
    node_duals, sel_routes = SolveMaster(routes, nodes)
    total_master_time += toq()
    # Solve integer solution to get cur solution
    sel_mip_routes, mip_obj = SolveMasterMIP(routes, nodes)
    println("Current integer solution: $mip_obj")
    PrintRoutes(sel_mip_routes, nodes)
    # Solve sub problem to get new routes (maybe)
    tic()
    new_routes = SolveSubproblem(node_duals, nodes, dists, depot_dists, lambda)
    total_routegen_time += toq()
    if length(new_routes) == 0
      # Done!
      println("Done")
      break
    else
      # Add routes
      println("New routes:")
      PrintRoutes(new_routes, nodes, -0.1)
      for r in new_routes
        push!(routes, r)
      end
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
