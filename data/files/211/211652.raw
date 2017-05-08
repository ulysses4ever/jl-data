using Winston
using NLopt
include("integration_gradients.jl")

# Pendulum system dynamics for [theta; theta']
function XDot(x, u)
  return [x[2]; -sin(x[1]) + u]
end

function XDotGradX(x, u)
  return [0 1; -cos(x[1]) 0]
end

function XDotGradU(x, u)
  return [0; 1]
end

# Integration tests
function PlotPend(states, times, u)
  xlabel("Time")
  oplot(times, states[:,1], "g", times, states[:,2], "b", times, u, "r");
end

function PlotControl(u, times)
  oplot(times, u, "r");
end

function TestPend()
  x_i = [pi/2 0.0]
  t_i = 0.0
  t_f = 7.0
  h = .001
  times = [t_i:h:t_f]
  u = zeros(length(times), 1)
  trajectory = IntegrateImprovedEuler(XDot, x_i, u, times)
  PlotPend(trajectory, times, u)
end

# Cost function for one particular cannon optimization scenario
opt_x_i = [pi/10, 0.0]
opt_t_i = 0.0
opt_t_f = 4.0
opt_h = .005
opt_times = [opt_t_i:opt_h:opt_t_f]
opt_n = length(opt_times)
opt_count = 0

opt_energy = [0.0:1.0:2000.0]*0
function PlotEnergy()
  nbig = 0
  for i = 2000:1
    if opt_energy != 0
      nbig = 2000 - i
      break
    end
  end
  plot(1:nbig, opt_energy(1:nbig))
end

function OptimizePend()
  plot()
  power= .01
  u_i = zeros(opt_n)

  # Optimal bang bang for uncontrolled trajectory
  #=
  states_i = IntegrateImprovedEuler(XDot, opt_x_i, u_i, opt_times)
  for n = 1:length(opt_times)
    if (states_i[n, 2] > 0)
      u_i[n] = -power
    else
      u_i[n] = power
    end
  end
  =#

  #opt = Opt(:LN_COBYLA, opt_n)
  opt = Opt(:LD_MMA, opt_n)
  lower_bounds!(opt, -power*ones(opt_n))
  upper_bounds!(opt, power*ones(opt_n))
  xtol_rel!(opt,1e-8)
  stopval!(opt, 1e-4)
  min_objective!(opt, Cost)

  #inequality_constraint!(opt::Opt, GroundConstraint)

  (minf,minx,ret) = optimize(opt, u_i)
  println("got $minf after $opt_count iterations (returned $ret)")

  states = IntegrateImprovedEuler(XDot, opt_x_i, minx, opt_times)
  println(states[end, :])
  println(GetEnergy(states[end, :]))
  PlotPend(states, opt_times, minx)
  #PlotEnergy()
end

# Trajectory and gradients cached for use between constraints:
cache_key = zeros(opt_n) # inputs are the keys
state_dim = 2
control_dim = 1
state_cache = zeros(opt_n, state_dim)
xn_grad_u_cache = zeros(state_dim, control_dim, opt_n, opt_n)

function Cost(u, grad)
  if length(grad) > 0
    states, xn_grad_u = GetGradients(XDot, XDotGradX, XDotGradU, opt_x_i, u, opt_times)

    for n=1:length(opt_times)
      x_grad_torque = xn_grad_u[:, :, end, n]
      angle = states[n, 1]
      ang_vel = states[n, 2]
      #energy_grad_x = [-2*sin(angle)*( -.5*ang_vel^2 + cos(angle) + 1), -2*ang_vel*( -.5*ang_vel^2 + cos(angle) + 1)]'
      energy_grad_x = [2*sin(angle)*( .5*ang_vel^2 - cos(angle) + 1), 2*ang_vel*( .5*ang_vel^2 - cos(angle) + 1)]'
      #println("$energy_grad_x, $x_grad_torque")
      grad[n] = (energy_grad_x*x_grad_torque)[1]
    end
  else
    states = IntegrateEuler(XDot, opt_x_i, u, opt_times)
  end

  global opt_count, opt_energy
  opt_count::Int += 1

  ke = .5*1.0*(states[end, 2])^2
  pe = 1.0*1.0*(1 - cos(states[end, 1]))
  total_energy = ke + pe
  required_energy = 1.0
  energy_cost = (required_energy - total_energy)^2
  println("$total_energy")
  #PlotControl(u, opt_times);
  #PlotPend(states, opt_times, u)
  opt_energy[opt_count] = total_energy
  return total_energy
end

function GetEnergy(state)
  ke = .5*1.0*(state[2])^2
  pe = 1.0*1.0*(1 - cos(state[1]))
  total_energy = ke + pe
  return total_energy
end
