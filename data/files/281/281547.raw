module helloworld

include("utility1.jl")   # Husband's utility
include("utility2.jl")   # Wife's utility
include("mUtil1_c1.jl")  # Husband's marginal utility wrt c1
include("mUtil1_q.jl")   # Husband's marginal utility wrt q
include("mUtil2_c2.jl")  # Wife's marginal utility wrt c2
include("mUtil2_q.jl")   # Wife's marginal utility wrt q


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
using NLopt
alexTheloudis = Opt(:LD_SLSQP, 3)  # :LN_COBYLA     :LD_SLSQP
ftol_rel!(alexTheloudis,1e-10)
lower_bounds!(alexTheloudis,[0.001 ; 0.001 ; 0.001])
upper_bounds!(alexTheloudis,[Inf   ; Inf   ; Inf ])

# Now I will carry out 3 rounds of optimisation,
# each with different levels of household resources:
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
  @time (fval,x_optimal,return_flag) = optimize(alexTheloudis,[resources/3;resources/3;resources/3])

  println("I got fval=",fval," at ",x_optimal)
  println("")
end #ixr

end #helloworld
