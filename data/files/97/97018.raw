type GroupLassoData{T<:FloatingPoint, I}
  groups::Vector{Int64}
  numActive::Int64
  groupToIndex::Vector{I}
  xold::Vector{T}
  Asvd::Vector{Any}
  maxGroupLen::Int64
  btild::Vector{T}      # vector of max group len
  x1::Vector{T}         # vector of max group len
  Utb::Vector{T}         # vector of max group len
end


function GroupLassoData{T<:FloatingPoint, I}(
    x::StridedVector{T},
    groupToIndex::Vector{I};
    options::LassoOptions = LassoOptions()
    )
  zero_thr = options.zerothr
  numElem = length(groupToIndex)
  groups = [1:numElem;]
  numActive = 0
  maxGroupLen = 0
  for gi = 1:numElem
    group_len = length(groupToIndex[gi])
    if maxGroupLen < group_len
      maxGroupLen = group_len
    end
    if vecnorm(sub(x, groupToIndex[gi])) >= zero_thr
      numActive += 1
      groups[numActive], groups[gi] = groups[gi], groups[numActive]
    end
  end
  GroupLassoData{T, I}(groups, numActive, groupToIndex,
                       zeros(length(x)), Array(Any, numElem),
                       maxGroupLen,
                       zeros(maxGroupLen),zeros(maxGroupLen),zeros(maxGroupLen)
                       )
end

function _add_violator!{T<:FloatingPoint}(
    activeset::GroupLassoData,
    x::StridedVector{T},
    A::StridedMatrix{T},
    b::StridedVector{T},
    λ::StridedVector{T};
    options::LassoOptions   =   LassoOptions()
    )
  changed = false

  zerothr = options.zerothr
  groups = activeset.groups
  numActive = activeset.numActive
  groupToIndex = activeset.groupToIndex
  numElem = length(groups)
  # check for things to be removed from the active set
  i = 0
  @inbounds while i < numActive
    i = i + 1
    t = groups[i]
    if _group_norm(x, activeset, t) < zerothr
      _fill_zero!(x, activeset, t)
      changed = true
      groups[numActive], groups[i] = groups[i], groups[numActive]
      numActive -= 1
      i = i - 1
    end
  end
  activeset.numActive = numActive

  btild = activeset.btild
  I = 0
  V = zero(T)
  @inbounds for i=numActive+1:numElem
    t = groups[i]
    group_norm = _Axkpb!(btild, A, b, x, t, activeset)
    nV = group_norm - λ[t]
    if V < nV
      I = i
      V = nV
    end
  end
  if I > 0 && V > options.gradtol
    gi = groups[I]
    if ~isdefined(activeset.Asvd, gi)
      activeset.Asvd[gi] = svdfact(sub(A, groupToIndex[gi], groupToIndex[gi]))
    end
    changed = true
    numActive += 1
    groups[numActive], groups[I] = groups[I], groups[numActive]
  end
  activeset.numActive = numActive
  changed
end

function _group_norm{T<:FloatingPoint}(
    x::StridedVector{T},
    activeset::GroupLassoData{T},
    j::Int64
    )
  r = zero(T)
  @inbounds for i in activeset.groupToIndex[j]
    r += x[i]^2.
  end
  sqrt(r)
end

function _fill_zero!{T<:FloatingPoint, I}(
    x::StridedVector{T},
    activeset::GroupLassoData{T, I},
    j::Int64
    )
  @inbounds for i in activeset.groupToIndex[j]
    x[i] = zero(T)
  end
  x
end

# computes x[-gj]'A[-gj, gj] + b[gj]'
# returns norm of res
function _Axkpb!{T<:FloatingPoint}(
    res::StridedVector{T},
    A::StridedMatrix{T},
    b::StridedVector{T},
    x::StridedVector{T},
    j::Int64,
    activeset::GroupLassoData
    )
  normRes = zero(T)

  groups = activeset.groups
  numActive = activeset.numActive
  groupToIndex = activeset.groupToIndex

  group_j = groupToIndex[j]
  indC = 0
  @inbounds for column_ind in group_j
    indC += 1
    res[indC] = zero(T)
    @inbounds for i=1:activeset.numActive
      gr = groups[i]
      if gr == j
        continue
      end
      @inbounds for ind in groupToIndex[gr]
        res[indC] += x[ind] * A[ind, column_ind]
      end
    end
    res[indC] += b[column_ind]
    normRes += res[indC]^2.
  end
  sqrt(normRes)
end



function _tgemv!{T<:FloatingPoint}(
    β::T,
    A::StridedMatrix{T},
    b::StridedVector{T},
    α::T,
    out::StridedVector{T})

  nr, nc = size(A)
  @inbounds for c=1:nc
    v = zero(T)
    @inbounds for r=1:nr
      v += b[r] * A[r, c]
    end
    out[c] = out[c] * α + β*v
  end
  out
end

function _min_one_group!{T<:FloatingPoint}(
    x::StridedVector{T},
    A::SVD{T,T},
    b::StridedVector{T},
    gld::GroupLassoData,
    j::Int64,
    λ::T;
    options::LassoOptions   =   LassoOptions()
    )

  gjToIndex = gld.groupToIndex[j]
  btilde = gld.btilde
  x1 = gld.x1
  Utb = gld.Utb
  U = A[:U]
  D = A[:S]
  Vt = A[:Vt]

  group_len = size(U, 1)
  gn = zero(T)
  for i=1:group_len
    gn += b[i]^2.
  end
  gn = sqrt(gn) - λ
  lb = gn / D[1]
  ub = gn / D[end]
  #
  _tgemv!(-1., U, b, 0., Utb)
  while ub-lb > 1e-4
    ##
    @inbounds for i=1:group_len
      x1[i] = Utb[i] / (D[i] + λ / gn)
    end
    #     At_mul_B!(x, Vt, x1)
    en = zero(T)
    @inbounds for i=1:group_len
      xind = gjToIndex[i]
      x[xind] = zero(T)
      for j=1:group_len
        x[ind] += Vt[i, j] * x1[j]
      end
      en += x[ind]^2.
    end
    en = sqrt(en)
    ##
    if abs(gn - en) < options.xtol
      break
    else
      if en > gn
        lb = gn
      else
        ub = gn
      end
      gn = (ub + lb) / 2.
    end
  end
  x
end


function _group_lasso!{T<:FloatingPoint}(
    x::StridedVector{T},
    A::StridedMatrix{T},
    b::StridedVector{T},
    λ::StridedVector{T},
    activeset::GroupLassoData,
    svdVector::Vector;
    options::LassoOptions   =   LassoOptions()
    )

  numActive = activeset.numActive
  groups = activeset.groups
  groupToIndex = activeset.groupToIndex
  res = activeset._res
  iter = 0
  while true
    iter += 1
    maxUpdate = zero(T)
    for i=1:activeset.numActive
      j = group[i]

      _Axkpb!(res, A, b, x, j, activeset)
      group_norm = _group_norm(res, activeset, j)
      if group_norm <= λ[j]
        _fill_zero!(res, activeset, j)
      else
        bt = sub(res, groupToIndex[j])
        xt = sub(x, groupToIndex[j])
        ### minimize one group
      end
      #########################################33 check converged
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



