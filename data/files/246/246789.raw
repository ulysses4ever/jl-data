function newtmin(obj, x0, maxIter=1000,ϵ=1e-10,BFGS=0)
  # Minimize a function f using Newton's method.
  # obj: a function that evaluates the objective value,
  # gradient, and Hessian at a point x, i.e.,
  # (f, g, H) = obj(x)
  # x0: starting point. Should be a column vector
  # maxIts (optional): maximum number of iterations.
  # optTol (optional): optimality tolerance based on
  #@              ‖grad(x)‖ ≦ optTol*‖grad(x0)‖
  if BFGS!=0
    error("I haven't implimented this feature yet")
  end
  n =size(x0)[1]
  x = x0
  Δx= ones(n)
  i=0
  while (norm(Δx)>=ϵ) & (i<=maxIter)
    (f, ▽, H) = obj(x)
    print(H)
    try
    H = factorize(H)
      catch
      println(x)
      println(f)
      println(▽)
      println(H)
      error("Ohmy. You seem to have chosen a singular matrix")
    end
    Δx = H\▽ # calculate the change in x
    # check if we can stop (i.e., the error due to our second order approximation is smaller than our error tolerance)
    decrement = ▽'*Δx
    if norm(decrement, 2)/2 < ϵ
      break;
    end
    x = x - Δx
    i+=1
  end
  return (x, i)
end

