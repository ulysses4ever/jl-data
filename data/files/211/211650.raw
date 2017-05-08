
function EulerStep(f, x, u, h)
  return x + (f(x, u)*h)'
end

function MidpointStep(f, x, u_1, u_2, h)
  k1 = f(x, u_1)'
  return x + (h*f(x + (h/2.0)*k1, (u_1 + u_2)/2))'
end

function ImprovedEulerStep(f, x, u_1, u_2, h)
  k1 = f(x, u_1)'
  k2 = f(x + h*k1, u_2)'
  return x + h*(k1 + k2)/2.0
end

# Propagates gradients through Euler Integration
function GetGradients(x_dot_func, x_grad_func, u_grad_func, x_i, u, times)
  N = length(times)

  x_dim = length(x_i)
  u_dim = length(u[1, :])
  states = zeros(N, x_dim)
  states[1, :] = x_i

  # Gradients of each x[n] wrt inputs (u[1:N])
  xn_grad_u = zeros(x_dim, u_dim, N, N)

  for n = 1:N-1
    # Simulate forwards
    h = times[n+1] - times[n]
    states[n+1, :] = EulerStep(x_dot_func, states[n, :], u[n, :], h)

    # For each of the inputs that affected the trajectory to this point
    # find the gradients
    for i = 1:n+1
      # When i is n, the gradient is just the first order U dependence:
      if i==n
        xn_grad_u[:, :, n+1, i] = u_grad_func(states[n, :],u[n, :])*h
      else
        prev_grad = xn_grad_u[:, :, n, i] # Take the gradient from the previous time-step
        xn_grad_u[:, :, n+1, i] = (eye(x_dim, x_dim) + x_grad_func(states[n, :], u[n, :])*h)*prev_grad
      end
    end
  end
  return states, xn_grad_u
end

# Propagates gradients through Improved Euler Integration
function GetGradientsImproved(x_dot_func, x_grad_func, u_grad_func, x_i, u, times)
  N = length(times)

  x_dim = length(x_i)
  u_dim = length(u[1, :])
  states = zeros(N, x_dim)
  states[1, :] = x_i

  # Gradients of each x[n] wrt inputs (u[1:N])
  xn_grad_u = zeros(x_dim, u_dim, N, N)

  for n = 1:N-1
    # Simulate forwards
    h = times[n+1] - times[n]
    states[n+1, :] = ImprovedEulerStep(x_dot_func, states[n, :], u[n, :], u[n+1, :], h)

    for i = 1:n+1
      # Gradients from a previous iteration
      dxn_dui = xn_grad_u[:, :, n, i]
      dxn_dun = xn_grad_u[:, :, n, n]
      dxn_dun1 = xn_grad_u[:, :, n, n+1]

      x_n = states[n, :]'
      u_n = u[n, :]'
      u_n1 = u[n+1, :]'

      f_xu = x_dot_func(x_n', u_n')
      #println("$f_xu, $x_n")
      a = x_grad_func(x_n, u_n)
      b = x_grad_func(x_n + h * f_xu, u_n1)
      c = u_grad_func(x_n, u_n)

      df_dxn = eye(x_dim, x_dim) + h/2.0*(a + b*(eye(x_dim, x_dim) + h*a))

      final = df_dxn*dxn_dui

      if i==n
        df_dun = dxn_dun + h/2.0*(c + b*(dxn_dun + h * c))
        final = final + df_dun
      elseif i==n+1
        d = u_grad_func(x_n + h * f_xu, u_n1)
        df_dun1 = dxn_dun1 + h/2.0*(a*dxn_dun1 + d)
        final = final + df_dun1
      end
      xn_grad_u[:, :, n+1, i] = final
    end
  end
  return states, xn_grad_u
end

function IntegrateEuler(f, x_i, u, times)
  N = length(times)
  states = zeros(N, length(x_i))
  states[1, :] = x_i
  for n = 2:N
    states[n, :] = EulerStep(f, states[n-1, :], u[n-1, :], times[n] - times[n-1])
  end
  return states
end

function IntegrateMidpoint(f, x_i, u, times)
  N = length(times)
  states = zeros(N, length(x_i))
  states[1, :] = x_i
  for n = 2:N
    states[n, :] = MidpointStep(f, states[n-1, :], u[n-1, :], u[n, :], times[n] - times[n-1])
  end
  return states
end

function IntegrateImprovedEuler(f, x_i, u, times)
  N = length(times)
  states = zeros(N, length(x_i))
  states[1, :] = x_i
  for n = 2:N
    states[n, :] = ImprovedEulerStep(f, states[n-1, :], u[n-1, :], u[n, :], times[n] - times[n-1])
  end
  return states
end

