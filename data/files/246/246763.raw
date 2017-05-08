using Toms566

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
<<<<<<< HEAD
    # Do a inexact linesearch to find the appropriate α
    α = 1
    αlow = 0
    frac = .0000001
    β= .75
=======
    # Do a backtracking line search to find an appropriate \alpha to scale by
    α = .5
    frac = .25
    β= .5
>>>>>>> parent of fa76fb8... Finish HW3
    while obj(x-α*Δx)[1]>(f+frac.*α.*▽'*Δx)[1]
      α*=β
    end
    x = x - α*Δx
    i+=1
    path = hcat(path, x)
  end
  return (i, minn, path, err)
end

function gradientDescent(obj, x0, maxIter=1000, ϵ=1e-10)
# returns (minn, path, error) where min is the minimum value, path is the set of points visited in minimizing obj,
#    and err is norm of the gradient in the last step
# obj: evaluates the function and it's gradient at any given point, returns them as (minn, gradf)
# x0: initial location; this must be a column vector at the moment
# maxIter: maximum number of iterations
# ϵ: the error tolerance
  i=1;
  α=1;
  path = x0;
  gradf=[];
  minn=[];
  err=[Inf];
  while i<=maxIter
    (minn, gradf) = obj(path[:,i]);
    # stop if the gradient is sufficiently small
    if norm(gradf,2)<=ϵ
      break;
    end
    # do line-back to find α
    α = .75
    while obj(path[:,i] - α*gradf)[1] > minn-α*.5*norm(gradf,2)
      α*=.5;
    end
    print(α)
    path = hcat(path, path[:,i]-α*gradf);
    i+=1;
    err = hcat(err, norm(gradf,2));
  end
  println(i)
  println("WHEEEEEEEEEEEEEEE")
  return (minn, path, err)
end


for i=1:18
  p = Problem(i)
  x0 = p.x0;
  (i, minn, path, err) = newtMin(x->(p.obj(x),p.grd(x),p.hes(x)),[.5 .5 .5]')
  (▽minn,▽path,▽err) = gradientDescent(x->(p.obj(x),p.grd(x)),[.5 .5 .5]')
  # Graph the path of the parameters
  plot(path[1,:]',path[2,:]',color=(1, 0,.5),label="Newton's Method")
  grad = plot(▽path[1,:]',▽path[2,:]',color=(0,0,1),label="Gradient Descent")
  legend(bbox_to_anchor=(0., 1.02, 1., .102), loc=17,ncol=1, mode="expand", borderaxespad=0.)
  title("Admissions Path")
  ylabel("GPA");
  xlabel("GRE");
  PyPlot.show()

  # Graph the size of the error
  plot(log(err[2:]),color=(1, 0,.5),label="Newton's Method")
  grad = plot(log(▽err[2:200]),color=(0,0,1),label="Gradient Descent")
  legend()
  title(string("Log error for ", "Admissions"))
  ylabel("log(error)");
  xlabel("step");
  PyPlot.show()
end

A^-1
e
x=[1]
x = hcat(x, 2*x[end]-e*x[end]^2)

y=[.3]

y = hcat(y, 2*y[end]-e*y[end]^2)

