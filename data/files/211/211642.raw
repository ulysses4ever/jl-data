using Winston
using NLopt
include("integration_gradients.jl")

# Dynamics
GradX = [0 0 1 0;
         0 0 0 1;
         0 0 0 0;
         0 0 0 0]

GradU = [0 0;
         0 0;
         1 0;
         0 1]

grav = -10.0
GradT = [0;
         0;
         0;
         grav]

function XDot(x, u)
  final = GradX*x' + GradU*u' + GradT
  return final
end

function XDotGradX(x, u)
  return GradX
end

function XDotGradU(x, u)
  return GradU
end

# Integration tests
function PlotCannon(states, times)
  plot(states[:,1], states[:, 2]);
  xlabel("X")
  ylabel("Y")
end

# Basic with no input
function TestCannon()
  x_i = [0, 0, 50.0, 50.0]
  t_i = 0.0
  t_f = 10.0
  h = .01
  times = [t_i:h:t_f]
  u = zeros(length(times), 2)
  trajectory = IntegrateEuler(XDot, x_i, u, times)
  PlotCannon(trajectory, times)
end

# One impulse in the middle of the time
function TestCannonImpulse()
  x_i = [0.0, 0.0, 0.0, 0.0]
  t_i = 0.0
  t_f = 10.0
  h = .01
  times = [opt_t_i:opt_h:opt_t_f]
  impulse_power = 50.0

  # Add one impulse
  #test_angles =[0.410699926520366,0.5097664680730979,0.6317889251707456]
  test_angles =[pi/4, pi/4, pi/4]
  u, _ = GetImpulseTrain(test_angles, times, impulse_power)

  trajectory = IntegrateEuler(XDot, x_i, u, times)
  PlotCannon(trajectory, times)
end

function GetImpulseTrain(angles, times, power)
  N = length(times)
  u = zeros(N, 2)
  impulse_times = int(linspace(1, N+1, length(angles) + 1)[1:end-1])
  for n=1:length(impulse_times)
    time_step = impulse_times[n]
    dt = times[time_step + 1] - times[time_step]
    u[time_step, :] = [power/dt*cos(angles[n]), power/dt*sin(angles[n])]
  end
  return u, impulse_times
end


# Cost function for one particular cannon optimization scenario
opt_x_i = [0.0, 0.0, 0.0, 0.0]
opt_t_i = 0.0
opt_t_f = 10.0
opt_h = .01
opt_impulse_power = 50.0
opt_times = [opt_t_i:opt_h:opt_t_f]
opt_count = 0
opt_num_impulses = 30
opt_out = [0.0:1.0:300.0]*0.0

function OptimizeImpulses()
  num_impulses = opt_num_impulses
  opt = Opt(:LN_COBYLA, num_impulses)
  lower_bounds!(opt, -pi/2*ones(num_impulses))
  upper_bounds!(opt, pi/2*ones(num_impulses))
  xtol_rel!(opt,1e-6)
  max_objective!(opt, Cost)

  inequality_constraint!(opt::Opt, GroundConstraint)

  (minf,minx,ret) = optimize(opt, ones(num_impulses))
  println("got $minf at $minx after $opt_count iterations (returned $ret)")

  u, _ = GetImpulseTrain(minx, opt_times, opt_impulse_power)
  states = IntegrateEuler(XDot, opt_x_i, u, opt_times)
  plot(states[:,1], states[:,2] );
end

function OptimizeImpulseWithGradients()
  num_impulses = opt_num_impulses
  opt = Opt(:LD_MMA, num_impulses)
  lower_bounds!(opt, -pi/2*ones(num_impulses))
  upper_bounds!(opt, pi/2*ones(num_impulses))
  xtol_rel!(opt,1e-6)
  max_objective!(opt, Cost)

  inequality_constraint!(opt::Opt, GroundConstraint)
  start = ones(num_impulses)

  (minf,minx,ret) = optimize(opt, start)
  println("got $minf at $minx after $opt_count iterations (returned $ret)")

  u, _ = GetImpulseTrain(minx, opt_times, opt_impulse_power)
  states = IntegrateEuler(XDot, opt_x_i, u, opt_times)
  plot(states[:,1], states[:,2] );
end

# Trajectory and gradients cached for use between constraints:
opt_n = length(opt_times)
cache_key = zeros(opt_num_impulses) # inputs are the keys
state_dim = 4
control_dim = 2
state_cache = zeros(opt_n, state_dim)
xn_grad_u_cache = zeros(state_dim, control_dim, opt_n, opt_n)

cost_grad_x = [1.0 0.0 0.0 0.0]''
function Cost(angles, grad)
  u, impulse_times = GetImpulseTrain(angles, opt_times, opt_impulse_power)
  if length(grad) > 0
    global cache_key, state_cache, xn_grad_u_cache
    if cache_key == angles
      states = state_cache
      xn_grad_u = xn_grad_u_cache
    else
      states, xn_grad_u = GetGradients(XDot, XDotGradX, XDotGradU, opt_x_i, u, opt_times)
      cache_key = copy(angles)
      state_cache = states
      xn_grad_u_cache = xn_grad_u
    end

    for n=1:length(angles)
      impulse_grad_angle = [-sin(angles[n]) cos(angles[n])]'
      x_grad_impulse = xn_grad_u[:, :, end, impulse_times[n]]
      grad[n] = (cost_grad_x*x_grad_impulse*impulse_grad_angle)[1]
    end
  else
    global cache_key, state_cache
    if cache_key == angles
      states = state_cache
    else
      states = IntegrateEuler(XDot, opt_x_i, u, opt_times)
      cache_key = copy(angles)
      state_cache = states
    end
  end

  global opt_count
  opt_count::Int += 1
  distance = states[end, 1]
  #println("f_$opt_count: $angles, $distance")
  #opt_out[opt_count] = distance
  return distance
end

# Constraint function to keep cannonball above the ground
ground_constraint_grad_x = [0.0 -1.0 0.0 0.0]''
function GroundConstraint(angles, grad)
  u, impulse_times = GetImpulseTrain(angles, opt_times, opt_impulse_power)
  if length(grad) > 0
    global cache_key, state_cache, xn_grad_u_cache
    if cache_key == angles
      states = state_cache
      xn_grad_u = xn_grad_u_cache
    else
      states, xn_grad_u = GetGradients(XDot, XDotGradX, XDotGradU, opt_x_i, u, opt_times)
      cache_key = copy(angles)
      state_cache = states
      xn_grad_u_cache = xn_grad_u
    end

    for n=1:length(angles)
      impulse_grad_angle = [-sin(angles[n]) cos(angles[n])]'
      x_grad_impulse = xn_grad_u[:, :, end, impulse_times[n]]
      grad[n] = (cost_grad_x*x_grad_impulse*impulse_grad_angle)[1]
    end

  else
    global cache_key, state_cache
    if cache_key == angles
      states = state_cache
    else
      states = IntegrateEuler(XDot, opt_x_i, u, opt_times)
      cache_key = copy(angles)
      state_cache = states
    end
  end
  return -states[end, 2]
end
