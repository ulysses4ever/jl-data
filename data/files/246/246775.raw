function newtMin(obj, x0, maxIter=100,ϵ=1e-10,BFGS=0)
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
  # record of all points visited
  path = x0
  Δx= ones(n)
  i=0
  err=[Inf]
  minn=0
  while (norm(Δx,2)>=ϵ) & (i<=maxIter)
    (f, ▽, H) = obj(x)
    try
    H = factorize(H)
      catch
      println(x)
      println(f)
      println(▽)
      println(H)
      error("Oh my. You seem to have chosen a singular matrix. I'll get back to you on that.")
    end
    Δx = H\▽ # calculate the change in x
    # check if we can stop (i.e., the error due to our second order approximation is smaller than our error tolerance)
    decrement = ▽'*Δx
    err = hcat(err,decrement)
    if norm(decrement, 2)/2 < ϵ
      minn = f
      break
    end
    # Do a backtracking line search to find an appropriate \alpha to scale by
    α = .5
    frac = .25
    β= .5
    while obj(x-α*Δx)[1]>(f+frac.*α.*▽'*Δx)[1]
      α*=β
    end
    x = x - α*Δx
    i+=1
    path = hcat(path, x)
  end
  return (i, minn, path, err)
end

