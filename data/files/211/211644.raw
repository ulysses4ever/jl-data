using Winston
using NLopt
include("double_integrator.jl")


# Integration tests
function PlotDI(states, times)
  plot(times, states[:,1]);
end

function TestDI()
  x_i = [4.0 .05]
  t_i = 0.0
  t_f = 1.0
  h = .01
  times = [t_i:h:t_f]
  u = zeros(length(times), 1)
  u[int(length(times)/2)] = 5000.0
  trajectory = IntegrateImprovedEuler(XDot, x_i, u, times)
  PlotDI(trajectory, times)
end

# Cost function for one particular cannon optimization scenario
opt_x_i = [4.0, 0.0]
opt_t_i = 0.0
opt_t_f = 1.0
opt_h = .05
opt_times = [opt_t_i:opt_h:opt_t_f]
opt_n = length(opt_times)
opt_count = 0

function OptimizeDI()
  opt = Opt(:LN_COBYLA, opt_n)
  lower_bounds!(opt, -100.0*ones(opt_n))
  upper_bounds!(opt, 100.0*ones(opt_n))
  xtol_rel!(opt,1e-6)
  min_objective!(opt, Cost)

  #inequality_constraint!(opt::Opt, GroundConstraint)

  (minf,minx,ret) = optimize(opt, 0*ones(opt_n))
  println("got $minf at $minx after $opt_count iterations (returned $ret)")

  states = IntegrateEuler(XDot, opt_x_i, minx, opt_times)
  PlotDI(states, opt_times)
end

# Trajectory and gradients cached for use between constraints:
cache_key = zeros(opt_n) # inputs are the keys
state_dim = 2
control_dim = 1
state_cache = zeros(opt_n, state_dim)
xn_grad_u_cache = zeros(state_dim, control_dim, opt_n, opt_n)

function Cost(u, grad)
  states = IntegrateEuler(XDot, opt_x_i, u, opt_times)

  global opt_count
  opt_count::Int += 1
  dist = states[end, 1]^2
  vel = states[end, 2]^2
  cost = dist + vel
  println("f_$opt_count: $cost")
  return cost
end
