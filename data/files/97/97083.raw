module CDLasso

import Base.LinAlg.BLAS
import Base.LinAlg.SVD

#######################################################################

type LassoOptions
  max_inner_iter::Int64
  max_outer_iter::Int64
  xtol::Float64
  gradtol::Float64
  zerothr::Float64
  printEvery::Int64
end

function LassoOptions(;max_inner_iter::Integer     = 200,
                      max_outer_iter::Integer      = 200,
                      xtol::Float64                = 1e-6,
                      gradtol::Float64             = 1e-6,
                      zerothr::Float64             = 1e-4,
                      printEvery::Integer          = -1
                      )
  LassoOptions(
    max_inner_iter,
    max_outer_iter,
    xtol,
    gradtol,
    zerothr,
    printEvery
    )
end

#######################################################################

include("lasso.jl")
include("glasso.jl")

####################################################################################

function _penalty_loadings!{T<:FloatingPoint}(
    γ::StridedVector{T},
    λ::StridedVector{T},
    X::StridedMatrix{T},
    res::StridedVector{T}
    )
  n, p = size(X)
  for j=1:p
    s = zero(T)
    m = zero(T)
    for i=1:n
      s += X[i, j]^2. * res[i]^2.
      m += X[i, j] * res[i]
    end
    γ[j] = sqrt(s / n - (m/n)^2.) * λ[j]
  end
end

# numIterations that estimate Gamma matrix
function feasible_lasso!{T<:FloatingPoint}(
    x::StridedVector{T},
    X::StridedMatrix{T},
    Y::StridedVector{T},
    λ::Vector{T};
    options::LassoOptions   =   LassoOptions(),
    refit::Bool             =   true,
    numIterations::Int      =   1,
    xtol::T                 =   1e-4
    )

  n, p = size(X)
  A = X'X
  scale!(A, 1./n)
  b = X'Y
  scale!(b, -1./n)

  xold = copy(x)
  γ = copy(λ)
  res = copy(Y)

  BLAS.gemv!('N', -1., X, x, 1., res)
  _penalty_loadings!(γ, λ, X, res)

  for iter=1:numIterations
    _, activeset = lasso!(x, A, b, γ)

    # check if done
    s = zero(T)
    for j=1:p
      s = max(s, abs(x[j] - xold[j]))
    end
    if s < xtol
      break
    end

    if refit
      indNZ = activeset.indexes[1:activeset.numActive]
      #       xv = sub(x, indNZ)
      #       Av = sub(A, indNZ, indNZ)
      #       bv = sub(b, indNZ)
      #       xv[:] = Av \ bv
      #       scale!(xv, -1)
      x[indNZ] = X[:, indNZ] \ Y[:]
    end

    # update γ
    if iter < numIterations
      # re-estimate gamma unless last iteration
      copy!(res, Y)
      BLAS.gemv!('N', -1., X, x, 1., res)
      _penalty_loadings!(γ, λ, X, res)

      copy!(xold, x)
    end
    #
  end
  x
end

end
