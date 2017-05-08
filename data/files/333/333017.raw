function bottom_up_dtsqr!( A::DArray )
  S = procs(A)
  n = length(S)
  T = Array(RemoteRef, n)
  for i = 1:n
    T[i] = remotecall(S[i], bu_dtsqr!, A)
  end
  while n != 1
    for i = 1:2:n
      p = div(i+1,2)
      if i == n
        T[p] = remotecall(S[p], bu_dtsqr!,[T[i]])
      else
        T[p] = remotecall(S[p], bu_dtsqr!, [T[i];T[i+1]])
      end
      n = div(i+1,2)
    end
  end
  return fetch(T[1])
end

function bu_dtsqr!( A::DArray )
  F = qrfact!(localpart(A))
  T = RemoteRef()
  put!(T,ReductionTree(F[:Q], []))
  return F[:R], T
end

function bu_dtsqr!( children::Array{RemoteRef,1} )
  n = length(children)
  Rs = cell(n)
  Ts = cell(n)
  @sync for i = 1:n
    @async Rs[i], Ts[i] = fetch( children[i] )
  end
  if n == 1
    return Rs[1], Ts[1]
  end
  F = tpqrt!(Rs[1],Rs[2])
  T = RemoteRef()
  put!( T, ReductionTree(F, Ts) )
  return F.R, T
end

# One master process distributes to all workers
function dtsqr!( A::DArray )
  S = procs(A)
  return remotecall_fetch( S[1], dtsqr!, A, S )
end

function dtsqr!( A::DArray, S )
  nblocks = length(S)
  if nblocks == 1
    Q,R = seqtsqr!(localpart(A), 200)
    T = RemoteRef()
    put!(T, ReductionTree(Q, []))
    return R, T
  else
    step = div(nblocks,2)
    rr1 = remotecall( S[1], dtsqr!, A, S[1:step] )
    rr2 = remotecall( S[step+1], dtsqr!, A, S[step+1:end] )
    Rs = cell(2)
    Ts = cell(2)
    @sync begin
      @async @inbounds Rs[1], Ts[1] = fetch( rr1 )
      @async @inbounds Rs[2], Ts[2] = fetch( rr2 )
    end
    F = tpqrt!(Rs[1], Rs[2])
    T = RemoteRef()
    put!( T, ReductionTree(F, Ts) )
    return(F.R,T)
  end
end

function constructQ( T )
  m,n = size(fetch(T).Q.R)
  applyQ( T, eye(n,n) )
end

function applyQ( RR, initial )
  T = fetch(RR)
  if length(T.leaves) == 0
    return T.Q*initial
  end
  Q = tpmqrt!(T.Q,initial)
  rr1 = remotecall( T.leaves[1].where, applyQ, T.leaves[1], Q[1] )
  rr2 = remotecall( T.leaves[2].where, applyQ, T.leaves[2], Q[2] )
  Q1 = [fetch(rr1); 
        fetch(rr2)]
  return( Q1 )
end

