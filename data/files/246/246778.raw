include("gradientDescent.jl")
function newtMin(obj, x0, maxIter=10,ϵ=1e-16,BFGS=0)
  # Minimize a function f using Newton's method.
  # obj: a function that evaluates the objective value,
  # gradient, and Hessian at a point x, i.e.,
  # (f, g, H) = obj(x)
  # x0: starting point. Should be a column vector
  # maxIts (optional): maximum number of iterations.
  # optTol (optional): optimality tolerance based on
  #@              ‖grad(x)‖ ≦ optTol*‖grad(x0)‖
  # Get a better estimate of the initial value using Gradient Descent
  #(minn, path, err) = gradientDescent(obj, x0, 100)
  #x0 = path[:,end]
  n =size(x0)[1]
  x = x0
  # record of all points visited
  path = x0
  Δx= ones(n)
  i=0
  err=[Inf]
  minn=Inf
  B=[]
  if BFGS!=0
    lastValues = []
  end
  while (norm(Δx,2)>=ϵ) & (i<=maxIter)
    (f, ▽, H) = obj(x)
    if BFGS!=0
      if i==0
        (D, V) = eig(H)
        B = V*diagm(max(abs(D),.000000001))*V'
        Δx = B\▽
        lastH = B^(-1)
      else
        s = lastValues[1]
        y = ▽ - lastValues[2]
        ρ = 1/((y'*s)[1])
        Hach = lastH - H*y*y'*H/((y'*H*y)[1]) + s*s'/ρ
        Δx = (lastH)*▽
        lastH = Hach
      end
    else
      try
        H = chol(H)
        (D, V) = eig(H)
        println("cholesky works, apparently, but round=",i," Eigenvalues: ", D)
        B = H
        #B = V*diagm(max(abs(D),1))*V'
      catch
        (D, V) = eig(H)
        #maxeig = maximum(-D)
        #B = V*diagm(D+maxeig+.001)*V'
        #B = V*diagm(max(abs(D).^2,1))*V'
        #B = V*diagm(max(D,.000000001))*V'
        B = V*diagm(max(abs(D),.000000001))*V'
        println("round:", i," Eigenvalues:", D)
      end
      Δx = B\▽ # calculate the change in x
    end
    # check if we can stop (i.e., the error due to our second order approximation is smaller than our error tolerance)
    decrement = -▽'*Δx
    err = hcat(err,norm(decrement,2))
    minn = f
    if norm(decrement, 2)/2 < ϵ
      minn = f
      break
    end

    # Do a inexact linesearch with Wolfe condtions to find the appropriate α
    α = 1
    c = .000000001
    η = .01
    β= .5
    if BFGS==1
      k=0.0
      αlow = 0
      αtemp = 1
      a = obj(x-α*Δx)[2]'*Δx
      b = decrement
      println("a: ", a)
      println("b: ", b)
      while ((abs(a[1]) > η.*abs(b[1])) | (1.0*obj(x-α*Δx)[1]>(f+c.*αtemp.*▽'*Δx)[1]))
        if αtemp>1
          α=1
          println("WE BROKE IT")
          break
        end
        println(αtemp)
        if a[1] < 0 & (1.0*obj(x-α*Δx)[1]>(f+c.*αtemp.*▽'*Δx)[1])
          αlow = αtemp
          αtemp = sqrt(αtemp)
        else
          α = αtemp
          αtemp *= β
        end
        a = obj(x-αtemp*Δx)[2]'*Δx
        k+=1
      end
    else
      # Do a backtracking line search to find an appropriate \alpha to scale by
      while obj(x-α*Δx)[1]>(f+c.*α.*▽'*Δx)[1]
        α*=β
      end
      x = x - α*Δx
      i+=1
      if BFGS!=0
        lastDelta = α*Δx
      end
    end
    println("alpha: ", α)
    x = x - α*Δx
    i+=1
    path = hcat(path, x)
    if BFGS!=0
      lastValues = [α.*x,▽]
    end
  end
  return (i, minn, path, err)
end

