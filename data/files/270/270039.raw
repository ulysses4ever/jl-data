
type TPQRCompactWY{S}
  R::StridedMatrix{S}
  V::StridedMatrix{S}
  T::Array{Float64,2}
end

## QR factorization of two triangles on top of each other
#function tpqrt!( A::StridedMatrix, B::StridedMatrix )
#  m, n = size(B)
#  tau = Array(Float64, n)
#  work = zeros(n)
#  for j = 1:n
#    # Construct Householder reflector
#    A[j,j], tau[j] = larfg!(A[j,j], sub(B, 1:j, j))
#    # Apply reflector to remainder
#    @simd for i = j+1:n
#      @inbounds work[i] = A[j,i]
#    end
#    Base.LinAlg.BLAS.gemv!('T', 1.0, sub(B, 1:j, j+1:n), sub(B, 1:j, j), 1.0, sub(work, j+1:n))
#    @simd for i = j+1:n
#      @inbounds A[j, i] = -tau[j]*work[i] + A[j,i]
#    end
#    Base.LinAlg.BLAS.ger!(-tau[j], sub(B, 1:j, j), sub(work, j+1:n), sub(B, 1:j, j+1:n))
#  end
#  return TPQRCompactWY(A, B, tau)
#end
#
#function tpmqrt!( Q::TPQRCompactWY, A, B )
#  m,n = size(B)
#  V = Q.V
#  tau = Q.T
#  work = zeros(n)
#  for j = n:-1:1
#
#    for i = j:n
#      work[i] = A[j,i]
#    end
#
#    a = A[j,j]
#
#    Base.LinAlg.BLAS.gemv!('T', 1.0, sub(B, 1:j, j:n), sub(V, 1:j, j), 1.0, sub(work, j:n))
#
#    for i = j:n
#      A[j,i] = -tau[j]*work[i] + A[j,i]
#    end
#
#    Base.LinAlg.BLAS.ger!(-tau[j], sub(V, 1:j, j), sub(work, j:n), sub(B, 1:j, j:n))
#
#  end
#  return A, B
#end

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


function larfg!( alpha::Float64, X::StridedVector{Float64} )
  tau = Array(Float64, 1)
  a = Array(Float64, 1)
  a[1] = alpha
  n = length(X) + 1
  incx = stride(X, 1)
  ccall((:dlarfg_, Base.libblas_name), Void, (Ptr{Int64}, Ptr{Float64}, 
    Ptr{Float64}, Ptr{Int64}, Ptr{Float64}), &n, a, X, &incx, tau)
  return a[1], tau[1]
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
    Base.LinAlg.BLAS.blascopy!(n1, loc(A, lda, j, j+1), lda, loc(work, j+1), 1)
    mygemv!('T', m, n1, 1.0, loc(B, ldb, 1, j+1), ldb, loc(B, ldb, 1, j), 1, 1.0, 
      loc(work, j+1), 1)
    Base.LinAlg.BLAS.axpy!(n1, -unsafe_load(tau), loc(work, j+1), 1, 
      loc(A, lda, j, j+1), lda)
    myger!(m, n1, -unsafe_load(tau), loc(B, ldb, 1, j), 1, loc(work, j+1), 1, loc(B, ldb, 1, j+1), ldb)
  end
end

function tpmqrf!( m::Int64, n::Int64, A::Ptr{Float64}, lda::Int64,
                  B::Ptr{Float64}, ldb::Int64, work::Ptr{Float64})
  for j = n:-1:1
    n1 = n-j
    # Compute tau from the stored Householder vector
    t = 2/(1.0+Base.LinAlg.BLAS.dot(m, loc(B, ldb, 1, j), 1, loc(B, ldb, 1, j), 1))
    a = unsafe_load(loc(A, lda, j, j))

    # Apply reflector to submatrix. Confusing pointers!
    Base.LinAlg.BLAS.blascopy!(n1+1, loc(A, lda, j, j), lda, loc(work, j), 1)
    mygemv!('T', m, n1, 1.0, loc(B, ldb, 1, j+1), ldb, loc(B, ldb, 1, j), 1, 1.0, 
      loc(work, j+1), 1)
    Base.LinAlg.BLAS.axpy!(n1+1, -t, loc(work, j), 1, loc(A, lda, j, j), lda)
    # unsafe_store!(loc(A, lda, j, j), a-t*a)
    myger!(m, n1, -t, loc(B, ldb, 1, j), 1, loc(work, j+1), 1, loc(B, ldb, 1, j+1), ldb)
    w = unsafe_load(loc(work,j))
    Base.LinAlg.BLAS.scal!(m, -t*w, loc(B,ldb,1,j), 1)
  end
end

# Compute Q'A for A split into nxk A and mxk B
function tpmrqrf!( m::Int64, n::Int64, k::Int64, A::Ptr{Float64}, lda::Int64,
                   B::Ptr{Float64}, ldb::Int64, 
                   V::Ptr{Float64}, ldv::Int64, work::Ptr{Float64} )
  for j = 1:n
    # Compute tau
    t = 2/(1.0+Base.LinAlg.BLAS.dot(m, loc(V, ldv, 1, j), 1, loc(V, ldv, 1, j), 1))
    Base.LinAlg.BLAS.blascopy!( k, loc(A,j), lda, work, 1 )
    mygemv!('T', m, k, 1.0, loc(B,1), ldb, loc(V,ldv,1,j), 1, 1.0, work, 1)
    Base.LinAlg.BLAS.axpy!(k, -t, work, 1, loc(A,j), lda)
    myger!(m,k,-t, loc(V,ldv,1,j), 1, work, 1, loc(B,1), ldb)
  end
end


function gemqrt!(side::Char, trans::Char, V::StridedMatrix, T::StridedMatrix, C::StridedVecOrMat)
    m, n = ndims(C)==2 ? size(C) : (size(C, 1), 1)
    nb, k = size(T)
    if k == 0 return C end
    if side == 'L'
        0 <= k <= m || throw(DimensionMismatch("Wrong value for k"))
        m == size(V,1) || throw(DimensionMismatch())
        ldv = stride(V,2)
        ldv >= max(1, m) || throw(DimensionMismatch("Q and C don't fit"))
        wss = n*k
    elseif side == 'R'
        0 <= k <= n || throw(DimensionMismatch("Wrong value for k"))
        n == size(V,1) || throw(DimensionMismatch())
        ldv = stride(V,2)
        ldv >= max(1, n) || throw(DimensionMismatch("stride error"))
        wss = m*k
    end
    1 <= nb <= k || throw(DimensionMismatch("Wrong value for nb"))
    ldc = max(1, stride(C,2))
    work = Array(Float64, wss)
    info = Array(Int64, 1)
    ccall((:dgemqrt_, Base.libblas_name), Void,
        (Ptr{UInt8}, Ptr{UInt8}, Ptr{Int64}, Ptr{Int64},
         Ptr{Int64}, Ptr{Int64}, Ptr{Float64}, Ptr{Int64},
         Ptr{Float64}, Ptr{Int64}, Ptr{Float64}, Ptr{Int64},
         Ptr{Float64}, Ptr{Int64}),
        &side, &trans, &m, &n,
        &k, &nb, V, &ldv,
        T, &max(1,stride(T,2)), C, &ldc,
        work, info)
    return C
end




A_mul_B!(A::TPQRCompactWY, B::StridedVecOrMat) = tpmqrt!(A,B)

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

function cgs!( A::StridedArray{Float64,2}, R::StridedArray{Float64,2} )
  m,n = size(A)
  R[1,1] = norm(sub(A,:,1))
  scale!(sub(A,:,1),1/R[1,1])
  for k = 2:n
    Base.LinAlg.BLAS.gemv!( 'T', 1.0, sub(A,:,1:k-1), sub(A,:,k), 0.0, sub(R,1:k-1,k) )
    Base.LinAlg.BLAS.gemv!( 'N', -1.0, sub(A,:,1:k-1), sub(R,1:k-1,k), 1.0, sub(A,:,k) )
    R[k,k] = norm(sub(A,:,k))
    scale!(sub(A,:,k),1/R[k,k])
  end
  return A,R
end

function cgs!( A::StridedArray{Float64,2} )
  m,n = size(A)
  return cgs!( A, zeros(n,n) )
end

function bgs!( A::StridedArray{Float64,2} )
  m,n = size(A)
  nb = 32
  R = zeros(n,n)
  for b = 1:nb:n
    t = min(b+nb-1,n)
    Q, R11 = cgs!( sub(A,:,b:t), sub(R,b:t,b:t) )
    if t != n
      Base.LinAlg.BLAS.gemm!('T','N', 1.0, Q, sub(A,:,t+1:n), 0.0, sub(R,b:t,t+1:n))
      Base.LinAlg.BLAS.gemm!('N','N', -1.0, Q, sub(R,b:t,t+1:n), 1.0, sub(A,:,t+1:n))
    end
  end
  return A,R
end

function dhamm!( A::StridedArray{Float64,2}, 
                 B::StridedArray{Float64,2}, 
                 C::StridedArray{Float64,2} )
  m,n = size(A)
  if n == 1
    #for j = 1:n
    #  for i = 1:j
    #    C[i,j] = 0.0
    #    @simd for k = 1:m
    #      @inbounds C[i,j] += A[k,i]*B[k,j]
    #    end
    #  end
    #end
    C[1,1] = Base.LinAlg.BLAS.dot(m,pointer(A),1,pointer(B),1)
  else
    n1 = div(n,2)
    dhamm!( sub(A,:,1:n1), sub(B,:,1:n1), sub(C,1:n1,1:n1) )
    Base.LinAlg.BLAS.gemm!('T', 'N', 1.0, sub(A,:,1:n1), sub(B,:,n1+1:n), 0.0, sub(C,1:n1,n1+1:n))
    dhamm!( sub(A,:,n1+1:n), sub(B,:,n1+1:n), sub(C,n1+1:n,n1+1:n) )
  end
  return C
end
