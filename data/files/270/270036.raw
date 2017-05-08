function SCBQR!( A::SharedArray, 
                 B::SparseMatrixCSC,
                 C::SharedArray,
                 M::Array )
  m,n = size(A)
  U, Z = tsqr!(A)
  U = constructQ!( U )
  
  blas_set_num_threads( nworkers() )

  # C := B*U
  mkl_cscsymm!( sdata(C), B, sdata(U) )

  # M := U'*C
  BLAS.gemm!( 'T', 'N', 1.0, U.s, C, 0.0, M )

  LAPACK.potrf!('U', M)

  # Q := U/M, R := M*Z
  BLAS.trsm!( 'R', 'U', 'N', 'N', 1.0, M, U )
  BLAS.trmm!( 'L', 'U', 'N', 'N', 1.0, M, Z )

  blas_set_num_threads( 1 )
  return Z
end

function CBQR!( A::SharedArray,
                B::SparseMatrixCSC,
                C::SharedArray,
                M::Array )
  m,n = size(A)

  blas_set_num_threads( nworkers() )
  # C := B*A
  mkl_cscsymm!( sdata(C), B, sdata(A) )
  
  # M := A'*C
  BLAS.gemm!( 'T', 'N', 1.0, A, C, 0.0, M )
  # Cholesky factorize M
  LAPACK.potrf!( 'U', M )
  # A := A/M
  BLAS.trsm!( 'R', 'U', 'N', 'N', 1.0, M, A )
  blas_set_num_threads( 1 )
  return triu(M)
end

function SCBQRT!( A::SharedArray,
                  B::SparseMatrixCSC,
                  C::SharedArray,
                  M::Array )
  m,n = size(A)
  Z = tsqr(A)
  
  blas_set_num_threads( nworkers() )

  BLAS.trsm!( 'R', 'U', 'N', 'N', 1.0, Z, A )

  mkl_cscsymm!( sdata(C), B, sdata(A) )

  BLAS.gemm!( 'T', 'N', 1.0, A, C, 0.0, M )
  LAPACK.potrf!( 'U', M )
  BLAS.trsm!( 'R', 'U', 'N', 'N', 1.0, M, A )
  BLAS.trmm!( 'L', 'U', 'N', 'N', 1.0, M, Z )

  blas_set_num_threads( 1 )
  return Z
end
