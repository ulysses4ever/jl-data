
const NB = 256000::Int64

type ReductionTree
  Q
  leaves::Array{Any,1}
end

type SHTSQRQ
  Q::SharedArray
  T::RemoteRef
end

#function shtsqr!( A::SharedArray )
#  m,n = size(A)
#  S = procs(A)
#  if length(S) == 1
#    T = remotecall_fetch(S[1], shtsqr!, A, 1, m)
#  else
#    T = remotecall_fetch(S[1], shtsqr!, A, 1, m, S)
#  end
#  return triu(A[1:n,:]), SHTSQRQ(A, T)
#end
#
#function shtsqr!( A::SharedArray, s::Int64, t::Int64 )
#  m,n = size(A)
#  F = seqtsqr!(sub(sdata(A), s:t, :), NB)
#  T = RemoteRef()
#  put!(T, ReductionTree(F, []))
#  return T
#end
#
#function shtsqr!( A::SharedArray, s::Int64, t::Int64, S::Array{Int64,1} )
#  m,n = size(A)
#  mid = s + div(t - s + 1, 2)
#  step = div(length(S), 2)
#  L = S[1:step]
#  LL = S[step+1:end]
#  rr = cell(2)
#  if length(L) == 1
#    rr[1] = remotecall(L[1], shtsqr!, A, s, mid)
#  else
#    rr[1] = remotecall(L[1], shtsqr!, A, s, mid, L)
#  end
#  if length(LL) == 1
#    rr[2] = remotecall(LL[1], shtsqr!, A, mid+1, t)
#  else
#    rr[2] = remotecall(LL[1], shtsqr!, A, mid+1, t, LL)
#  end
#  @sync begin
#    @async rr[1] = fetch(rr[1])
#    @async rr[2] = fetch(rr[2])
#  end
#  F = tpqrt!(sub(sdata(A), s:s+n-1, :), sub(sdata(A), mid+1:mid+n, :))
#  T = RemoteRef()
#  put!( T, ReductionTree(F, rr))
#  return T
#end

function shtsqr!( A::SharedArray, I::UnitRange )
  m,n = size(A)
  my_A = sub(sdata(A), I, :)
  #F = seqtsqr!( my_A, NB )
  Q,S = Base.LinAlg.LAPACK.geqrt!(my_A,min(n,36))
  F = Base.LinAlg.QRCompactWY(Q,sub(S,1:size(S,1),:))
  T = RemoteRef()
  put!( T, ReductionTree(F,[]) )
  return F[:R], T
end

function shtsqr!( A::SharedArray, rr1::RemoteRef, rr2::RemoteRef )
  m,n = size(A)
  R1, T1 = fetch(rr1)
  R2, T2 = fetch(rr2)
  F = tpqrt!( R1, R2)
  T = RemoteRef()
  put!( T, ReductionTree(F, [T1; T2]) )
  return R1, T
end

function shtsqr!( A::SharedArray )
  m,n = size(A)
  p = procs(A)
  np = length(p)
  idxs = Base.splitrange(m, np)
  refs = Array(RemoteRef, ceil(Int64, log2(np))+1,np)
  for i = 1:np
    refs[1,i] = remotecall( p[i], shtsqr!, A, idxs[i] )
  end
  for k = 1:ceil(Int64, log2(np))
    for i = 1:2^k:np
      if i + 2^(k-1) <= np
        j = i + 2^(k-1)
        refs[k+1,i] = remotecall( p[i], shtsqr!, A, refs[k,i], refs[k,j] )
      else
        refs[k+1,i] = refs[k,i]
      end
    end
  end
  I, T = fetch(refs[end,1])
  return SHTSQRQ(A,T), triu(A[1:n,:])
end

function shtsqr( A::SharedArray, I::UnitRange )
  #m,n = size(A)
  #copy!(sub(sdata(C),I,:), sub(sdata(A), I, :))
  #R = seqtsqr( my_A, NB )
  #Q,S = LAPACK.geqrt!(sub(sdata(C),I,:),min(n,36))
  F = qrfact(sub(sdata(A),I,:))
  #F = Base.LinAlg.QRCompactWY(Q,sub(S,1:size(S,1),:))
  return F[:R]
end

function shtsqr( A::SharedArray, rr1::RemoteRef, rr2::RemoteRef )
  m,n = size(A)
  R1, R2 = fetch(rr1), fetch(rr2)
  F = tpqrt!( R1, R2 )
  return R1
end

function shtsqr( A::SharedArray )
  m,n = size(A)
  p = procs(A)
  np = length(p)
  idxs = Base.splitrange(m, np)
  refs = Array(RemoteRef, ceil(Int64, log2(np))+1,np)
  for i = 1:np
    refs[1,i] = remotecall( p[i], shtsqr, A, idxs[i] )
  end
  for k = 1:ceil(Int64, log2(np))
    for i = 1:2^k:np
      if i + 2^(k-1) <= np
        j = i + 2^(k-1)
        refs[k+1,i] = remotecall( p[i], shtsqr, A, refs[k,i], refs[k,j] )
      else
        refs[k+1,i] = refs[k,i]
      end
    end
  end
  R = fetch(refs[end,1])
  return R
end

#function shtsqr( A::SharedArray )
#  m,n = size(A)
#  S = procs(A)
#  if length(S) == 1
#    R = remotecall_fetch(S[1], shtsqr, A, 1, m)
#  else
#    R = remotecall_fetch(S[1], shtsqr, A, 1, m, S)
#  end
#  return R
#end
#
#function shtsqr( A::SharedArray, s::Int64, t::Int64 )
#  m,n = size(A)
#  R = seqtsqr(sub(sdata(A), s:t, :), NB)
#  return R
#end
#
#function shtsqr( A::SharedArray, s::Int64, t::Int64, S::Array{Int64,1} )
#  m,n = size(A)
#  mid = s + div(t - s + 1, 2)
#  step = div(length(S), 2)
#  L = S[1:step]
#  LL = S[step+1:end]
#  rr = cell(2)
#  R = cell(2)
#  if length(L) == 1
#    rr[1] = remotecall(L[1], shtsqr, A, s, mid)
#  else
#    rr[1] = remotecall(L[1], shtsqr, A, s, mid, L)
#  end
#  if length(LL) == 1
#    rr[2] = remotecall(LL[1], shtsqr, A, mid+1, t)
#  else
#    rr[2] = remotecall(LL[1], shtsqr, A, mid+1, t, LL)
#  end
#  @sync begin
#    @async R[1] = fetch(rr[1])::Array{Float64,2}
#    @async R[2] = fetch(rr[2])::Array{Float64,2}
#  end
#  F = tpqrt!( R[1], R[2] )
#  return R[1]
#end


function constructQ!( Q::SHTSQRQ )
  m,n = size(Q.Q)

  # Replace R factor in upper corner with the upper triangle of the identity
  for j = 2:n
    @simd for i = 1:j-1
      @inbounds Q.Q[i,j] = 0
    end
  end
  @simd for i = 1:n
    @inbounds Q.Q[i,i] = 1
  end
  remotecall_fetch( Q.T.where, constructQ!, Q.T, n )
  return Q.Q
end

function constructQ!( T::RemoteRef, n )
  T = fetch(T)

  # If at leaf nodes, use the seqtsqr method
  if length(T.leaves) == 0
    R = zeros(size(T.Q.factors)...)
    # Copy into separate array so multiplication works
    for j = 1:n
      @simd for i = 1:j
        @inbounds R[i,j] = T.Q.factors[i,j]
      end
    end
    # Multiply Q by the new array R
    gemqrt!('L','N',T.Q.factors,T.Q.T,R)
    copy!(T.Q.factors,R)

  # Otherwise, use tpmqrt
  else
    R = zeros(n,n)
    # Copy into separate array R
    for j = 1:n
      @simd for i = 1:j
        @inbounds R[i,j] = T.Q.R[i,j]
      end
    end
    # Multiply Q by the new array R
    Q1,Q2 = tpmqrt!( T.Q, R )
    # Copy data back to original matrix
    for j = 1:n
      @simd for i = 1:j
        @inbounds T.Q.R[i,j] = Q1[i,j]
        @inbounds T.Q.V[i,j] = Q2[i,j]
      end
    end
    # Perform on children
    @sync begin
      @async remotecall_wait( T.leaves[1].where, constructQ!, T.leaves[1], n)
      @async remotecall_wait( T.leaves[2].where, constructQ!, T.leaves[2], n)
    end
  end
end

