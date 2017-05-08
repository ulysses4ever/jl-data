include("newtMin.jl")
function simpleProblem(x)
  # evaluate the function f(x)=‖x-y_0‖^4, the gradient 2x, and the Hessian 2*Id
  y0 = [-1 100 3]'
  f = norm(x-y0, 2)^4
  g = 4*norm(x-y0, 2)^2*(x-y0)
  H = 8*(x-y0)*(x-y0)'
  return (f, g, H)
end

function simplestProblem(x)
  # evaluate the function f(x)=‖x-y_0‖^2, the gradient 2x, and the Hessian 2*Id
  y0 = [-1 100 3]';
  f = norm(x-y0, 2)^2;
  g = 2(x-y0);
  H = 2eye(3)
  return (f, g, H);
end
include("newtMin.jl"); out = newtMin(simplestProblem, [-34 129 128]',10,1e-16,0)
norm(out[1]-[-1,100,3]',2)
y0 = [-1 100 3]'
f = norm([-5, 136, 157]-y0, 2)^4

prob = [128 -1152 -4928
 -1152 10368 44352
 -4928 44352 189728]
factorize(prob)
det(prob)
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

=======
newtmin(simpleProblem, [-1,136, 161])
>>>>>>> parent of 72c1a48... Small issue



chol()
A = [200.0 -1591.5494309189535 0.0
 -1591.5494309189535 506.60591821168896 318.3098861837907
 0.0 318.3098861837907 202.0]
F = svdfact(A)

F[:U]

F[:S]
F[:V]
F[:Vt]

F[:U]*diagm(F[:S])*F[:Vt]
chol(A)
(D,V) =eig(A)

D

V

(D, V) = eig(A)
V*diagm(D)*V'
V*diagm(abs(D))*V'

factorize
max(D,.0001)

max(abs(D),.0001)

