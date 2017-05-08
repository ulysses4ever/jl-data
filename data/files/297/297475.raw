import Base: *, A_mul_B!, Ac_mul_B!, At_mul_B!
import Base: getindex, setindex!

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


# algorithm based on scipy/sparse/sparsetools/csr.h
function csr2csc{Tv,Ti}(indptr::Vector{Ti}, indval::Vector{Ti},
                        nzval::Vector{Tv}, m::Int, n::Int)
    # allocate
    Bptr = zeros(Ti, n+1)
    Bind = similar(indval)
    Bval = similar(nzval)

    numnz = indptr[m]

    # get colptr by accumulating hits on colval and doing cumsum
    @inbounds Bptr[1] = 1
    @inbounds for n=1:numnz Bptr[indval[n]+1] += 1 end
    Bptr = cumsum(Bptr)

    @inbounds for row=1:m
        for j=indptr[row]:(indptr[row+1]-1)
            col = indval[j]
            dest = Bptr[col]

            Bind[dest] = row
            Bval[dest] = nzval[j]
            Bptr[col] += 1
        end
    end

    # fix up Bp
    last = 1
    @inbounds for col=1:n
        temp = Bptr[col]
        Bptr[col] = last
        last = temp
    end
    Bptr, Bind, Bval
end

function Base.convert{Tv,Ti<:Integer}(::Type{SparseMatrixCSC{Tv,Ti}},
                                      A::SparseMatrixCSR{Tv,Ti})
    Bptr, Bind, Bval = csr2csc(A.rowptr, A.colval, A.nzval, A.m, A.n)
    SparseMatrixCSC(A.m, A.n, Bptr, Bind, Bval)
end

function Base.convert{Tv,Ti<:Integer}(::Type{SparseMatrixCSR{Tv,Ti}},
                                      B::SparseMatrixCSC{Tv,Ti})
    Aptr, Aind, Aval = csr2csc(B.colptr, B.rowval, B.nzval, B.n, B.m)
    SparseMatrixCSR(B.m, B.n, Aptr, Aind, Aval)
end

Base.size(S::SparseMatrixCSR) = (S.m, S.n)
Base.nnz(S::SparseMatrixCSR) = Int(S.rowptr[end] - 1)

function A_mul_B!{T}(α::Number, A::SparseMatrixCSR, B::StridedVecOrMat,
                     β::Number, C::StridedVecOrMat{T})
    A.m == size(C, 1) || throw(DimensionMismatch("size(C, 1) != size(A, 1)"))
    A.n == size(B, 1) || throw(DimensionMismatch("size(B, 1) != size(A, 2)"))
    size(C, 2) == size(B, 2) || throw(DimensionMismatch("size(C, 2) != size(B, 2)"))

    @inbounds begin
        for k=1:size(C, 2)
            for row=1:A.m
                temp = zero(T)
                @simd for j=A.rowptr[row]:A.rowptr[row+1]-1
                    temp += B[A.colval[j], k] * A.nzval[j]
                end
                C[row, k] = α*temp + β*C[row, k]
            end
        end
    end  # inbounds
    C
end

# API to be consistent with Base dense operations
A_mul_B!{T}(C::StridedVecOrMat{T}, A::SparseMatrixCSR, B::StridedVecOrMat) =
    A_mul_B!(one(T), A, B, zero(T), C)

function (*){T,S}(A::SparseMatrixCSR{T}, x::StridedVector{S})
    TS = promote_type(Base.LinAlg.arithtype(T), Base.LinAlg.arithtype(S))
    A_mul_B!(similar(x, TS, size(A, 1)), A, convert(AbstractVector{TS}, x))
end

function (*){T,S}(A::SparseMatrixCSR{T}, B::StridedMatrix{S})
    TS = promote_type(Base.LinAlg.arithtype(T), Base.LinAlg.arithtype(S))
    A_mul_B!(similar(B, TS, size(A, 1), size(B, 2)), A,
             convert(AbstractMatrix{TS}, B))
end
