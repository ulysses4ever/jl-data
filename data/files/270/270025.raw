function tsqr!( A::BlockMatrix )
  return remotecall_fetch( A[1].where, blktsqr!, A )
end

function blktsqr!( A::BlockMatrix )
  if nblocks(A) == 1
    M = fetch(A[1])
    Q = seqtsqr!(M, 200)
    R = triu(Q.Q[1:A.n,:])
    return R
  else
    step = div(nblocks(A), 2)
    R = cell(2)
    @sync begin
      @async R[1] = blktsqr!( A[1:step] )
      @async R[2] = remotecall_fetch( A[step+1].where, blktsqr!, A[step+1:length(A.procs)] )
    end
    tpqrt!( R[1], R[2] )
    return R[1]
  end
end
