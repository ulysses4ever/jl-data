include("problemStatements.jl")
include("NewtonMeth.jl")

# Iterative Augmented Lagrangian Method
# L(x,y,rho) = f(x) - y'*c(x) + (rho/2)*c(x)'*c(x)
function augLag(LagOracle,fcnOracle,constraintOracle,conSize,x0,maxIts)
  y= ones(conSize)
  ρ = 1
  L(x) = LagOracle(x,y,ρ)
  f = fcnOracle
  c = constraintOracle
  x = x0
  k = 1
  η = 1/k
  ρ = 1e-2
  cTol = 1e-2
  gTol = 1e-2           # newtmin(obj, x0, maxIts, optTol, warmUp, whileSwitch, randPerts,newtVers)
  (x, its, fvals, gNormVals) = newtmin(L, x, 1000, 1e-3, 1, 1, 0, 2)
  println("found initial x")
  y = -ρ*c(x)[1]

  while ( (norm(c(x)[1]) > cTol) || (norm(f(x)[2] - c(x)[2]*y) > gTol) ) && (k < maxIts)
    if (norm(c(x)[1]) < η)
      y = y - ρ*c(x)[1]
    else
      ρ = 10*ρ
      L(x) = LagOracle(x,y,ρ)
    end
    (x, its, fvals, gNormVals) = newtmin(L, x, 1000, 1e-3, 10, 1, 0, 2)
    k = k + 1
    η = 1/k
    println("passed iteration ",k," with x =",x,", c(x) = ",c(x)[1])
  end
  return (x, k)
end

(xstar,k) = augLag(diff_L6abb, diff_f6, diff_c6, 1, x6_0, 100)
(xstar,k) = augLag(diff_L7abb, diff_f7, diff_c7, 1, x7_0, 100)
(xstar,k) = augLag(diff_L8abb, diff_f8, diff_c8, 2, x8_0, 100)
(xstar,k) = augLag(diff_L9abb, diff_f9, diff_c9, x9_0, 1, 100)

