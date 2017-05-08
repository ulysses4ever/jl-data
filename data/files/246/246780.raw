function gradientDescent(obj, x0, maxIter=10000, ϵ=1e-10)
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
  end
  println(i)
  println("WHEEEEEEEEEEEEEEE")
  err = norm(gradf,2);
  return (minn, path, err)
end

