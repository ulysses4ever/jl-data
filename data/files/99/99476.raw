using Gurobi
using JuMP

function SolveMIP(node_duals, nodes, dists, depot_dists, lambda, T, harsh=false)
  num_nodes = length(nodes)
  depot = num_nodes+1  # Depot is the (n+1)th location

  m = Model(:Min, mipsolver=GurobiSolver(OutputFlag=0, MIPGap=0.10))

  @defVar(m, x[i=1:depot,t_i=1:24,j=1:depot,t_j=1:24], Bin)
  @defVar(m, a[i=1:depot,t_i=1:24] >= t_i)
  @defVar(m, trueT >= 0)

  coefs = zeros(depot,24,depot,24)
  const BIGM = 24.0

  for i = 1:depot
    for t_i = 1:24
      for j = 1:depot
        for t_j = 1:24
          # No back-in-time or self links
          # No link if no demand
          # Harsh mode: if available after time limit, not allowed to go there
          # If dual isn't non-zero, its definitely going to be there
          dead = false
          if (i == j && t_j <= t_i) ||
             (j < depot && nodes[j].demand[t_j] <= 0) ||
             (t_j > T && harsh) ||
             (j < depot && node_duals[j,t_j] == 0)
            @addConstraint(m, x[i,t_i,j,t_j] == 0)
            dead = true
          end

          # Objective coefficient
          if !dead   
            if i == depot && j == depot  # x[D,D]
              coefs[i,t_i,j,t_j] = 0.0
            elseif i == depot && j < depot  # x[D,j]
              coefs[i,t_i,j,t_j] = lambda*depot_dists[j] - node_duals[j,t_j] +
                                   (1-lambda)*nodes[j].demand[t_j]*(T - t_j)
            elseif i < depot && j == depot  # x[i,D]
              coefs[i,t_i,j,t_j] = lambda*depot_dists[i]
            else  i < depot && j < depot  # x[i,j]
              coefs[i,t_i,j,t_j] = lambda*dists[i,j] - node_duals[j,t_j] +
                                   (1-lambda)*nodes[j].demand[t_j]*(T - t_j)
            end

            if j < depot
              # Time windows
              dist_to_use = (i == depot) ? depot_dists[j] : dists[i,j]
              @addConstraint(m, a[j,t_j] >= a[i,t_i] + dist_to_use*DISTTIME - BIGM*(1-x[i,t_i,j,t_j]))
            end # non-depot
          end # !dead
        end # t_j
      end # j

      # Return time to depot
      if i < depot
        for t_j = 1:24
          @addConstraint(m, trueT >= a[i,t_i] + depot_dists[i]*DISTTIME - BIGM*(1-x[i,t_i,depot,t_j]))
        end
      end
      # Each node has at most one link out
      @addConstraint(m, sum{x[i,t_i,j,t_j], j=1:depot,t_j=1:24} <= 1)
    end # t_i
  end # i
  @setObjective(m, sum{coefs[i,t_i,j,t_j]*x[i,t_i,j,t_j], i=1:depot,t_i=1:24,j=1:depot,t_j=1:24} + 1e-6*trueT)

  # Links in = links out
  for k = 1:num_nodes
    for t_k = 1:24
      @addConstraint(m, sum{x[i,t_i,k,t_k], i=1:depot,t_i=1:24} == sum{x[k,t_k,j,t_j], j=1:depot,t_j=1:24})
    end
  end

  # Gotta leave depot and come back there
  @addConstraint(m, sum{x[depot,t_i,j,t_j], t_i=1:24,j=1:num_nodes,t_j=1:24} == 1)
  @addConstraint(m, sum{x[i,t_i,depot,t_j], i=1:num_nodes,t_i=1:24,t_j=1:24} == 1)

  status = solve(m)
  if status != :Optimal
    return zeros(num_nodes,24,num_nodes,24), T, Inf, Inf
  end

  colObj = 0.0
  rcObj = 0.0
  trueT = getValue(trueT)
  for i = 1:depot
    for t_i = 1:24
      for j = 1:depot
        for t_j = 1:24
          x_ij = getValue(x[i,t_i,j,t_j])
          if x_ij <= 1e-6
            continue
          end

          if i == depot && j == depot  # x[D,D]
            # Nothing

          elseif i == depot && j < depot  # x[D,j]
            colObj += lambda    *depot_dists[j] +
                      (1-lambda)*nodes[j].demand[t_j]*(trueT - t_j)
            rcObj  += lambda    *depot_dists[j] +
                      (1-lambda)*nodes[j].demand[t_j]*(trueT - t_j) -
                      node_duals[j,t_j]

          elseif i < depot && j == depot  # x[i,D]
            colObj += lambda*depot_dists[i] 
            rcObj  += lambda*depot_dists[i]

          else  i < depot && j < depot  # x[i,j]
            colObj += lambda    *dists[i,j] +
                      (1-lambda)*nodes[j].demand[t_j]*(trueT - t_j)
            rcObj  += lambda    *dists[i,j] +
                      (1-lambda)*nodes[j].demand[t_j]*(trueT - t_j) -
                      node_duals[j,t_j]
          end
        end
      end
    end
  end

  #println("         MIP Sol:")
  #for i = 1:depot
  #  for t_i = 1:24
  #    for j = 1:depot
  #      for t_j = 1:24
  #        if getValue(x[i,t_i,j,t_j]) > 1e-6
  #          println("           $i $t_i $j $t_j")
  #        end
  #      end
  #    end
  #  end
  #end
  return getValue(x), trueT, colObj+TRUCKFIXED, rcObj+TRUCKFIXED
end


###############################################################################
# SolveSubproblem
# Given duals, calculate a minimum cost route
function SolveSubproblem(node_duals, nodes, dists, depot_dists, lambda)

  num_nodes = length(nodes)
  depot = num_nodes+1  # Depot is the (n+1)th location

  #println("  node_duals")
  #for i = 1:num_nodes
  #  for t_i = 1:24
  #    if node_duals[i,t_i] != 0.0
  #      println("    $i $t_i $(node_duals[i,t_i])")
  #    end
  #  end
  #end

  # Grid search initially
  println("  SUB: Grid search on T")
  first_T = 24
  last_T = 0
  for i = 1:num_nodes
    for t_i = 1:24
      if node_duals[i,t_i] != 0.0
        first_T = min(first_T, t_i) + 0.5
        last_T  = max(last_T,  t_i) + 0.5
      end
    end
  end
  #blah = readline(STDIN)
  best_x, best_T, best_colObj, best_rcObj = SolveMIP(node_duals, nodes, dists, depot_dists, lambda, first_T-1, true)
  for grid_T = (first_T):1:(last_T)
    #println("       grid_T = $grid_T")
    cur_x, cur_T, cur_colObj, cur_rcObj = SolveMIP(node_duals, nodes, dists, depot_dists, lambda, grid_T, true)
    if cur_colObj < 0
      # WTF happened
      println("        Something aberrant happened for grid_T = $grid_T, colobj < 0")
      continue
    end
    if cur_rcObj < best_rcObj - 1e-6
      best_x = cur_x[1:depot,1:24,1:depot,1:24]
      best_T = cur_T
      best_colObj = cur_colObj
      best_rcObj = cur_rcObj
      #if best_rcObj < -1e-6
      #  break
      #end
    end
    #println("       $cur_colObj")
    #blah = readline(STDIN)
  end
  println("  SUB: Best initial T: ", best_T)
  println("  SUB: Best initial rc: ", best_rcObj)
  println("  SUB: Best initial col: ", best_colObj)
  next_T = best_T

  for iter = 1:10
    if best_rcObj < -1e-6
      break
    end
    println("  SUB: Iter $iter, next_T: ", next_T)
    cur_x, cur_T, cur_colObj, cur_rcObj = SolveMIP(node_duals, nodes, dists, depot_dists, lambda, next_T)
    println("         Cur T: ", cur_T)
    println("         Cur rc: ", cur_rcObj)
    println("         Cur col: ", cur_colObj)
    if cur_rcObj < best_rcObj - 1e-6 && cur_colObj > 0
      best_x = cur_x[1:depot,1:24,1:depot,1:24]
      best_T = cur_T
      best_colObj = cur_colObj
      best_rcObj = cur_rcObj
    end
    if abs(next_T-cur_T)/next_T <= 0.05
      println("         Difference between next_T and cur_T below 5% ", abs(next_T-cur_T)/next_T)
      break
    end
    next_T = 0.5*next_T + 0.5*cur_T
    #blah = readline(STDIN)
  end

  if best_rcObj < -1e-6
    # New route!
    println("  SUB: Found route")
    visits = zeros(num_nodes, 24)
    for i = 1:depot
      for t_i = 1:24
        for j = 1:num_nodes
          for t_j = 1:24
            if best_x[i,t_i,j,t_j] >= 1-1e-6
              visits[j,t_j] = 1
            end
          end
        end
      end
    end
    return Route(best_colObj, visits, 0.0)
  else
    # no new route
    println("  SUB: Didn't find route")
    return nothing
  end
end

