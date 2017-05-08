# Types for storing info about reduction tree
type ReductionTree
  Q
  leaves::Array{Any,1}
end

type TSQRQ
  Q::SharedArray
  T::RemoteRef
end

#
# Functions to map to leaf nodes and then reduce in binary tree
#
function tsqr_map( F, A::SharedArray )
  m,n = size(A)
  p = procs(A)
  refs = Array(RemoteRef, length(p))
  for (i, idx) in enumerate(Base.splitrange(m,length(p)))
    refs[i] = remotecall( p[i], F, A, idx )
  end
  return refs
end

function tsqr_reduce( F, A::SharedArray, refs )
  p = procs(A)
  np = length(p)
  for k = 1:ceil(Int64, log2(np))
    for i = 1:2^k:np
      if i + 2^(k-1) <= np
        j = i+2^(k-1)
        refs[i] = remotecall( p[i], F, A, refs[i], refs[j] )
      end
    end
  end
  return refs[1]
end


#
# TSQR, where A is overwritten by implicit Q
#
function tsqr!( A::SharedArray, I::UnitRange )
  m,n = size(A)
  # Factor this segment of A, overwriting with R and implicit Q
  F = qrfact!(sub(sdata(A), I, :))
  T = RemoteRef()
  put!( T, ReductionTree(F,[]) )
  # Return a COPY of R, since LAPACK's tpqrt appears to write over the lower
  # triangle
  return F[:R], T
end

function tsqr!( A::SharedArray, rr1::RemoteRef, rr2::RemoteRef )
  m,n = size(A)
  R1, T1 = fetch(rr1)
  R2, T2 = fetch(rr2)
  F = tpqrt!( R1, R2 )
  T = RemoteRef()
  put!( T, ReductionTree(F, [T1; T2]) )
  return R1, T
end

function tsqr!( A::SharedArray )
  rr = tsqr_map( tsqr!, A )
  R,T = fetch(tsqr_reduce( tsqr!, A, rr ))
  return TSQRQ(A,T), R
end


#
# TSQR, A is not overwritten and Q is discarded. Only R is returned
#
function tsqr( A::SharedArray, I::UnitRange )
  F = qrfact(sub(sdata(A),I,:))
  return F[:R]
end

function tsqr( A::SharedArray, rr1::RemoteRef, rr2::RemoteRef )
  m,n = size(A)
  R1, R2 = fetch(rr1), fetch(rr2)
  tpqrt!( R1, R2 )
  return R1
end

function tsqr( A::SharedArray )
  rr = tsqr_map( tsqr, A )
  R = fetch( tsqr_reduce( tsqr, A, rr ) )
  return R
end

#
# Construct full Q from explicit representation
#
function constructQ!( Q::TSQRQ )
  m,n = size(Q.Q)
  remotecall_wait( Q.T.where, constructQ!, Q.T, eye(n,n) )
  return Q.Q
end

function constructQ!( T::RemoteRef, A::Array{Float64,2} )
  T = fetch(T)

  # If at leaf nodes, use gemqrtr!
  if length(T.leaves) == 0
    m,n = size(T.Q.factors)
    R = zeros(m,n)
    for j = 1:n
      for i = 1:j
        @inbounds R[i,j] = A[i,j]
      end
    end
    # Multiply Q by the new array A
    gemqrtr!(T.Q,R)
    copy!(T.Q.factors,R)

  # Otherwise, use tpmqrt
  else
    # Multiply Q by the new array R
    Q1,Q2 = tpmqrt!( T.Q, A )
    # Perform on children
    @sync begin
      @async remotecall_wait( T.leaves[1].where, constructQ!, T.leaves[1], Q1)
      @async remotecall_wait( T.leaves[2].where, constructQ!, T.leaves[2], Q2)
    end
  end
end

