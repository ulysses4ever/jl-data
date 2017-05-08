using NewtonISMP
using Base.Test
using CUTEst

problem = convert(ASCIIString, ARGS[1])
nlp = CUTEstModel(problem)
x0 = nlp.meta.x0

f(x) = obj(nlp, x)
g(x) = objgrad(nlp, x, true)[2]
H(x) = hess(nlp, x)

(exitflag, x, fx, gx, k) = NewtonISMP.solve(f, g, H, x0)

println("exitflag = ", exitflag)
if length(x) < 5
  println("x = ", x)
end
println("fx = ", fx)
println("|gx| = ", norm(gx))
println("k = ", k)

cutest_finalize(nlp)
