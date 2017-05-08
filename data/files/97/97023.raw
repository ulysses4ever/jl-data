type GroupLassoData{T<:AbstractFloat, I}
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


function GroupLassoData{T<:AbstractFloat, I}(
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

function _add_violator!{T<:AbstractFloat}(
    gld::GroupLassoData,
    x::StridedVector{T},
    A::StridedMatrix{T},
    b::StridedVector{T},
    λ::StridedVector{T};
    options::LassoOptions   =   LassoOptions()
    )
  changed = false

  zerothr = options.zerothr
  groups = gld.groups
  numActive = gld.numActive
  groupToIndex = gld.groupToIndex
  numElem = length(groups)
  # check for things to be removed from the active set
  i = 0
  @inbounds while i < numActive
    i = i + 1
    t = groups[i]
    if ~isdefined(gld.Asvd, t)
      gld.Asvd[t] = svdfact(sub(A, groupToIndex[t], groupToIndex[t]))
    end
    if _group_norm(x, gld, t) < zerothr
      _fill_zero!(x, gld, t)
      changed = true
      groups[numActive], groups[i] = groups[i], groups[numActive]
      numActive -= 1
      i = i - 1
    end
  end
  gld.numActive = numActive

  btild = gld.btild
  I = 0
  V = zero(T)
  @inbounds for i=numActive+1:numElem
    t = groups[i]
    group_norm = _Axkpb!(btild, A, b, x, t, gld)
    nV = group_norm - λ[t]
    if V < nV
      I = i
      V = nV
    end
  end
  if I > 0 && V > options.gradtol
    t = groups[I]
    if ~isdefined(gld.Asvd, t)
      gld.Asvd[t] = svdfact(sub(A, groupToIndex[t], groupToIndex[t]))
    end
    changed = true
    numActive += 1
    groups[numActive], groups[I] = groups[I], groups[numActive]
  end
  gld.numActive = numActive
  changed
end

function _group_norm{T<:AbstractFloat}(
    x::StridedVector{T},
    gld::GroupLassoData{T},
    j::Int64
    )
  r = zero(T)
  @inbounds for i in gld.groupToIndex[j]
    r += x[i]^2.
  end
  sqrt(r)
end

function _fill_zero!{T<:AbstractFloat, I}(
    x::StridedVector{T},
    gld::GroupLassoData{T, I},
    j::Int64
    )
  @inbounds for i in gld.groupToIndex[j]
    x[i] = zero(T)
  end
  x
end

# computes x[-gj]'A[-gj, gj] + b[gj]'
# returns norm of res
function _Axkpb!{T<:AbstractFloat}(
    res::StridedVector{T},
    A::StridedMatrix{T},
    b::StridedVector{T},
    x::StridedVector{T},
    j::Int64,
    gld::GroupLassoData
    )
  normRes = zero(T)

  groups = gld.groups
  numActive = gld.numActive
  groupToIndex = gld.groupToIndex

  group_j = groupToIndex[j]
  indC = 0
  @inbounds for column_ind in group_j
    indC += 1
    res[indC] = zero(T)
    for i=1:numActive
      gr = groups[i]
      if gr == j
        continue
      end
      for ind in groupToIndex[gr]
        res[indC] += x[ind] * A[ind, column_ind]
      end
    end
    res[indC] += b[column_ind]
    normRes += res[indC]^2.
  end
  sqrt(normRes)
end

function _tgemv!{T<:AbstractFloat}(
    β::T,
    A::StridedMatrix{T},
    b::StridedVector{T},
    α::T,
    out::StridedVector{T})

  nr, nc = size(A)
  @inbounds for c=1:nc
    v = zero(T)
    for r=1:nr
      v += b[r] * A[r, c]
    end
    out[c] = out[c] * α + β*v
  end
  out
end

function _min_one_group!{T<:AbstractFloat}(
    x::StridedVector{T},
    A::SVD{T,T},
    b::StridedVector{T},
    gld::GroupLassoData,
    j::Int64,
    λ::T;
    options::LassoOptions   =   LassoOptions()
    )

  gjToIndex = gld.groupToIndex[j]
  x1 = gld.x1
  Utb = gld.Utb
  U = A[:U]
  D = A[:S]
  Vt = A[:Vt]

  group_len = size(U, 1)
  gn = zero(T)
  @inbounds for i=1:group_len
    gn += b[i]^2.
  end
  gn = sqrt(gn) - λ
  lb = gn / D[1]
  ub = gn / D[end]
  #
  _tgemv!(-1., U, b, 0., Utb)
  @inbounds while true
    ##
    for i=1:group_len
      x1[i] = Utb[i] / (D[i] + λ / gn)
    end
    #     At_mul_B!(x, Vt, x1)
    en = zero(T)
    for i=1:group_len
      xind = gjToIndex[i]
      x[xind] = zero(T)
      for j=1:group_len
        x[xind] += Vt[j, i] * x1[j]
      end
      en += x[xind]^2.
    end
    en = sqrt(en)
    ##
    if abs(gn - en) < options.xtol || ub - lb < options.xtol
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

function _group_lasso!{T<:AbstractFloat}(
    x::StridedVector{T},
    A::StridedMatrix{T},
    b::StridedVector{T},
    λ::StridedVector{T},
    gld::GroupLassoData;
    options::LassoOptions   =   LassoOptions()
    )

  numActive = gld.numActive
  groups = gld.groups
  groupToIndex = gld.groupToIndex
  btild = gld.btild
  xold = gld.xold

  iter = 0
  @inbounds while true
    iter += 1
    maxUpdate = zero(T)
    for i=1:numActive
      j = groups[i]
      group_norm = _Axkpb!(btild, A, b, x, j, gld)
      if group_norm <= λ[j]
        _fill_zero!(x, gld, j)
      else
        _min_one_group!(x, gld.Asvd[j], btild, gld, j, λ[j]; options=options)
      end
      # compute norm of change
      norm_diff = zero(T)
      for k in groupToIndex[j]
        norm_diff += (x[k] - xold[k])^2.
      end
      norm_diff = sqrt(norm_diff)
      if norm_diff > maxUpdate
        maxUpdate = norm_diff
      end
    end
    if iter > options.max_inner_iter || maxUpdate < options.xtol
      break
    end
    copy!(xold, x)
  end
  x
end



group_lasso!{T<:AbstractFloat, I}(
    x::StridedVector{T},
    A::StridedMatrix{T},
    b::StridedVector{T},
    λ::T,
    groupToIndex::Vector{I};
    options::LassoOptions   =   LassoOptions(),
    gld                     =   nothing
    ) = group_lasso!(x, A, b, fill(λ, length(groupToIndex)), groupToIndex; options=options, gld=gld)



function group_lasso!{T<:AbstractFloat, I}(
    x::StridedVector{T},
    A::StridedMatrix{T},
    b::StridedVector{T},
    λ::StridedVector{T},
    groupToIndex::Vector{I};
    options::LassoOptions   =   LassoOptions(),
    gld                     =   nothing
    )

  maxoutiter = options.max_outer_iter
  if is(gld, nothing)
    gld = GroupLassoData(x, groupToIndex; options=options)
  end
  _add_violator!(gld, x, A, b, λ; options=options)

  for outiter=1:maxoutiter
    _group_lasso!(x, A, b, λ, gld; options=options)
    if ~_add_violator!(gld, x, A, b, λ; options=options)
      break
    end
  end
  x, gld
end




