type ActiveSet
  indexes::Vector{Int64}
  numActive::Int64
end


function ActiveSet{T<:AbstractFloat}(
    x::StridedVector{T};
    options::LassoOptions = LassoOptions()
    )
  zero_thr = options.zerothr
  numElem = length(x)
  activeset = [1:numElem;]
  numActive = 0
  @inbounds for j = 1:numElem
    if abs(x[j]) >= zero_thr
      numActive += 1
      activeset[numActive], activeset[j] = activeset[j], activeset[numActive]
    end
  end
  ActiveSet(activeset, numActive)
end

function _add_violator!{T<:AbstractFloat}(
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
  @inbounds for i=numActive+1:numElem
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

shrink{T<:AbstractFloat}(v::T, c::T) = v > c ? v - c : (v < -c ? v + c : zero(T))

#######################################################################

# computes x'A[:, j]
function _Axk{T<:AbstractFloat}(A::StridedMatrix{T}, x::StridedVector{T}, j::Int64, activeset::ActiveSet)
  s = zero(T)
  indexes = activeset.indexes
  @inbounds for i=1:activeset.numActive
    ind = indexes[i]
    s += x[ind] * A[ind, j]
  end
  s
end


function _lasso!{T<:AbstractFloat}(
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
    @inbounds for i=1:activeset.numActive
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

lasso!{T<:AbstractFloat}(
    x::StridedVector{T},
    A::StridedMatrix{T},
    b::StridedVector{T},
    λ::T;
    options::LassoOptions   =   LassoOptions()
    ) = lasso!(x, A, b, fill(λ, length(x)); options=options)

function lasso!{T<:AbstractFloat}(
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

