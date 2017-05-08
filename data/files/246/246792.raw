include("newtMin.jl")
function simpleProblem(x)
  # evaluate the function f(x)=‖x-y_0‖^4, the gradient 2x, and the Hessian 2*Id
  y0 = [-1 100 3]';
  f = norm(x-y0, 2)^4;
  g = 4*norm(x-y0, 2)^2*(x-y0);
  H = 8*(x-y0)*(x-y0)'
  return (f, g, H);
end

out = newtmin(simpleProblem, [-5 136 157]')
norm(out[1]-[-1,100,3]',2)


w=[1 2 3]'

w*w'

x =[-20 125 13]'
i=0
maxIter=100000
ϵ=1e-10
println("ARGLEBLARGLEBARG")
while (norm(x)>=ϵ) & (i<=maxIter)
    (f, g, H) = simpleProblem(x);
    println(i)
    println(H)
    Δx = H\g # calculate the change in x
    # check if we can stop (i.e., the error due to our second order approximation is smaller than our error tolerance)
    decrement = g'*Δx
    if norm(decrement, 2)/2 < ϵ
      break;
    end
    x = x - Δx;
    i+=1;
  end

