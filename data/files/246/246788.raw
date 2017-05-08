function newtmin(obj, x0, maxIter=1000,ϵ=1e-10)
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
    decrement = g'*Δx
    if decrement/2 < ϵ
      break;
    end
    x = x - Δx;
    i+=1;
  end
  return (x, i)
end

function simpleProblem(x)
  # evaluate the function f(x)=‖x-y_0‖^4, the gradient 2x, and the Hessian 2*Id
  y0 = [-1 100 3];
  f = norm(x-y0, 2)^4;
  g = 4*norm(x-y0, 2)^2*(x-y0);
  H = 8*(x-y0)*(x-y0)';
  return (f, g, H);
end
