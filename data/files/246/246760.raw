using Toms566
using PyPlot

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
    path = hcat(path, path[:,i]-α*gradf);
    i+=1;
    err = hcat(err, norm(gradf,2));
  end
  return (minn, path, err)
end

function newtMin(obj, x0, maxIter=1000,ϵ=1e-16,BFGS=0)
  # Minimize a function f using Newton's method.
  # obj: a function that evaluates the objective value,
  # gradient, and Hessian at a point x, i.e.,
  # (f, g, H) = obj(x)
  # x0: starting point. Should be a column vector
  # maxIts (optional): maximum number of iterations.
  # optTol (optional): optimality tolerance based on
  #@              ‖grad(x)‖ ≦ optTol*‖grad(x0)‖
  # Get a better estimate of the initial value using Gradient Descent
  (minn, path, err) = gradientDescent(obj, x0, 100)
  x0 = path[:,end]
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
  minn=Inf
  B=[]
  while (norm(Δx,2)>=ϵ) & (i<=maxIter)
        (f, ▽, H) = obj(x)
        try
            H = chol(H)
            (D, V) = eig(H)
            #println("cholesky works, apparently, but round=",i," Eigenvalues: ", D)
            B = H
            #B = V*diagm(max(abs(D),1))*V'
        catch
            (D, V) = eig(H)
            #maxeig = maximum(-D)
            #B = V*diagm(D+maxeig+.001)*V'
            #B = V*diagm(max(abs(D).^2,1))*V'
            #B = V*diagm(max(D,.000000001))*V'
            B = V*diagm(max(abs(D),.000000001))*V'
            #println("round:", i," Eigenvalues:", D)
        end
    Δx = B\▽ # calculate the change in x
    # check if we can stop (i.e., the error due to our second order approximation is smaller than our error tolerance)
    decrement = ▽*Δx'
    #println(decrement, " WORDS ", ▽, " NERDS ", Δx)
    err = hcat(err,norm(decrement,2))
    minn = f
    if norm(decrement, 2)/2 < ϵ
      minn = f
      break
    end
    # Do a inexact linesearch to find the appropriate α
    α = 1
    αlow = 0
    frac = .0000001
    β= .75
    while obj(x-α*Δx)[1]>(f+frac.*α.*▽'*Δx)[1]
      α*=β
    end
    x = x - α*Δx
    i+=1
    path = hcat(path, x)
    #if i==round(maxIter/4)
    #    (minn, path, err) = gradientDescent(obj, x, 100)
    #    x = path[:,end]
    #end
  end
  return (i, minn, path, err)
end
t=[]
for i=1:18
    p = Problem(i)
    x0 = p.x0;
    (ii, minn, path, err) = newtMin(x->(p.obj(x),p.grd(x),p.hes(x)),x0);
    t2 = vcat(t,[minn, ii, err[end]]'')
end

A^-1
e
x=[1]
x = hcat(x, 2*x[end]-e*x[end]^2)

y=[.3]

y = hcat(y, 2*y[end]-e*y[end]^2)

