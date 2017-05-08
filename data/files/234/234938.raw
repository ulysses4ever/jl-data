# This file is a part of Julia. License is MIT: http://julialang.org/license

## The LAPACK module of interfaces to LAPACK subroutines
module LAPACK

const liblapack = Base.liblapack_name

import Base.@blasfunc

import Base.LinAlg: BlasFloat, Char, BlasInt, LAPACKException,
    DimensionMismatch, SingularException, PosDefException, chkstride1, checksquare

#Generic LAPACK error handlers
"""
Handle only negative LAPACK error codes

*NOTE* use only if the positive error code is useful.
"""
function chkargsok(ret::BlasInt)
    if ret < 0
        throw(ArgumentError("invalid argument #$(-ret) to LAPACK call"))
    end
end

"Handle all nonzero info codes"
function chklapackerror(ret::BlasInt)
    if ret == 0
        return
    elseif ret < 0
        throw(ArgumentError("invalid argument #$(-ret) to LAPACK call"))
    else # ret > 0
        throw(LAPACKException(ret))
    end
end

function chknonsingular(ret::BlasInt)
    if ret > 0
        throw(SingularException(ret))
    end
end

function chkposdef(ret::BlasInt)
    if ret > 0
        throw(PosDefException(ret))
    end
end

"Check that upper/lower (for special matrices) is correctly specified"
function chkuplo(uplo::Char)
    if !(uplo == 'U' || uplo == 'L')
        throw(ArgumentError("uplo argument must be 'U' (upper) or 'L' (lower), got $uplo"))
    end
    uplo
end

"Check that {c}transpose is correctly specified"
function chktrans(trans::Char)
    if !(trans == 'N' || trans == 'C' || trans == 'T')
        throw(ArgumentError("trans argument must be 'N' (no transpose), 'T' (transpose), or 'C' (conjugate transpose), got $trans"))
    end
    trans
end

"Check that left/right hand side multiply is correctly specified"
function chkside(side::Char)
    if !(side == 'L' || side == 'R')
        throw(ArgumentError("side argument must be 'L' (left hand multiply) or 'R' (right hand multiply), got $side"))
    end
    side
end

"Check that unit diagonal flag is correctly specified"
function chkdiag(diag::Char)
    if !(diag == 'U' || diag =='N')
        throw(ArgumentError("diag argument must be 'U' (unit diagonal) or 'N' (non-unit diagonal), got $diag"))
    end
    diag
end

subsetrows(X::AbstractVector, Y::AbstractArray, k) = Y[1:k]
subsetrows(X::AbstractMatrix, Y::AbstractArray, k) = Y[1:k, :]

function chkfinite(A::StridedMatrix)
    for a in A
        if !isfinite(a)
            throw(ArgumentError("matrix contains Infs or NaNs"))
        end
    end
    return true
end

# LAPACK version number
function laver()
    major = Ref{BlasInt}(0)
    minor = Ref{BlasInt}(0)
    patch = Ref{BlasInt}(0)
    ccall((@blasfunc(ilaver_), liblapack), Void,
        (Ptr{BlasInt}, Ptr{BlasInt}, Ptr{BlasInt}),
        major, minor, patch)
    return major[], minor[], patch[]
end

## (ST) Symmetric tridiagonal - eigendecomposition
for (stev, stebz, stegr, stein, elty) in
    ((:dstev_,:dstebz_,:dstegr_,:dstein_,:Float64),
     (:sstev_,:sstebz_,:sstegr_,:sstein_,:Float32)
#     , (:zstev_,:Complex128)  Need to rewrite for ZHEEV, rwork, etc.
#     , (:cstev_,:Complex64)
     )
    @eval begin
        function stev_work(job::Char, dv::Vector{$elty}, ev::Vector{$elty})
            n = length(dv)
            if length(ev) != n - 1
                throw(DimensionMismatch("ev has length $(length(ev)) but needs one less than dv's length, $n)"))
            end

            Zmat = similar(dv, $elty, (n, job != 'N' ? n : 0))
            work = Array($elty, max(1, 2n-2))

            info = Ref{BlasInt}()

            Zmat, work, info
        end

        function stev!(job::Char, dv::AbstractVector{$elty}, ev::AbstractVector{$elty},
                       Zmat::StridedMatrix{$elty}, work::Array{$elty}, info::Ref{BlasInt})
            n = length(dv)

            ldz = stride(Zmat, 2)

            ccall((@blasfunc($stev), liblapack), Void,
                  (Ptr{UInt8}, Ptr{BlasInt}, Ptr{$elty}, Ptr{$elty}, Ptr{$elty},
                   Ptr{BlasInt}, Ptr{$elty}, Ptr{BlasInt}),
                  &job, &n, dv, ev, Zmat, &ldz, work, info)
            chklapackerror(info[])
        end

        function stev!(job::Char, dv::Vector{$elty}, ev::Vector{$elty})
            Zmat, work, info = stev_work(job, dv, ev)

            stev!(job, dv, ev, Zmat, work, info)
            dv, Zmat
        end

        function stegr_work(jobz::Char, range::Char, dv::Vector{$elty}, eev::Vector{$elty}, vl::Real, vu::Real, il::Integer, iu::Integer)
            n = length(dv)
            if length(eev) != n
                throw(DimensionMismatch("eev must have the same length as dv, the last element does not have to initialized."))
            end

            abstol = Array($elty, 1)
            m = Array(BlasInt, 1)
            w = similar(dv, $elty, n)
            ldz = jobz == 'N' ? 1 : n
            Z = similar(dv, $elty, ldz, n)
            isuppz = similar(dv, BlasInt, 2n)
            work = Array($elty, 1)
            lwork = BlasInt(-1)
            iwork = Array(BlasInt, 1)
            liwork = BlasInt(-1)

            info = Ref{BlasInt}()

            ccall((@blasfunc($stegr), liblapack), Void,
                  (Ptr{UInt8}, Ptr{UInt8}, Ptr{BlasInt}, Ptr{$elty},
                   Ptr{$elty}, Ptr{$elty}, Ptr{$elty}, Ptr{BlasInt},
                   Ptr{BlasInt}, Ptr{$elty}, Ptr{BlasInt}, Ptr{$elty},
                   Ptr{$elty}, Ptr{BlasInt}, Ptr{BlasInt}, Ptr{$elty},
                   Ptr{BlasInt}, Ptr{BlasInt}, Ptr{BlasInt}, Ptr{BlasInt}),
                  &jobz, &range, &n, dv,
                  eev, &vl, &vu, &il,
                  &iu, abstol, m, w,
                  Z, &ldz, isuppz, work,
                  &lwork, iwork, &liwork, info)
            chklapackerror(info[])
            lwork = BlasInt(work[1])
            work = Array($elty, lwork)
            liwork = iwork[1]
            iwork = Array(BlasInt, liwork)

            abstol, m, w, Z, isuppz, work, lwork, iwork, liwork, info
        end

        function stegr!(jobz::Char, range::Char,
                        dv::AbstractVector{$elty}, eev::AbstractVector{$elty},
                        vl::Real, vu::Real, il::Integer, iu::Integer,
                        abstol::Array{$elty}, m::Array{BlasInt}, w::Vector{$elty}, Z::StridedMatrix{$elty},
                        isuppz::Vector{BlasInt},
                        work::Array{$elty}, lwork::BlasInt,
                        iwork::Array{BlasInt}, liwork::BlasInt,
                        info::Ref{BlasInt})
            n = length(dv)

            ldz = stride(Z, 2)

            ccall((@blasfunc($stegr), liblapack), Void,
                  (Ptr{UInt8}, Ptr{UInt8}, Ptr{BlasInt}, Ptr{$elty},
                   Ptr{$elty}, Ptr{$elty}, Ptr{$elty}, Ptr{BlasInt},
                   Ptr{BlasInt}, Ptr{$elty}, Ptr{BlasInt}, Ptr{$elty},
                   Ptr{$elty}, Ptr{BlasInt}, Ptr{BlasInt}, Ptr{$elty},
                   Ptr{BlasInt}, Ptr{BlasInt}, Ptr{BlasInt}, Ptr{BlasInt}),
                  &jobz, &range, &n, dv,
                  eev, &vl, &vu, &il,
                  &iu, abstol, m, w,
                  Z, &ldz, isuppz, work,
                  &lwork, iwork, &liwork, info)
            chklapackerror(info[])
        end

        function stegr!(jobz::Char, range::Char, dv::Vector{$elty}, ev::Vector{$elty}, vl::Real, vu::Real, il::Integer, iu::Integer)
            n = length(dv)
            if length(ev) != n - 1
                throw(DimensionMismatch("ev has length $(length(ev)) but needs one less than dv's length, $n)"))
            end
            eev = [ev; zero($elty)]

            abstol, m, w, Z, isuppz, work, lwork, iwork, liwork, info = stegr_work(jobz, range, dv, eev, vl, vu, il, iu)

            info = Ref{BlasInt}()

            stegr!(jobz, range, dv, eev, vl, vu, il, iu, abstol, m, w, Z, isuppz, work, lwork, iwork, liwork,info)

            w[1:m[1]], Z[:,1:m[1]]
        end
    end
end
stegr!(jobz::Char, dv::Vector, ev::Vector) = stegr!(jobz, 'A', dv, ev, 0.0, 0.0, 0, 0)

"""
    stev!(job, dv, ev) -> (dv, Zmat)

Computes the eigensystem for a symmetric tridiagonal matrix with `dv` as
diagonal and `ev` as off-diagonal. If `job = N` only the eigenvalues are
found and returned in `dv`. If `job = V` then the eigenvectors are also found
and returned in `Zmat`.
"""
stev!(job::Char, dv::Vector, ev::Vector)

"""
    stegr!(jobz, range, dv, ev, vl, vu, il, iu) -> (w, Z)

Computes the eigenvalues (`jobz = N`) or eigenvalues and eigenvectors
(`jobz = V`) for a symmetric tridiagonal matrix with `dv` as diagonal
and `ev` as off-diagonal. If `range = A`, all the eigenvalues
are found. If `range = V`, the eigenvalues in the half-open interval
`(vl, vu]` are found. If `range = I`, the eigenvalues with indices between
`il` and `iu` are found. The eigenvalues are returned in `w` and the eigenvectors
in `Z`.
"""
stegr!(jobz::Char, range::Char, dv::Vector, ev::Vector, vl::Real, vu::Real, il::Integer, iu::Integer)

end # module
