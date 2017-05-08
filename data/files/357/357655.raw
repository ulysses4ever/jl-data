import Base: *, A_mul_B!, Ac_mul_B!, At_mul_B!

type SparseMatrixCSR{Tv,Ti<:Integer} <: AbstractSparseMatrix{Tv,Ti}
    m::Int                  # Number of rows
    n::Int                  # Number of columns
    rowptr::Vector{Ti}      # Row i is in rowptr[i]:(rowptr[i+1]-1)
    colval::Vector{Ti}      # Column values of nonzeros
    nzval::Vector{Tv}       # Nonzero values
end

# constructor in the form of `sparse(I, J, V, m, n, combine) -> CSC` in Base
function SparseMatrixCSR{Tv,Ti<:Integer}(I::AbstractVector{Ti},
                                         J::AbstractVector{Ti},
                                         V::AbstractVector{Tv},
                                         nrow::Integer, ncol::Integer,
                                         combine::Union{Function,Base.Func}=Base.AddFun())
    # super simple solution for now. Just construct the CSC with the rows/cols
    # and I/J flipped then extract the fields
    csc = sparse(J, I, V, ncol, nrow, combine)
    rowptr = csc.colptr
    colval = csc.rowval
    nzval = csc.nzval
    SparseMatrixCSR(nrow, ncol, rowptr, colval, nzval)
end

# NOTE:  copied/pasted from base. Modified slightly
function Base.showarray(io::IO, S::SparseMatrixCSR;
                        header::Bool=true, limit::Bool=Base._limit_output,
                        rows = Base.tty_size()[1], repr=false)

    if header
        print(io, S.m, "x", S.n, " CSR sparse matrix with ", nnz(S), " ",
              eltype(S), " entries:")
    end

    if limit
        half_screen_rows = div(rows - 8, 2)
    else
        half_screen_rows = typemax(Int)
    end
    pad = ndigits(max(S.m, S.n))
    k = 0
    sep = "\n\t"
    for row = 1:S.m, k = S.rowptr[row] : (S.rowptr[row+1]-1)
        if k < half_screen_rows || k > nnz(S)-half_screen_rows
            print(io, sep, '[', rpad(row, pad), ", ", lpad(S.colval[k], pad), "]  =  ")
            showcompact(io, S.nzval[k])
        elseif k == half_screen_rows
            print(io, sep, '\u22ee')
        end
        k += 1
    end
end

Base.size(S::SparseMatrixCSR) = (S.m, S.n)
Base.nnz(S::SparseMatrixCSR) = Int(S.rowptr[end] - 1)

# NOTE:  copied/pasted from base
# for (f, op, transp) in ((:A_mul_B, :identity, false),
#                         (:Ac_mul_B, :ctranspose, true),
#                         (:At_mul_B, :transpose, true))
#     @eval begin
#         function $(symbol(f,:!)){TC}(α::Number, A::SparseMatrixCSR, B::StridedVecOrMat, β::Number, C::StridedVecOrMat{TC})
#             if $transp
#                 A.n == size(C, 1) || throw(DimensionMismatch())
#                 A.m == size(B, 1) || throw(DimensionMismatch())
#             else
#                 A.n == size(B, 1) || throw(DimensionMismatch())
#                 A.m == size(C, 1) || throw(DimensionMismatch())
#             end
#             size(B, 2) == size(C, 2) || throw(DimensionMismatch())

#             if β != 1
#                 β != 0 ? scale!(C, β) : fill!(C, zero(eltype(C)))
#             end

#             nzval = A.nzval
#             colval = A.colval
#             rowptr = A.rowptr

#             for row = 1:A.m
#                 for k = 1:size(C, 2)
#                     if $transp
#                         tmp = zero(TC)
#                         @inbounds for j = rowptr[row]:(rowptr[row+1] - 1)
#                             tmp += $(op)(nzval[j])*B[colval[j], k]
#                         end
#                         C[col, k] += α*tmp
#                     else
#                         temp = β*C[row, k]
#                         @inbounds for j = rowptr[row]:(rowptr[row+1] - 1)
#                             C[rv[j], k] += nzv[j]*αxj
#                         end
#                     end
#                 end
#             end
#             C
#         end

#         function $(f){TA,S,Tx}(A::SparseMatrixCSR{TA,S}, x::StridedVector{Tx})
#             T = promote_type(TA, Tx)
#             $(symbol(f,:!))(one(T), A, x, zero(T), similar(x, T, A.n))
#         end
#         function $(f){TA,S,Tx}(A::SparseMatrixCSR{TA,S}, B::StridedMatrix{Tx})
#             T = promote_type(TA, Tx)
#             $(symbol(f,:!))(one(T), A, B, zero(T), similar(B, T, (A.n, size(B, 2))))
#         end
#     end
# end

function A_mul_B!{T}(α::Number, A::SparseMatrixCSR, B::StridedVector, β::Number,
                     C::StridedVector{T})
    A.m == size(C, 1) || throw(DimensionMismatch())
    A.n == size(B, 1) || throw(DimensionMismatch())

    @inbounds for row=1:A.m
        temp = zero(T)
        @simd for j=A.rowptr[row]:A.rowptr[row+1]-1
            temp += B[A.colval[j]] * A.nzval[j]
        end
        C[row] = α*temp + β*C[row]
    end
    C
end

# API to be consistent with Base dense operations
A_mul_B!{T}(C::StridedVector{T}, A::SparseMatrixCSR, B::StridedVector) =
    A_mul_B!(one(T), A, B, zero(T), C)

function (*){T,S}(A::SparseMatrixCSR{T}, x::StridedVector{S})
    TS = promote_type(Base.LinAlg.arithtype(T), Base.LinAlg.arithtype(S))
    A_mul_B!(similar(x, TS, size(A, 1)), A, convert(AbstractVector{TS}, x))
end
