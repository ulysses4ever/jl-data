function newtmin(obj, x0, maxIter=100000,ϵ=1e-10)
  # Minimize a function f using Newton's method.
  # obj: a function that evaluates the objective value,
  # gradient, and Hessian at a point x, i.e.,
  # (f, g, H) = obj(x)
  # x0: starting point.
  # maxIts (optional): maximum number of iterations.
  # optTol (optional): optimality tolerance based on
  #@              ‖grad(x)‖ ≦ optTol*‖grad(x0)‖
  x = x0
  i=0
  while (norm(x)>=ϵ) & (i<=maxIter)
    (f, g, H) = obj(x);
    Δx = H\g # calculate the change in x
    # check if we can stop (i.e., the error due to our second order approximation is smaller than our error tolerance)
    decrement = g'*Δx;
    if norm(decrement,2) < ϵ
      break;
    end
    x = x - Δx;
    i+=1;
  end
  return (x, i)
end

