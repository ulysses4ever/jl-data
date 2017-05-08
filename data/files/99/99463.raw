using Gurobi


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

  m = Model(:Min, mipsolver=GurobiSolver())

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
