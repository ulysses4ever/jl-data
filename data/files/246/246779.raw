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
    end
    # check if we can stop (i.e., the error due to our second order approximation is smaller than our error tolerance)
    decrement = -▽'*Δx
    err = hcat(err,norm(decrement,2))
    minn = f
    if norm(decrement,2)<ϵ
      break
    end
    # Do a inexact linesearch with Wolfe condtions to find the appropriate α
    α = 1
    c = .000000001
    η = .9
    β= .9
    if BFGS==-1
      α=1
    elseif BFGS==1
      k=0.0
      αlow = 0
      αmax = 1
      αtemp = αmax
      ψlow = f
      β=1/16
      α = αmax*β
      b = decrement
      while 1>0
        (ψα, ψp, bler) = obj(x-αmax*Δx)
        a = ψp'*Δx
        #println("a: ", a)
        #println("b: ", b)
        # if the objective function has gotten too large by moving the interval away, use the last interval
        if (ψα > (f+c.*α.*▽'*Δx)[1])
          #println("objective function is too large αlow=", αlow, " α=", α)
          α = zoom(αlow, α, obj, ▽, Δx, ψlow, a, b, η, c, x, f)
          break
        end
        if abs(a[1]) <= η.*abs(b[1]) # we satisfy both conditions!
          #println("Satisfy both conditions! α=",α)
          break
        elseif a[1]>=0 #the derivative is positive
          #println("The derivative is positive")
          α = zoom(αlow, α, obj, ▽, Δx, ψlow, a, b, η, c, x, f)
          break
        end
        αlow = α
        ψlow = ψα
        α += (αmax-α)*β # interpolation of some kind would make this more effective
      end
#       while ((abs(a[1]) > η.*abs(b[1])) | (1.0*obj(x-α*Δx)[1]>(f+c.*αtemp.*▽'*Δx)[1])) & bool(k<100)
#         if αtemp>1
#           α=1
#           println("WE BROKE IT")
#           break
#         end
#         #println(αtemp)
#         if ((a[1] < 0) & (1.0*obj(x-α*Δx)[1]<(f+c.*αtemp.*▽'*Δx)[1]))
#           #println("a is negative and somehow the objective function is ok with that")
#           #println(1.0*obj(x-α*Δx)[1], " WORDS ", (f+c.*αtemp.*▽'*Δx)[1])
#           αlow = αtemp
#           αtemp += (1-β)*(α-αlow)/2
#         else
#           α = αtemp
#           αtemp *= β
#         end
#         a = obj(x-αtemp*Δx)[2]'*Δx
#         k+=1
#       end
    else
      # Do a backtracking line search to find an appropriate \alpha to scale by
      while obj(x-α*Δx)[1]>(f+c.*α.*▽'*Δx)[1]
        α*=β
      end
    end
    #println(α)
    x = x - α*Δx
    i+=1
    path = hcat(path, x)
    if BFGS!=0
      lastValues = [α*Δx ▽]
    end
  end
  return (i, minn, path, err)
end

function zoom(αlow, α, obj, ▽, Δx, ψlow, a, b, η, c, x, f)
  for k=1:1000
  #while abs(a[1]) > η.*abs(b[1])
    αtemp = αlow + (α-αlow)/2 # interpolation would make this better
    #println(αtemp, "∈(",αlow,",",α,")")
    (ψα, ψp, bler) = obj(x-α*Δx)
    a = ψp'*Δx
    # the new point doesn't satisfy the Armijo conditions, or has a higher objective value than the αlow
    if (ψlow <= ψα) | (ψα > (f+c.*αlow.*▽'*Δx)[1])
      #println("breaks armijo")
      α = αtemp
    else
      # we've reached the tolerance
      if abs(a[1]) <= η.*abs(b[1])
        return α = αtemp
      end
      if (ψp*(α-αlow))[1] >= 0
        α = αlow
        println("Somehow we got here?")
      end
      αlow = αtemp
    end
  end
  println("TOO MANY")
  return α
end
