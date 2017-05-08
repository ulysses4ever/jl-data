using JuMP
using Gurobi

function solve_route(n,d,r,S,l,D,lambda,T,first=false)

  m = Model(:Min, mipsolver=GurobiSolver(MIPGap=0.20))

  @defVar(m, x[i=1:n, j=1:n], Bin)
  @defVar(m, a[i=1:n] >= l[i])
  @defVar(m, trueT >= 0)

  objCoef = lambda*r + (1-lambda)*repmat((T-l)',n,1)
  if first
    objCoef = 1*r
  end

  @setObjective(m, sum{objCoef[i,j]*x[i,j], i=1:n, j=1:n} + 1e-6*trueT)

  for k = 1:n
    @addConstraint(m, sum{x[i,k], i=1:n} == sum{x[k,j], j=1:n})
    @addConstraint(m, x[k,k] == 0)
    @addConstraint(m, sum{x[k,i], i=1:n} <= 1)
  end

  @addConstraint(m, sum{x[1,k], k=1:n} == 1)  # Leave depot
  @addConstraint(m, sum{x[k,1], k=1:n} == 1)  # Return to depot

  # Time windows
  const BIGM = 100.0
  for i = 1:n
    @addConstraint(m, trueT >= a[i] + d[i,1]*S - BIGM*(1-x[i,1]))
    for j = 2:n
      @addConstraint(m, a[j] >= a[i] + d[i,j]*S - BIGM*(1-x[i,j]))
    end
  end

  solve(m)

  trueObj = 0.0
  trueT = getValue(trueT)
  trueObjCoeff = lambda*r + (1-lambda)*repmat((trueT-l)',n,1)
  for i = 1:n
    for j = 1:n
      trueObj += trueObjCoeff[i,j]*getValue(x[i,j])
    end
  end

  return getValue(x), trueObj, trueT
end



function framework(n, lambda)

  # Scatter nodes on unit square
  xy = rand(n,2)

  # Calculate pairwise distances
  d = zeros(n,n)
  for i = 1:n
    for j = 1:n
      d[i,j] = norm(xy[i]-xy[j])
    end
  end
  println("d=", round(d,2))

  # Reduced costs
  r = d[:,:]
  for j = 1:n
    if rand() < 0.5
      r[:,j] -= rand(1:3)
    end
  end
  println("r=", round(r,2))

  # Speeds
  S = 1.0

  # Arrival times
  l = [(i-1)*0.7 for i = 1:n]
  println("l=", l)

  # Demand
  D = rand(1:5, n)
  println("D=",D)

  # Initial solve uses lambda 1 (no time penalty)
  println("Guess T: ", maximum(d)*(n+1)*S)
  x, z, trueT = solve_route(n,d,r,S,l,D,lambda,maximum(d)*(n+1)*S)
  println("Initial z: ", z)
  println("Initial T: ", trueT)
  best_x = x[:,:]
  best_z = copy(z)
  best_T = trueT
  next_T = trueT
  for i = 1:10
    println("Iter $i")
    cur_x, cur_z, cur_T = solve_route(n,d,r,S,l,D,lambda,next_T)
    println("Solved")
    println("z: ", cur_z)
    println("T: ", cur_T)
    if cur_z < best_z
      best_x = cur_x[:,:]
      best_z = cur_z
      best_T = cur_T
    end
    if abs(next_T - cur_T)/next_T <= 0.05
      println("Early done")
      break
    end
    next_T = 0.5*next_T + 0.5*cur_T
    println("next_T: ", next_T)
  end
  println("Best z: ", best_z)
  println("Best T: ", best_T)
  #println(best_x)
end

srand(2)
framework(100, 0.9)
