
type SeqTSQRQ
  Q::StridedMatrix
  tau::Array{Float64, 1}
end

@inline function loc(A::Ptr{Float64}, i::Int64)
  return A + sizeof(eltype(A))*(i-1)
end

function seqtsqr!( A::StridedMatrix{Float64}, cs::Int64 )
  m,n = size(A)
  nb = max(div(cs,n),n)
  m1 = min(nb,m)

  # Preallocate work array to save allocation time
  work = Array(Float64, n)
  # tau array holds the tau values from the first QR factorization
  tau = Array(Float64, n)
  # t is used to hold the computed tau in the rest of the factorizations
  t = Array(Float64,1)
  # Factor first block
  Base.LinAlg.LAPACK.geqrf!(sub(A, 1:m1, :), tau)

  # Factor remaining blocks
  for i = m1+1:nb:m
    m1 = min(i+nb-1,m) - i + 1
    tpqrf!(m1, n, pointer(A), stride(A,2), pointer(A,i), stride(A,2), pointer(t), pointer(work))
  end

  return SeqTSQRQ( A, tau )
end

# Same as above, but does not modify A and only returns R
function seqtsqr( A::StridedMatrix{Float64}, cs::Int64 )
  m,n = size(A)
  nb = min(max(div(cs,n),n),m)
  m1 = min(nb,m)

  # Allocate space
  A2 = zeros( nb, n )
  T = Array(Float64, min(36,n), n)
  work = Array(Float64, size(T,1)*n)

  # Copy first block of A to temporary space
  for j = 1:n
    @simd for i = 1:m1
      @inbounds A2[i,j] = A[i,j]
    end
  end
  Base.LinAlg.LAPACK.geqrt!( sub(A2, 1:m1, :), T )
  R = triu(sub(A2,1:n,:))

  for i = m1+1:nb:m
    m1 = min(i+nb-1,m) - i + 1
    for j = 1:n
      @simd for k = 1:m1
        @inbounds A2[k,j] = A[i+k-1,j]
      end
    end
    tpqrt!( R, A2, 0.0, T, work )
  end

  return R
end

# Do TSQR with reduction for diagonal plus low rank
function seqtsqr!( A::StridedMatrix{Float64}, nb::Int64, U::StridedMatrix,
                  B::Diagonal )
  m,n = size(A)
  k   = size(U)[2]
  m1 = min(nb,m)

  # Allocate space
  work = Array(Float64, max(n,k))
  A2 = zeros( nb, n )
  t = Array(Float64, n)

  # Copy first block of A to temporary space
  for j = 1:n
    @simd for i = 1:m1
      @inbounds A2[i,j] = A[i,j]
    end
  end
  Asub = sub(A2, 1:m1, :)
  Base.LinAlg.LAPACK.geqrf!( Asub, work )
  R = triu(sub(A2,1:n,:))

  for i = m1+1:nb:m
    m1 = min(i+nb-1,m) - i + 1
    for j = 1:n
      @simd for l = 1:m1
        @inbounds A2[l,j] = A[i+l-1,j]
      end
    end
    tpqrf!( m1, n, pointer(R), stride(R,2), pointer(A2), stride(A2,2), pointer(t), pointer(work))
  end

  Base.LinAlg.BLAS.trsm!( 'R', 'U', 'N', 'N', 1.0, R, A )
  U2 = Base.LinAlg.BLAS.gemm( 'T', 'N', A, U )
  scale!(sqrt(B.diag), A)
  M2 = Base.LinAlg.BLAS.syrk( 'U', 'T', 1.0, A )

  return R, U2, M2
end

# nb must be the same as the input to seqtsqr!
function seqmtsqr!( A::SeqTSQRQ, B::Array{Float64,2}, nb::Int64 )
  # Assign a reference for convenience
  Q = A.Q
  m,n = size(Q)
  m1 = mod(m, nb)

  work = Array(Float64, n)

  # Compute Q starting from last block
  if m > nb
    if m1 != 0
      tpmqrf!(m1, n, pointer(B), stride(B,2), pointer(Q, m-m1+1), stride(Q,2), pointer(work))
    end
    for i = m-m1-nb+1:-nb:nb
      tpmqrf!(nb, n, pointer(B), stride(B,2), pointer(Q, i), stride(Q,2), pointer(work))
    end
  end
  # Construct the final explicit Q block, then multiply to get the final answer
  Base.LinAlg.LAPACK.orgqr!(sub(Q, 1:min(nb,m), :), A.tau)
  mytrmm!('R', 'U', 'N', 'N', min(nb,m), n, 1.0, pointer(B), stride(B,2), pointer(Q), stride(Q,2))

end

