module CDLasso

import Base.LinAlg.BLAS

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

type ActiveSet
  indexes::Vector{Int64}
  numActive::Int64
end

type GroupActiveSet{I}
  groups::Vector{Int64}
  numActive::Int64
  groupToIndex::Vector{I}
end

function ActiveSet{T<:FloatingPoint}(
    x::StridedArray{T};
    options::LassoOptions = LassoOptions()
    )
  zero_thr = options.zerothr
  numElem = length(x)
  activeset = [1:numElem;]
  numActive = 0
  for j = 1:numElem
    if abs(x[j]) >= zero_thr
      numActive += 1
      activeset[numActive], activeset[j] = activeset[j], activeset[numActive]
    end
  end
  ActiveSet(activeset, numActive)
end

function _add_violator!{T<:FloatingPoint}(
    activeset::ActiveSet,
    x::StridedVector{T},
    A::StridedMatrix{T},
    b::StridedVector{T},
    λ::StridedVector{T};
    options::LassoOptions   =   LassoOptions()
    )
  changed = false

  zerothr = options.zerothr
  numElem = length(x)
  numActive = activeset.numActive
  indexes = activeset.indexes
  # check for things to be removed from the active set
  i = 0
  @inbounds while i < numActive
    i = i + 1
    t = indexes[i]
    if abs(x[t]) < zerothr
      x[t] = zero(T)
      changed = true
      indexes[numActive], indexes[i] = indexes[i], indexes[numActive]
      numActive -= 1
      i = i - 1
    end
  end
  activeset.numActive = numActive

  I = 0
  V = zero(T)
  for i=numActive+1:numElem
    t = indexes[i]
    tmp = _Axk(A, x, t, activeset) + b[t]
    nV = abs(tmp) - λ[t]
    if V < nV
      I = i
      V = nV
    end
  end
  if I > 0 && V > options.gradtol
    changed = true
    numActive += 1
    indexes[numActive], indexes[I] = indexes[I], indexes[numActive]
  end
  activeset.numActive = numActive
  changed
end

#######################################################################

shrink{T<:FloatingPoint}(v::T, c::T) = v > c ? v - c : (v < -c ? v + c : zero(T))

#######################################################################

# computes x'A[:, j]
function _Axk{T<:FloatingPoint}(A::StridedMatrix{T}, x::StridedVector{T}, j::Int64, activeset::ActiveSet)
  s = zero(T)
  indexes = activeset.indexes
  for i=1:activeset.numActive
    ind = indexes[i]
    s += x[ind] * A[ind, j]
  end
  s
end

function _lasso!{T<:FloatingPoint}(
    x::StridedVector{T},
    A::StridedMatrix{T},
    b::StridedVector{T},
    λ::StridedVector{T},
    activeset::ActiveSet;
    options::LassoOptions   =   LassoOptions()
    )

  indexes = activeset.indexes
  iter = 0
  while true
    iter += 1
    maxUpdate = zero(T)
    for i=1:activeset.numActive
      j = indexes[i]
      a = A[j, j]
      S0 = _Axk(A, x, j, activeset) - a * x[j] + b[j]
      newValue = shrink(-S0 / a, abs(λ[j] / a))
      if abs(x[j] - newValue) > maxUpdate
        maxUpdate = abs(x[j] - newValue)
      end
      x[j] = newValue
    end
    if iter > options.max_inner_iter || maxUpdate < options.xtol
      break
    end
  end
  x
end

lasso!{T<:FloatingPoint}(
    x::StridedVector{T},
    A::StridedMatrix{T},
    b::StridedVector{T},
    λ::T;
    options::LassoOptions   =   LassoOptions()
    ) = lasso!(x, A, b, fill(λ, length(x)); options=options)

function lasso!{T<:FloatingPoint}(
    x::StridedVector{T},
    A::StridedMatrix{T},
    b::StridedVector{T},
    λ::StridedVector{T};
    options::LassoOptions   =   LassoOptions()
    )

  maxoutiter = options.max_outer_iter
  activeset = ActiveSet(x; options=options)
  if activeset.numActive == 0
    _add_violator!(activeset, x, A, b, λ; options=options)
  end

  for outiter=1:maxoutiter
    _lasso!(x, A, b, λ, activeset; options=options)
    if ~_add_violator!(activeset, x, A, b, λ; options=options)
      break
    end
  end
  x, activeset
end


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

### todo:
# groups lasso


end
