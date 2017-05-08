#### OBJECTIVE FUNCTION (household objective)
function objectivef(choice_var::Array{Float64,1}, grad::Array{Float64,1})

  # Declare choice variables:
  c1   = choice_var[1]     # husband's private consumption
  c2   = choice_var[2]     # wife's private consumption
  q    = choice_var[3]     # household's public consumption

  # Declare Pareto weights:
  pareto1 = 1/2
  pareto2 = 1/2

  # Calculate gradient:
  if length(grad) > 0
    grad[1] = pareto1 * mUtil1_c1(c1, q)
    grad[2] = pareto2 * mUtil2_c2(c2, q)
    grad[3] = pareto1 * mUtil1_q(c1, q) + pareto2 * mUtil2_q(c2, q)
  end

  # Calculate objective:
  objective   = pareto1 * utility1(c1, q) + pareto2 * utility2(c2, q)

end

#### CONSTRAINT (household budget constraint)
function constraint(choice_var::Array{Float64,1}, grad::Array{Float64,1}, resources::Float64)

  # Declare choice variables:
  c1   = choice_var[1]     # husband's private consumption
  c2   = choice_var[2]     # wife's private consumption
  q    = choice_var[3]     # household's public consumption

  # Calculate gradient:
  if length(grad) > 0
    grad[1] = -1
    grad[2] = -1
    grad[3] = -1
  end

  # Write (budget) constraint:
  resources - c1 - c2 - q

end

#### OPTIMIZATION

function doNLopt()
	alexTheloudis = Opt(:LD_SLSQP, 3)  # :LN_COBYLA     :LD_SLSQP
	ftol_rel!(alexTheloudis,1e-10)
	lower_bounds!(alexTheloudis,[0.001 ; 0.001 ; 0.001])
	upper_bounds!(alexTheloudis,[Inf   ; Inf   ; Inf ])

	# Now I will carry out 3 rounds of optimisation,
	# each with different levels of household resources:
  println("STARTING NLopt:")
	for ixr = 1:1:3

	  if     ixr == 1
	    resources = 10.0   # resources round 1
	  elseif ixr == 2
	    resources = 100.0  # resources round 2
	  else
	    resources = 900.0  # resources round 3
	  end #if ixr
	  println("This is round ",ixr," with total resources = ",resources)

	  max_objective!(alexTheloudis, (x,g) -> objectivef(x, g))
	  equality_constraint!(alexTheloudis, (x,g) -> constraint(x, g, resources), 1e-6)
	  (fval,x_optimal,return_flag) = optimize(alexTheloudis,[resources/3;resources/3;resources/3])

	  println("I got fval=",fval," at ",x_optimal," with exit flag ",return_flag)
	  println("-----------")
	end #ixr
end

type Param
	mu1::Float64
	mu2::Float64
	alpha::Float64
	gamma::Float64
	resources::Float64
	myNA::Float64
	n::Int
	function Param(res::Float64=10.0)
		mu1 = 0.5
		mu2 = 0.5
		alpha = 0.5
		gamma = 3/2
		myNA = -1e6
		n = 300
		return new(mu1, mu2, alpha, gamma,res,myNA,n)
	end
end

function CRRA(x::Float64,p::Param)
	(1/(1-p.gamma)) * x^(1-p.gamma)
end

function objfun(c1::Float64,c2::Float64,q::Float64,p::Param)
	x1 = p.mu1 * (p.alpha * CRRA(c1,p) + (1-p.alpha) * CRRA(q,p))
	x2 = p.mu2 * (p.alpha * CRRA(c2,p) + (1-p.alpha) * CRRA(q,p))
	#check constraint
	if c1 + c2 + q > p.resources
		return p.myNA
	else
		return x1 + x2
	end
end

function gridSearch(p::Param)
	# search at given level of resources
	c1 = linspace(0.001,p.resources,p.n)
	c2 = linspace(0.001,p.resources,p.n)
	q  = linspace(0.001,p.resources,p.n)
	# table with grid point	s
	grid = DataFrame(c1=repeat(c1,inner=[1],outer=[p.n^2]),c2=repeat(c2,inner=[p.n],outer=[p.n]),q=repeat(q,inner=[p.n^2],outer=[1]),value = zeros(p.n^3))
	x = Float64[objfun(c1[i],c2[j],q[k],p) for i in 1:p.n, j in 1:p.n, k in 1:p.n]
	grid[:value] = x[:]
	# for e in eachrow(grid)
	# 	e[:value] = objfun(e[:c1],e[:c2],e[:q],p)
	# end
	v = findmax(grid[:value])
	return (grid[v[2],:])
end

function doGridSearch()
	for res in [10.0,100,900]
		p = Param(res)
		x = gridSearch(p)
		println("results for resources = $(p.resources)")
		println(x)
	end
end

# =================================================

function gridSearch2(p::Param)
	# Generate grid for c1 given resources:
	c1 = linspace(0.001,p.resources,p.n)
  # Generate c2, q such that FOCs are satisfied conditional on c1:
	c2 = ((p.mu1/p.mu2)^(-1/p.gamma)) * c1
  q  = (((p.alpha * p.mu1) / ((1-p.alpha)*(p.mu1+p.mu2)))^(-1/p.gamma)) * c1
  # Evaluate objective:
  obj = Float64[objfun(c1[i],c2[i],q[i],p) for i in 1:p.n]
	(value, index) = findmax(obj)
	return (value, index, [c1 c2 q])
end

function doGridSearch2()
  println("STARTING GridSearch2:")
	for res in [10.0,100.0,900.0]
		p = Param(res)
		(value, index, x) = gridSearch2(p)
		println("Results for resources = $(p.resources). I found $(value) for c1 = $(x[index,1]), c2 = $(x[index,2]) and q = $(x[index,3])")
    println("-----------")
	end
end


# =================================================

function objective(c1::Float64,c2::Float64,q::Float64,p::Param)
	x1 = p.mu1 * (p.alpha * CRRA(c1,p) + (1-p.alpha) * CRRA(q,p))
	x2 = p.mu2 * (p.alpha * CRRA(c2,p) + (1-p.alpha) * CRRA(q,p))
	return x1 + x2
end

function fixedPoint(p::Param)
  c1 = (1 + (p.mu1/p.mu2)^(-1/p.gamma) + ((p.alpha * p.mu1) / ((1-p.alpha)*(p.mu1+p.mu2)))^(-1/p.gamma))^(-1)*p.resources
  c2 = (p.mu1/p.mu2)^(-1/p.gamma)*c1
  q  = ((p.alpha * p.mu1) / ((1-p.alpha)*(p.mu1+p.mu2)))^(-1/p.gamma)*c1
  value = objective(c1,c2,q,p)
  return (value,c1,c2,q)
end

function findFixedPoint()
  println("STARTING findSolution:")
	for res in [10.0,100.0,900.0]
		p = Param(res)
		(value,c1,c2,q) = fixedPoint(p)
		println("Results for resources = $(p.resources). I found $(value) for c1 = $(c1), c2 = $(c2) and q = $(q)")
    println("-----------")
	end
end
