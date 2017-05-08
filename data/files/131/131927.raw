# Some extra LAPACK functions not defined in Base.


const liblapack = Base.liblapack_name

import Base.LinAlg: BlasFloat, BlasChar, BlasInt, blas_int, LAPACKException,
    DimensionMismatch, SingularException, PosDefException, chkstride1, chksquare

#Generic LAPACK error handlers
macro assertargsok() #Handle only negative info codes - use only if positive info code is useful!
    :(info[1]<0 && throw(ArgumentError("invalid argument #$(-info[1]) to LAPACK call")))
end
macro lapackerror() #Handle all nonzero info codes
    :(info[1]>0 ? throw(LAPACKException(info[1])) : @assertargsok )
end

macro assertnonsingular()
    :(info[1]>0 && throw(SingularException(info[1])))
end
macro assertposdef()
    :(info[1]>0 && throw(PosDefException(info[1])))
end

#Check that upper/lower (for special matrices) is correctly specified
macro chkuplo()
    :((uplo=='U' || uplo=='L') || throw(ArgumentError("""invalid uplo = $uplo

Valid choices are 'U' (upper) or 'L' (lower).""")))
end

num_packed(np) = div(-1 + isqrt(1+8*np), 2)


    

# (PO) positive-definite symmetric matrices,
# Cholesky decomposition, solvers (direct and factored) and inverse.
for (ppsv, pptrf, pptri, pptrs, elty, rtyp) in
    ((:dppsv_,:dpptrf_,:dpptri_,:dpptrs_,:Float64,:Float64),
     (:sppsv_,:spptrf_,:spptri_,:spptrs_,:Float32,:Float32),
     (:zppsv_,:zpptrf_,:zpptri_,:zpptrs_,:Complex128,:Float64),
     (:cppsv_,:cpptrf_,:cpptri_,:cpptrs_,:Complex64,:Float32))
    @eval begin
        #       SUBROUTINE DPPSV( UPLO, N, NRHS, AP, B, LDB, INFO )
        #       .. Scalar Arguments ..
        #       CHARACTER          UPLO
        #       INTEGER            INFO, LDB, N, NRHS
        #       ..
        #       .. Array Arguments ..
        #       DOUBLE PRECISION   AP( * ), B( LDB, * )
        function ppsv!(uplo::BlasChar, A::StridedVector{$elty}, B::StridedVecOrMat{$elty})
            chkstride1(A, B)
            n = size(B,1) 
            @chkuplo
            if size(B,1) != n throw(DimensionMismatch("ppsv!")) end
            info    = Array(BlasInt, 1)
            ccall(($(string(ppsv)),liblapack), Void,
                  (Ptr{BlasChar}, Ptr{BlasInt}, Ptr{BlasInt}, Ptr{$elty}, 
                   Ptr{$elty}, Ptr{BlasInt}, Ptr{BlasInt}),
                  &uplo, &n, &size(B,2), A, B, &max(1,stride(B,2)), info)
            @assertargsok
            @assertposdef
            A, B
        end
        #       SUBROUTINE DPPTRF( UPLO, N, AP, INFO )
        # 
        #       .. Scalar Arguments ..
        #       CHARACTER          UPLO
        #       INTEGER            INFO, N
        #       ..
        #       .. Array Arguments ..
        #       DOUBLE PRECISION   AP( * )
        function pptrf!(uplo::BlasChar, A::StridedVector{$elty})
            chkstride1(A)
            @chkuplo
            info = Array(BlasInt, 1)
            n = Array(BlasInt,1)
            n[1] = num_packed(length(A))
            
            ccall(($(string(pptrf)),liblapack), Void,
                  (Ptr{BlasChar}, Ptr{BlasInt}, Ptr{$elty}, Ptr{BlasInt}),
                  &uplo, n, A, info)
            @assertargsok
            #info[1]>0 means the leading minor of order info[i] is not positive definite
            #ordinarily, throw Exception here, but return error code here
            #this simplifies isposdef! and factorize!
            return A, info[1]
        end
        #       SUBROUTINE DPPTRI( UPLO, N, AP, INFO )
        # 
        #       .. Scalar Arguments ..
        #       CHARACTER          UPLO
        #       INTEGER            INFO, N
        #       ..
        #       .. Array Arguments ..
        #       DOUBLE PRECISION   AP( * )        

        function pptri!(uplo::BlasChar, A::StridedVector{$elty})
            @chkuplo
            info = Array(BlasInt, 1)
            n = Array(BlasInt, 1)
            n[1] = num_packed(length(A))
            ccall(($(string(pptri)),liblapack), Void,
                  (Ptr{BlasChar}, Ptr{BlasInt}, Ptr{$elty}, Ptr{BlasInt}),
                  &uplo, n, A, info)
            @assertargsok
            @assertnonsingular
            A
        end
        #       SUBROUTINE DPPTRS( UPLO, N, NRHS, AP, B, LDB, INFO )
        # 
        #       .. Scalar Arguments ..
        #       CHARACTER          UPLO
        #       INTEGER            INFO, LDB, N, NRHS
        #       ..
        #       .. Array Arguments ..
        #       DOUBLE PRECISION   AP( * ), B( LDB, * )
        #     SUBROUTINE DPOTRS( UPLO, N, NRHS, A, LDA, B, LDB, INFO )
        #     .. Scalar Arguments ..
        #      CHARACTER          UPLO
        #      INTEGER            INFO, LDA, LDB, N, NRHS
        #     .. Array Arguments ..
        #      DOUBLE PRECISION   A( LDA, * ), B( LDB, * )
        function pptrs!(uplo::BlasChar, A::StridedVector{$elty}, B::StridedVecOrMat{$elty})
            chkstride1(A, B)
            n = Array(BlasInt,1)
            n[1] = num_packed(length(A))
            
            @chkuplo
            nrhs = size(B,2)
            if size(B,1) != n[1] throw(DimensionMismatch("left and right hand sides do not fit")) end
            ldb = max(1,stride(B,2))
            info = Array(BlasInt, 1)
            ccall(($(string(pptrs)),liblapack), Void,
                  (Ptr{BlasChar}, Ptr{BlasInt}, Ptr{BlasInt}, Ptr{$elty}, 
                    Ptr{$elty}, Ptr{BlasInt}, Ptr{BlasInt}),
                   &uplo, n, &nrhs, A, 
                   B, &ldb, info)
            @lapackerror
            return B
        end
    end
end






for (pbtrf, pbtrs, elty) in
    ((:dpbtrf_,:dpbtrs_,:Float64),
     (:spbtrf_,:spbtrs_,:Float32),
     (:zpbtrf_,:zpbtrs_,:Complex128),
     (:cpbtrf_,:cpbtrs_,:Complex64))
    @eval begin
        #       SUBROUTINE DPBTRF( UPLO, N, KD, AB, LDAB, INFO )
        # 
        #       .. Scalar Arguments ..
        #       CHARACTER          UPLO
        #       INTEGER            INFO, KD, LDAB, N
        #       ..
        #       .. Array Arguments ..
        #       DOUBLE PRECISION   AB( LDAB, * )
        function pbtrf!(uplo::BlasChar, kd::Integer, AB::StridedMatrix{$elty})
            @chkuplo
            chkstride1(AB)
            info = Array(BlasInt, 1)
            n    = size(AB, 2)
            ccall(($(string(pbtrf)),liblapack), Void,
                  (Ptr{BlasChar}, Ptr{BlasInt}, Ptr{BlasInt}, 
                   Ptr{$elty}, Ptr{BlasInt}, Ptr{BlasInt}),
                  &uplo, &n, &kd, AB, &max(1,stride(AB,2)), info)
            @lapackerror
            AB
        end

        #       SUBROUTINE DPBTRS( UPLO, N, KD, NRHS, AB, LDAB, B, LDB, INFO )
        # 
        #       .. Scalar Arguments ..
        #       CHARACTER          UPLO
        #       INTEGER            INFO, KD, LDAB, LDB, N, NRHS
        #       ..
        #       .. Array Arguments ..
        #       DOUBLE PRECISION   AB( LDAB, * ), B( LDB, * )
        function pbtrs!(uplo::BlasChar, kd::Integer, 
                        AB::StridedMatrix{$elty}, B::StridedVecOrMat{$elty})
            @chkuplo
            chkstride1(AB, B)
            info = Array(BlasInt, 1)
            n    = size(AB,2)
            if n != size(B,1) throw(DimensionMismatch("pbtrs!")) end
            ccall(($(string(pbtrs)),liblapack), Void,
                  (Ptr{BlasChar}, Ptr{BlasInt}, Ptr{BlasInt}, Ptr{BlasInt}, 
                   Ptr{$elty}, Ptr{BlasInt}, Ptr{$elty},   Ptr{BlasInt},
                   Ptr{BlasInt}),
                  &uplo, &n, &kd, &size(B,2), AB, &max(1,stride(AB,2)), 
                  B, &max(1,stride(B,2)), info)
            @lapackerror
            B
        end
    end
end
