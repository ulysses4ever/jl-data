type TPQRCompactWY{S}
  R::StridedMatrix{S}
  V::StridedMatrix{S}
  T::Array{Float64,2}
end

function tpqrt!( A, B, l, T, work )
  m, n = size(B)
  nb = size(T,1)
  info = 0
  ccall((:dtpqrt_,Base.libblas_name), Void, (Ptr{Int64}, Ptr{Int64},
    Ptr{Int64}, Ptr{Int64}, Ptr{Float64}, Ptr{Int64}, Ptr{Float64},
    Ptr{Int64}, Ptr{Float64}, Ptr{Int64}, Ptr{Float64}, Ptr{Int64}), &m,
    &n, &l, &nb, A, &max(1, stride(A,2)), B, &max(1, stride(B,2)), T, &max(1,
    stride(T,2)), work, &info)
  TPQRCompactWY(A, B, T)
end

tpqrt!(A,B,l,T) = tpqrt!(A,B,l,T, Array(Float64,size(T,1)*size(A,2)))
tpqrt!(A,B,l) = tpqrt!(A,B,l, Array(Float64,min(36,size(A,2)),size(A,2)))
tpqrt!(A,B) = tpqrt!(A,B,0.0)

function tpmqrt!( Q::TPQRCompactWY, A )
  m, n = size(A)
  k = l = n
  nb = min( n, 36 )
  B = zeros(m, n)
  work = Array(Float64, nb*n)
  info = Array(Int64, 1)
  trans = 'N'
  side = 'L'
  ccall((:dtpmqrt_,Base.libblas_name), Void, (Ptr{Uint8}, Ptr{Uint8},Ptr{Int64},
  Ptr{Int64}, Ptr{Int64}, Ptr{Int64}, Ptr{Int64}, Ptr{Float64}, Ptr{Int64},
  Ptr{Float64}, Ptr{Int64}, Ptr{Float64}, Ptr{Int64}, Ptr{Float64}, Ptr{Int64},
  Ptr{Float64}, Ptr{Int64}),
  &side, &trans, &m, &n, &k, &l, &nb, Q.V, &max(1, stride(Q.V,2)), Q.T,
  &max(1, stride(Q.T,2)), A, &max(1, stride(A,2)), B, &max(1, stride(B,2)),
  work, info)
  # Returns Q1 and Q2, where QA = [Q1; Q2]
  A, B
end

function mylarfg!( n::Int64, alpha::Ptr{Float64}, X::Ptr{Float64}, incx::Int64, tau::Ptr{Float64} )
  ccall((:dlarfg_, Base.libblas_name), Void, (Ptr{Int64}, Ptr{Float64}, 
    Ptr{Float64}, Ptr{Int64}, Ptr{Float64}), &n, alpha, X, &incx, tau)
end

function mygemv!(trans::Char, m::Int64, n::Int64, alpha::Float64, 
  A::Ptr{Float64}, lda::Int64,
  X::Ptr{Float64}, incx::Int64, beta::Float64, Y::Ptr{Float64}, incy::Int64)
  ccall((:dgemv_,Base.libblas_name), Void,
    (Ptr{UInt8}, Ptr{Int64}, Ptr{Int64}, Ptr{Float64},
     Ptr{Float64}, Ptr{Int64}, Ptr{Float64}, Ptr{Int64},
     Ptr{Float64}, Ptr{Float64}, Ptr{Int64}),
    &trans, &m, &n, &alpha,
    A, &lda, X, &incx,
    &beta, Y, &incy)
end

function myger!(m::Int64, n::Int64, α::Float64, x::Ptr{Float64}, incx::Int64,
              y::Ptr{Float64}, incy::Int64, A::Ptr{Float64}, lda::Int64)
  ccall((:dger_, Base.libblas_name), Void,
    (Ptr{Int64}, Ptr{Int64}, Ptr{Float64}, Ptr{Float64},
     Ptr{Int64}, Ptr{Float64}, Ptr{Int64}, Ptr{Float64},
     Ptr{Int64}),
    &m, &n, &α, x,
    &incx, y, &incy, A,
    &lda)
end

function mytrmm!(side::Char, uplo::Char, trans::Char, diag::Char,
                m::Int64,n::Int64, alpha::Float64, A::Ptr{Float64}, lda::Int64,
                B::Ptr{Float64}, ldb::Int64)
  ccall((:dtrmm_, Base.libblas_name), Void,
    (Ptr{Char}, Ptr{Char}, Ptr{Char}, Ptr{Char}, Ptr{Int64}, Ptr{Int64},
      Ptr{Float64}, Ptr{Float64}, Ptr{Int64}, Ptr{Float64}, Ptr{Int64}),
    &side, &uplo, &trans, &diag,
    &m, &n, &alpha, A, &lda, B, &ldb)
end


@inline function loc(A::Ptr{Float64}, lda::Int64, i::Int64, j::Int64)
  return A + sizeof(eltype(A))*(lda*(j-1)+i-1)
end

@inline function loc(A::Ptr{Float64}, i::Int64)
  return A + sizeof(eltype(A))*(i-1)
end

# QR factorization of triangle on top of rectangle
function tpqrf!( m::Int64, n::Int64, A::Ptr{Float64}, lda::Int64,
                 B::Ptr{Float64}, ldb::Int64, tau::Ptr{Float64}, work::Ptr{Float64} )
  for j = 1:n
    n1 = n-j
    # Construct Householder reflector
    mylarfg!(m+1, loc(A, lda, j, j), loc(B, ldb, 1, j), 1, tau)
    # Apply reflector to remainder
    BLAS.blascopy!(n1, loc(A, lda, j, j+1), lda, loc(work, j+1), 1)
    mygemv!('T', m, n1, 1.0, loc(B, ldb, 1, j+1), ldb, loc(B, ldb, 1, j), 1, 1.0, 
      loc(work, j+1), 1)
    BLAS.axpy!(n1, -unsafe_load(tau), loc(work, j+1), 1, 
      loc(A, lda, j, j+1), lda)
    myger!(m, n1, -unsafe_load(tau), loc(B, ldb, 1, j), 1, loc(work, j+1), 1, loc(B, ldb, 1, j+1), ldb)
  end
end

function tpmqrf!( m::Int64, n::Int64, A::Ptr{Float64}, lda::Int64,
                  B::Ptr{Float64}, ldb::Int64, work::Ptr{Float64})
  for j = n:-1:1
    n1 = n-j
    # Compute tau from the stored Householder vector
    t = 2/(1.0+BLAS.dot(m, loc(B, ldb, 1, j), 1, loc(B, ldb, 1, j), 1))
    a = unsafe_load(loc(A, lda, j, j))

    # Apply reflector to submatrix. Confusing pointers!
    BLAS.blascopy!(n1+1, loc(A, lda, j, j), lda, loc(work, j), 1)
    mygemv!('T', m, n1, 1.0, loc(B, ldb, 1, j+1), ldb, loc(B, ldb, 1, j), 1, 1.0, 
      loc(work, j+1), 1)
    BLAS.axpy!(n1+1, -t, loc(work, j), 1, loc(A, lda, j, j), lda)
    # unsafe_store!(loc(A, lda, j, j), a-t*a)
    myger!(m, n1, -t, loc(B, ldb, 1, j), 1, loc(work, j+1), 1, loc(B, ldb, 1, j+1), ldb)
    w = unsafe_load(loc(work,j))
    BLAS.scal!(m, -t*w, loc(B,ldb,1,j), 1)
  end
end

# Compute Q'A for A split into nxk A and mxk B
function tpmrqrf!( m::Int64, n::Int64, k::Int64, A::Ptr{Float64}, lda::Int64,
                   B::Ptr{Float64}, ldb::Int64, 
                   V::Ptr{Float64}, ldv::Int64, work::Ptr{Float64} )
  for j = 1:n
    # Compute tau
    t = 2/(1.0+BLAS.dot(m, loc(V, ldv, 1, j), 1, loc(V, ldv, 1, j), 1))
    BLAS.blascopy!( k, loc(A,j), lda, work, 1 )
    mygemv!('T', m, k, 1.0, loc(B,1), ldb, loc(V,ldv,1,j), 1, 1.0, work, 1)
    BLAS.axpy!(k, -t, work, 1, loc(A,j), lda)
    myger!(m,k,-t, loc(V,ldv,1,j), 1, work, 1, loc(B,1), ldb)
  end
end

A_mul_B!(A::TPQRCompactWY, B::StridedVecOrMat) = tpmqrt!(A,B)

# Sparse matrix multiple vector multiplication
function mkl_cscmm!( Y::Array, A::SparseMatrixCSC, X::Array )
  m,n = size(X)
  trans = 'N'
  alpha = 1.0
  beta = 0.0
  ccall((:mkl_dcscmm_, Base.libblas_name), Void,
  (Ptr{UInt8}, Ptr{Int64}, Ptr{Int64},
  Ptr{Int64}, Ptr{Float64}, Ptr{UInt8}, Ptr{Float64}, Ptr{Int64}, Ptr{Int64},
  Ptr{Int64}, Ptr{Float64}, Ptr{Int64}, Ptr{Float64}, Ptr{Float64},
  Ptr{Int64}),
  &trans, &m, &n, &m, &alpha, "GUNF", A.nzval, A.rowval, A.colptr,
  pointer(A.colptr,2), X, &stride(X,2), &beta, Y,
  &stride(Y,2))
end

# Sparse symmetric matrix multiple vector multiplication (only store upper
# triangle of A!)
function mkl_cscsymm!( Y::Array, A::SparseMatrixCSC, X::Array )
  m,n = size(X)
  trans = 'N'
  alpha = 1.0
  beta = 0.0
  ccall((:mkl_dcscmm_, Base.libblas_name), Void,
  (Ptr{UInt8}, Ptr{Int64}, Ptr{Int64},
  Ptr{Int64}, Ptr{Float64}, Ptr{UInt8}, Ptr{Float64}, Ptr{Int64}, Ptr{Int64},
  Ptr{Int64}, Ptr{Float64}, Ptr{Int64}, Ptr{Float64}, Ptr{Float64},
  Ptr{Int64}),
  &trans, &m, &n, &m, &alpha, "SUNF", A.nzval, A.rowval, A.colptr,
  pointer(A.colptr,2), X, &stride(X,2), &beta, Y,
  &stride(Y,2))
end

function dlarfbtr!( V::StridedMatrix, T::StridedMatrix, R::StridedMatrix,
  work::StridedMatrix )
  m,n = size(R)
  k = size(T,1)
  for j = 1:k
    @simd for i = 1:k
      @inbounds work[i,j] = R[i,j]
    end
  end
  for j = 1:k
    @simd for i = k+1:m
      @inbounds R[i,j] = V[i,j]
    end
  end

  BLAS.trmm!( 'L', 'L', 'T', 'U', 1.0, sub(V, 1:k, 1:k), work ) 
  BLAS.trmm!( 'L', 'U', 'N', 'N', 1.0, T, work )
  BLAS.trmm!( 'R', 'U', 'N', 'N', -1.0, work, sub(R,k+1:m,1:k))
  BLAS.trmm!( 'L', 'L', 'N', 'U', 1.0, sub(V,1:k,1:k), work )
  for j = 1:k
    @simd for i = 1:k
      @inbounds R[i,j] = R[i,j] - work[i,j]
    end
  end
end

function dlarfb!( V::StridedMatrix, T::StridedMatrix, C::StridedMatrix,
  work::StridedMatrix )
  m,n = size(C)
  k = size(T,1)
  side = 'L'
  trans = 'N'
  direct = 'F'
  storev = 'C'
  ccall((:dlarfb_, Base.libblas_name), Void, 
  (Ptr{UInt8}, Ptr{UInt8}, Ptr{UInt8}, Ptr{UInt8},
   Ptr{Int64}, Ptr{Int64}, Ptr{Int64},
   Ptr{Float64}, Ptr{Int64}, Ptr{Float64}, Ptr{Int64},
   Ptr{Float64}, Ptr{Int64}, Ptr{Float64}, Ptr{Int64}),
  &side, &trans, &direct, &storev, &m, &n, &k, V, &stride(V,2),
  T, &stride(T,2), C, &stride(C,2), work, &stride(work,2))
end



function gemqrtr!( F::Base.LinAlg.QRCompactWY, R::Array{Float64,2} )
  m,n = size(R)
  nb = 36
  work = zeros(n,nb)
  for i = (div(n-1,nb)*nb+1):-nb:1
    ib = min(n-i+1,nb)
    V = sub( F.factors, i:m, i:i+ib-1 )
    T = sub( F.T, 1:ib, i:i+ib-1 )
    dlarfbtr!( V, T, sub( R, i:m, i:i+ib-1 ), sub(work, 1:ib, 1:ib) )
    if i+ib-1 < n
      dlarfb!( V, T, sub( R, i:m, i+ib:n ), work )
    end
  end
end

