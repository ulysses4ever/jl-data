btsqr!( A, B::Array{Float64,2} ) = btsqr!(A, B, zeros(size(A)...))

macro timeit(ex)
  quote
    local t0 = time_ns()
    $(esc(ex))
    (time_ns() - t0)/1e9
  end
end

function btsqr!( A, B::Array{Float64,2}, BA::Array{Float64,2} )
  m,n = size(A)
  U, Z = shtsqr!(A)
  U = constructQ!( U )
  blas_set_num_threads( nworkers() )
  # M = zeros(n,n)
  # Base.LinAlg.BLAS.symm!( 'L', 'U', 1.0, B, U.s, 0.0, BA )
  # Base.LinAlg.BLAS.gemm!( 'T', 'N', 1.0, U.s, BA, 0.0, M )
  M = U'*B*U
  cholfact!(M)
  Base.LinAlg.BLAS.trsm!( 'R', 'U', 'N', 'N', 1.0, M, U )
  Base.LinAlg.BLAS.trmm!( 'L', 'U', 'N', 'N', 1.0, M, Z )
  blas_set_num_threads( 1 )
  U, Z
end

function bgsBQR!( A::SharedArray,
                 B::SparseMatrixCSC,
                 C::SharedArray,
                 M::Array )
  m,n = size(A)
  blas_set_num_threads(nworkers())
  Q,R = TallSkinnyQR.bgs!(sdata(A))
  mkl_cscsymm!(sdata(C), B, Q)
  Base.LinAlg.BLAS.gemm!('T','N', 1.0, Q, sdata(C), 0.0, M)
  Base.LinAlg.LAPACK.potrf!('U', M)
  Base.LinAlg.BLAS.trsm!('R','U','N','N', 1.0, M, Q)
  Base.LinAlg.BLAS.trmm!('L','U','N','N', 1.0, M, R)
  blas_set_num_threads(1)
  return R
end


function lapack_bqr( A::SharedArray, 
                    B::SparseMatrixCSC, 
                    C::SharedArray,
                    M::Array)
  m,n = size(A)
  blas_set_num_threads(nworkers())
  R = zeros(n,n)
  W1 = zeros(n,n)
  W,S = Base.LinAlg.LAPACK.geqrt!(sdata(A), n)
  V = sdata(C)
  for j = 1:n
    @simd for i = 1:j
      @inbounds R[i,j] = W[i,j]
      @inbounds W[i,j] = 0.0
    end
    @inbounds W[j,j] = 1.0
    @simd for i = j:n
      @inbounds W1[i,j] = W[i,j]
    end
  end

  Base.LinAlg.BLAS.trmm!( 'R', 'U', 'N', 'N', 1.0, S, W)
  mkl_cscsymm!( V, B, W )
  Base.LinAlg.BLAS.gemm!( 'T', 'N', 0.5, V, W, 0.0, M )
  Base.LinAlg.BLAS.gemm!( 'N', 'N', -1.0, W1, M, 1.0, sub(V, 1:n, 1:n))
  for j = 1:n
    for i = 1:j
      if B[i,j] == 0.0
        M[i,j] = 0
      else
        M[i,j] = B[i,j]
      end
    end
  end
  Base.LinAlg.BLAS.syr2k!( 'U', 'N', -1.0, sub(V, 1:n, 1:n), W1, 1.0, M )
  Base.LinAlg.LAPACK.potrf!( 'U', M )
  Base.LinAlg.BLAS.trsm!( 'L', 'U', 'T', 'N', 1.0, M, W1 )
  Base.LinAlg.BLAS.trmm!( 'R', 'L', 'T', 'N', -1.0, W1, W )
  Base.LinAlg.BLAS.trmm!( 'L', 'U', 'N', 'N', 1.0, M, R )
  Base.LinAlg.LAPACK.trtri!( 'U', 'N', M )
  for j = 1:n
    @simd for i = 1:j
      @inbounds W[i,j] = M[i,j] + W[i,j]
    end
  end
  blas_set_num_threads(1)
  return R
end


function SimpleBQR!( A::SharedArray, 
                 B::SparseMatrixCSC,
                 C::SharedArray,
                 M::Array )
  m,n = size(A)
  U, Z = shtsqr!(A)
  U = constructQ!( U )
  
  blas_set_num_threads( nworkers() )

  # C := B*U
  mkl_cscsymm!( sdata(C), B, sdata(U) )

  # M := U'*C
  Base.LinAlg.BLAS.gemm!( 'T', 'N', 1.0, U.s, C, 0.0, M )

  Base.LinAlg.LAPACK.potrf!('U', M)

  # Q := U/M, R := M*Z
  Base.LinAlg.BLAS.trsm!( 'R', 'U', 'N', 'N', 1.0, M, U )
  Base.LinAlg.BLAS.trmm!( 'L', 'U', 'N', 'N', 1.0, M, Z )

  blas_set_num_threads( 1 )
  return Z
end

function CholBQR!( A::SharedArray,
                   B::SparseMatrixCSC,
                   C::SharedArray,
                   M::Array )
  m,n = size(A)

  blas_set_num_threads( nworkers() )
  # C := B*A
  mkl_cscsymm!( sdata(C), B, sdata(A) )
  
  # M := A'*C
  Base.LinAlg.BLAS.gemm!( 'T', 'N', 1.0, A, C, 0.0, M )
  Base.LinAlg.LAPACK.potrf!( 'U', M )
  Base.LinAlg.BLAS.trsm!( 'R', 'U', 'N', 'N', 1.0, M, A )
  blas_set_num_threads( 1 )
  return triu(M)
end

function caBQR!( A::SharedArray,
                 B::SparseMatrixCSC,
                 C::SharedArray,
                 M::Array )
  m,n = size(A)
  Z = shtsqr(A)
  
  blas_set_num_threads( nworkers() )

  Base.LinAlg.BLAS.trsm!( 'R', 'U', 'N', 'N', 1.0, Z, A )

  mkl_cscsymm!( sdata(C), B, sdata(A) )

  Base.LinAlg.BLAS.gemm!( 'T', 'N', 1.0, A, C, 0.0, M )
  Base.LinAlg.LAPACK.potrf!( 'U', M )
  Base.LinAlg.BLAS.trsm!( 'R', 'U', 'N', 'N', 1.0, M, A )
  Base.LinAlg.BLAS.trmm!( 'L', 'U', 'N', 'N', 1.0, M, Z )

  blas_set_num_threads( 1 )
  return Z
end

function lapack_bqr( A::SharedArray, 
                    B::SparseMatrixCSC, 
                    C::SharedArray,
                    M::Array,
                    timing::Bool)
  m,n = size(A)
  local W,S
  tqr,tmm,tsp,tch = 0.0,0.0,0.0,0.0
  blas_set_num_threads(nworkers())
  R = zeros(n,n)
  W1 = zeros(n,n)
  tqr += @timeit W,S = Base.LinAlg.LAPACK.geqrt!(sdata(A), n)
  V = sdata(C)
  for j = 1:n
    @simd for i = 1:j
      @inbounds R[i,j] = W[i,j]
      @inbounds W[i,j] = 0.0
    end
    @inbounds W[j,j] = 1.0
    @simd for i = j:n
      @inbounds W1[i,j] = W[i,j]
    end
  end

  tmm += @timeit Base.LinAlg.BLAS.trmm!( 'R', 'U', 'N', 'N', 1.0, S, W)
  tsp += @timeit mkl_cscsymm!( V, B, W )
  tmm += @timeit Base.LinAlg.BLAS.gemm!( 'T', 'N', 0.5, V, W, 0.0, M )
  tmm += @timeit Base.LinAlg.BLAS.gemm!( 'N', 'N', -1.0, W1, M, 1.0, sub(V, 1:n, 1:n))
  for j = 1:n
    for i = 1:j
      if B[i,j] == 0.0
        M[i,j] = 0
      else
        M[i,j] = B[i,j]
      end
    end
  end
  tmm += @timeit Base.LinAlg.BLAS.syr2k!( 'U', 'N', -1.0, sub(V, 1:n, 1:n), W1, 1.0, M )
  tch += @timeit Base.LinAlg.LAPACK.potrf!( 'U', M )
  tmm += @timeit Base.LinAlg.BLAS.trsm!( 'L', 'U', 'T', 'N', 1.0, M, W1 )
  tmm += @timeit Base.LinAlg.BLAS.trmm!( 'R', 'L', 'T', 'N', -1.0, W1, W )
  tmm += @timeit Base.LinAlg.BLAS.trmm!( 'L', 'U', 'N', 'N', 1.0, M, R )
  tmm += @timeit Base.LinAlg.LAPACK.trtri!( 'U', 'N', M )
  tmm += @timeit for j = 1:n
    @simd for i = 1:j
      @inbounds W[i,j] = M[i,j] + W[i,j]
    end
  end
  blas_set_num_threads(1)
  return [tqr,tsp,tmm,tch]
end


function SimpleBQR!( A::SharedArray, 
                 B::SparseMatrixCSC,
                 C::SharedArray,
                 M::Array,
                 timing::Bool)
  m,n = size(A)
  local U,Z
  tqr,tmm,tsp,tch = 0.0,0.0,0.0,0.0
  tqr += @timeit U, Z = shtsqr!(A)
  tqr += @timeit U = constructQ!( U )
  
  blas_set_num_threads( nworkers() )

  # C := B*U
  tsp += @timeit mkl_cscsymm!( sdata(C), B, sdata(U) )

  # M := U'*C
  tmm += @timeit Base.LinAlg.BLAS.gemm!( 'T', 'N', 1.0, U.s, C, 0.0, M )

  tch += @timeit Base.LinAlg.LAPACK.potrf!('U', M)

  # Q := U/M, R := M*Z
  tmm += @timeit Base.LinAlg.BLAS.trsm!( 'R', 'U', 'N', 'N', 1.0, M, U )
  tmm += @timeit Base.LinAlg.BLAS.trmm!( 'L', 'U', 'N', 'N', 1.0, M, Z )

  blas_set_num_threads( 1 )
  return [tqr,tsp,tmm,tch]
end

function CholBQR!( A::SharedArray,
                   B::SparseMatrixCSC,
                   C::SharedArray,
                   M::Array,
                   timing::Bool)
  m,n = size(A)
  tqr,tsp,tmm,tch = 0.0,0.0,0.0,0.0

  blas_set_num_threads( nworkers() )
  # C := B*A
  tsp += @timeit mkl_cscsymm!( sdata(C), B, sdata(A) )
  
  # M := A'*C
  tmm += @timeit Base.LinAlg.BLAS.gemm!( 'T', 'N', 1.0, A, C, 0.0, M )
  tch += @timeit Base.LinAlg.LAPACK.potrf!( 'U', M )
  tmm += @timeit Base.LinAlg.BLAS.trsm!( 'R', 'U', 'N', 'N', 1.0, M, A )
  blas_set_num_threads( 1 )
  return [tqr,tsp,tmm,tch]
end

function caBQR!( A::SharedArray,
                 B::SparseMatrixCSC,
                 C::SharedArray,
                 M::Array,
                 timing::Bool)
  m,n = size(A)
  local Z
  tqr,tsp,tmm,tch = 0.0,0.0,0.0,0.0
  tqr += @timeit Z = shtsqr(A)
  
  blas_set_num_threads( nworkers() )

  tmm += @timeit Base.LinAlg.BLAS.trsm!( 'R', 'U', 'N', 'N', 1.0, Z, A )

  tsp += @timeit mkl_cscsymm!( sdata(C), B, sdata(A) )

  tmm += @timeit Base.LinAlg.BLAS.gemm!( 'T', 'N', 1.0, A, C, 0.0, M )
  tch += @timeit Base.LinAlg.LAPACK.potrf!( 'U', M )
  tmm += @timeit Base.LinAlg.BLAS.trsm!( 'R', 'U', 'N', 'N', 1.0, M, A )
  tmm += @timeit Base.LinAlg.BLAS.trmm!( 'L', 'U', 'N', 'N', 1.0, M, Z )

  blas_set_num_threads( 1 )
  return [tqr,tsp,tmm,tch]
end


















# Do sparse plus low-rank thing B = S + UU'
function caBQR!( A::SharedArray,
                 B::SparseMatrixCSC,
                 C::SharedArray,
                 M::Array,
                 U::SharedArray )
  m,n = size(A)
  k   = size(U)[2]
  Z   = shtsqr(A)

  blas_set_num_threads( nworkers() )

  # A := A/Z
  Base.LinAlg.BLAS.trsm!( 'R', 'U', 'N', 'N', 1.0, Z, A )

  # M := A'BA
  mkl_cscsymm!( sdata(C), B, sdata(A) )
  Base.LinAlg.BLAS.gemm!( 'T', 'N', 1.0, A, C, 0.0, M )

  # M := M + A'UU'A
  M2 = sub(sdata(C), 1:k, 1:n)
  Base.LinAlg.BLAS.gemm!( 'T', 'N', 1.0, U, A, 0.0, M2 )
  Base.LinAlg.BLAS.syrk!( 'U', 'T', 1.0, M2, 1.0, M )

  Base.LinAlg.LAPACK.potrf!('U',M)
  Base.LinAlg.BLAS.trsm!( 'R', 'U', 'N', 'N', 1.0, M, A )
  Base.LinAlg.BLAS.trmm!( 'L', 'U', 'N', 'N', 1.0, M, Z )

  blas_set_num_threads( 1 )
  return Z
end
