include("integration_gradients.jl")

# Double Integrator system dynamics
GradU = [0; 1]
GradX = [0 1; 0 0]

function XDot(x, u)
  return GradX*x' + GradU*u'
end

function XDotGradX(x, u)
  return GradX
end

function XDotGradU(x, u)
  return GradU
end

# Test to see how accurate the gradient propagation is with this model
function TestGradients()
  n_controls = 1
  x_i = [0.0 0.0]
  t_i = 0.0
  t_f = 100.0
  h = .1
  times = [t_i:h:t_f]
  N = length(times)
  control_var = 1
  u_a = .5412*ones(N, n_controls)
  states_a, xn_grad_u = GetGradients(XDot, XDotGradX, XDotGradU, x_i, u_a, times)


  #states_a = IntegrateEuler(XDot, x_i, u_a, times)

  diff = ones(n_controls)*.01
  u_b = copy(u_a)
  u_b[control_var, :] += diff'

  states_b = IntegrateEuler(XDot, x_i, u_b, times)
  expected = xn_grad_u[:, :, N, control_var]*diff
  
  actual = states_b[N,:] - states_a[N,:]
  error = (expected' - actual) ./ actual
  println("$error,  $actual, $expected")
end

# Testing Euler Improved gradients
function TestGradients2()
  n_controls = 1
  x_i = [0.0 0.0]
  t_i = 0.0
  t_f = 100.0
  h = .1
  times = [t_i:h:t_f]
  N = length(times)
  control_var = 1
  u_a = .5412*ones(N, n_controls)
  states_a, xn_grad_u = GetGradientsImproved(XDot, XDotGradX, XDotGradU, x_i, u_a, times)

  diff = ones(n_controls)*.01
  u_b = copy(u_a)
  u_b[control_var, :] += diff'

  states_b = IntegrateImprovedEuler(XDot, x_i, u_b, times)
  expected = xn_grad_u[:, :, N, control_var]*diff
  
  actual = states_b[N,:] - states_a[N,:]
  error = (expected' - actual) ./ actual
  println("$error,  $actual, $expected")
end
