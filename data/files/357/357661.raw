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

copy(S::SparseMatrixCSR) =
    SparseMatrixCSR(S.m, S.n, copy(S.rowptr), copy(S.colval), copy(S.nzval))

spzeros_csr(m::Integer, n::Integer) = spzeros_csr(Float64, m, n)
spzeros_csr(Tv::Type, m::Integer, n::Integer) = spzeros_csr(Tv, Int, m, n)
function spzeros_csr(Tv::Type, Ti::Type, m::Integer, n::Integer)
    ((m < 0) || (n < 0)) && throw(ArgumentError("Invalid Array dimensions"))
    SparseMatrixCSR(m, n, ones(Ti, m+1), Array(Ti, 0), Array(Tv, 0))
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

    numnz = indptr[m+1] - 1

    # get colptr by accumulating hits on colval and doing cumsum
    @inbounds Bptr[1] = 1
    @inbounds for i=1:numnz Bptr[indval[i]+1] += 1; end
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

    # fix up Bptr
    last = 1
    @inbounds for col=1:n
        temp = Bptr[col]
        Bptr[col] = last
        last = temp
    end
    Bptr, Bind, Bval
end

function Base.convert{Tv,Ti<:Integer}(::Type{SparseMatrixCSC},
                                      A::SparseMatrixCSR{Tv,Ti})
    Bptr, Bind, Bval = csr2csc(A.rowptr, A.colval, A.nzval, A.m, A.n)
    SparseMatrixCSC(A.m, A.n, Bptr, Bind, Bval)
end

function Base.convert{Tv,Ti<:Integer}(::Type{SparseMatrixCSR},
                                      B::SparseMatrixCSC{Tv,Ti})
    Aptr, Aind, Aval = csr2csc(B.colptr, B.rowval, B.nzval, B.n, B.m)
    SparseMatrixCSR(B.m, B.n, Aptr, Aind, Aval)
end

## getindex methods. NOTE: copied and modified from Base
getindex(A::SparseMatrixCSR, I::Tuple{Integer,Integer}) =
    getindex(A, I[1], I[2])

function getindex{Tv,Ti}(A::SparseMatrixCSR{Tv,Ti}, i0::Integer, i1::Integer)
    !(1 <= i0 <= A.m && 1 <= i1 <= A.n) && throw(BoundsError())
    r1 = Int(A.rowptr[i0])
    r2 = Int(A.rowptr[i0+1]-1)
    (r1 > r2) && return zero(Tv)
    r1 = searchsortedfirst(A.colval, i1, r1, r2, Base.Order.Forward)
    ((r1 > r2) || (A.colval[r1] != i1)) ? zero(Tv) : A.nzval[r1]
end

getindex{T<:Integer}(A::SparseMatrixCSR, I::AbstractVector{T}, j::Integer) =
    getindex(A, I, [j])
getindex{T<:Integer}(A::SparseMatrixCSR, i::Integer, J::AbstractVector{T}) =
    getindex(A, [i], J)

# Colon translation (this could be done more efficiently)
getindex(A::SparseMatrixCSR, ::Colon) = getindex(A, 1:length(A))
getindex(A::SparseMatrixCSR, ::Colon, ::Colon) = getindex(A, 1:size(A, 1), 1:size(A, 2))
getindex(A::SparseMatrixCSR, ::Colon, j) = getindex(A, 1:size(A, 1), j)
getindex(A::SparseMatrixCSR, i, ::Colon) = getindex(A, i, 1:size(A, 2))

function getindex_rows{Tv,Ti}(A::SparseMatrixCSR{Tv,Ti}, I::AbstractVector)
    m, n = size(A)
    nI = length(I)

    rowptrA = A.rowptr; colvalA = A.colval; nzvalA = A.nzval

    rowptrB = Array(Ti, nI+1)
    rowptrB[1] = 1
    nnzB = 0

    @inbounds for i = 1:nI
        row = I[i]
        1 <= row <= m || throw(BoundsError())
        nnzB += rowptrA[row+1] - rowptrA[row]
        rowptrB[i+1] = nnzB + 1
    end

    colvalB = Array(Ti, nnzB)
    nzvalB  = Array(Tv, nnzB)
    ptrB = 0

    @inbounds for i = 1:nI
        row = I[i]
        for k = rowptrA[row]:rowptrA[row+1]-1
            ptrB += 1
            colvalB[ptrB] = colvalA[k]
            nzvalB[ptrB] = nzvalA[k]
        end
    end
    return SparseMatrixCSR(nI, n, rowptrB, colvalB, nzvalB)
end

function getindex{Tv,Ti<:Integer}(A::SparseMatrixCSR{Tv,Ti},
                                  I::AbstractVector, J::Range)
    # Ranges for indexing rows
    (m, n) = size(A)

    # whole rows:
    if J == 1:n
        return getindex_rows(A, I)
    end

    nI = length(I)
    nJ = length(J)
    rowptrA = A.rowptr; colvalA = A.colval; nzvalA = A.nzval
    rowptrS = Array(Ti, nI+1)
    rowptrS[1] = 1
    nnzS = 0

    # Form the structure of the result and compute space
    @inbounds for i = 1:nI
        row = I[i]
        @simd for k in rowptrA[row]:rowptrA[row+1]-1
            nnzS += colvalA[k] in J
        end
        rowptrS[i+1] = nnzS+1
    end

    # Populate the values in the result
    colvalS = Array(Ti, nnzS)
    nzvalS  = Array(Tv, nnzS)
    ptrS    = 1

    @inbounds for i = 1:nI
        row = I[i]
        for k = rowptrA[row]:rowptrA[row+1]-1
            colA = colvalA[k]
            j = Base.SparseMatrix.rangesearch(J, colA)
            if j > 0
                colvalS[ptrS] = j
                nzvalS[ptrS] = nzvalA[k]
                ptrS += 1
            end
        end
    end

    return SparseMatrixCSR(nI, nJ, rowptrS, colvalS, nzvalS)
end

function getindex_J_sorted{Tv,Ti}(A::SparseMatrixCSR{Tv,Ti}, I::AbstractVector,
                                  J::AbstractVector)
    # sorted vectors for indexing columns
    # similar to getindex_general, but without the transpose trick
    m, n = size(A)

    nJ = length(J)
    avgN = div(nnz(A), m)

    # heuristics based on experiments
    alg = ((nJ - avgN) > 2^8)  ? 1 :
          ((avgN - nJ) > 2^10) ? 0 : 2

    return (alg == 0) ? getindex_J_sorted_bsearch_A(A, I, J) :
           (alg == 1) ? getindex_J_sorted_bsearch_J(A, I, J) :
                        getindex_J_sorted_linear(A, I, J)
end

function getindex_J_sorted_bsearch_A{Tv,Ti}(A::SparseMatrixCSR{Tv,Ti},
                                            I::AbstractVector, J::AbstractVector)
    const nI = length(I)
    const nJ = length(J)

    rowptrA = A.rowptr; colvalA = A.colval; nzvalA = A.nzval
    rowptrS = Array(Ti, nI+1)
    rowptrS[1] = 1

    ptrS = 1
    # determine result size
    @inbounds for i = 1:nI
        row = I[i]
        ptrJ::Int = 1 # runs through J
        ptrA::Int = rowptrA[row]
        stopA::Int = rowptrA[row+1]-1
        if ptrA <= stopA
            while ptrJ <= nJ
                colJ = J[ptrJ]
                ptrJ += 1
                (colvalA[ptrA] > colJ) && continue
                ptrA = searchsortedfirst(colvalA, colJ, ptrA, stopA, Base.Order.Forward)
                (ptrA <= stopA) || break
                if colvalA[ptrA] == colJ
                    ptrS += 1
                end
            end
        end
        rowptrS[i+1] = ptrS
    end

    colvalS = Array(Ti, ptrS-1)
    nzvalS  = Array(Tv, ptrS-1)

    # fill the values
    ptrS = 1
    @inbounds for i = 1:nI
        row = I[i]
        ptrJ::Int = 1 # runs through J
        ptrA::Int = rowptrA[row]
        stopA::Int = rowptrA[row+1]-1
        if ptrA <= stopA
            while ptrJ <= nJ
                colJ = J[ptrJ]
                if colvalA[ptrA] <= colJ
                    ptrA = searchsortedfirst(colvalA, colJ, ptrA, stopA, Base.Order.Forward)
                    (ptrA <= stopA) || break
                    if colvalA[ptrA] == colJ
                        colvalS[ptrS] = ptrJ
                        nzvalS[ptrS] = nzvalA[ptrA]
                        ptrS += 1
                    end
                end
                ptrJ += 1
            end
        end
    end
    return SparseMatrixCSR(nI, nJ, rowptrS, colvalS, nzvalS)
end

function getindex_J_sorted_linear{Tv,Ti}(A::SparseMatrixCSR{Tv,Ti},
                                         I::AbstractVector, J::AbstractVector)
    const nI = length(I)
    const nJ = length(J)

    rowptrA = A.rowptr; colvalA = A.colval; nzvalA = A.nzval
    rowptrS = Array(Ti, nI+1)
    rowptrS[1] = 1
    cacheJ = zeros(Int, A.n)

    ptrS   = 1
    # build the cache and determine result size
    @inbounds for i = 1:nI
        row = I[i]
        ptrJ::Int = 1 # runs through I
        ptrA::Int = rowptrA[row]
        stopA::Int = rowptrA[row+1]
        while ptrJ <= nJ && ptrA < stopA
            colA = colvalA[ptrA]
            colJ = J[ptrJ]

            if colJ > colA
                ptrA += 1
            elseif colJ < colA
                ptrJ += 1
            else
                (cacheJ[colA] == 0) && (cacheJ[colA] = ptrJ)
                ptrS += 1
                ptrJ += 1
            end
        end
        rowptrS[i+1] = ptrS
    end

    colvalS = Array(Ti, ptrS-1)
    nzvalS  = Array(Tv, ptrS-1)

    # fill the values
    ptrS = 1
    @inbounds for i = 1:nI
        row = I[i]
        ptrA::Int = rowptrA[row]
        stopA::Int = rowptrA[row+1]
        while ptrA < stopA
            colA = colvalA[ptrA]
            ptrJ = cacheJ[colA]
            if ptrJ > 0
                while ptrJ <= nJ && J[ptrJ] == colA
                    colvalS[ptrS] = ptrJ
                    nzvalS[ptrS] = nzvalA[ptrA]
                    ptrS += 1
                    ptrJ += 1
                end
            end
            ptrA += 1
        end
    end
    return SparseMatrixCSR(nI, nJ, rowptrS, colvalS, nzvalS)
end

function getindex_J_sorted_bsearch_J{Tv,Ti}(A::SparseMatrixCSR{Tv,Ti},
                                            I::AbstractVector, J::AbstractVector)
    const nI = length(I)
    const nJ = length(J)

    rowptrA = A.rowptr; colvalA = A.colval; nzvalA = A.nzval
    rowptrS = Array(Ti, nI+1)
    rowptrS[1] = 1

    n = A.n

    # cacheJ is used first to store num occurrences of each col in rows of
    # interest and later to store position of first occurrence of each col in J
    cacheJ = zeros(Int, n)

    # count rows
    @inbounds for i = 1:nI
        row = I[i]
        for ptrA in rowptrA[row]:(rowptrA[row+1]-1)
            cacheJ[colvalA[ptrA]] += 1
        end
    end

    # fill cache and count nnz
    ptrS::Int = 0
    ptrJ::Int = 1
    @inbounds for i = 1:n
        rval = cacheJ[i]
        (rval == 0) && continue
        ptrJ = searchsortedfirst(J, i, ptrJ, nJ, Base.Order.Forward)
        cacheJ[i] = ptrJ
        while ptrJ <= nJ && J[ptrJ] == i
            ptrS += rval
            ptrJ += 1
        end
        if ptrJ > nJ
            @simd for j=(i+1):n; @inbounds cacheJ[i]=ptrJ; end
            break
        end
    end

    colvalS = Array(Ti, ptrS)
    nzvalS  = Array(Tv, ptrS)
    rowptrS[nI+1] = ptrS+1

    # fill the values
    ptrS = 1
    @inbounds for i = 1:nI
        row = I[i]
        ptrA::Int = rowptrA[row]
        stopA::Int = rowptrA[row+1]
        while ptrA < stopA
            colA = colvalA[ptrA]
            ptrJ = cacheJ[colA]
            (ptrJ > nJ) && break
            if ptrJ > 0
                while J[ptrJ] == colA
                    colvalS[ptrS] = ptrJ
                    nzvalS[ptrS] = nzvalA[ptrA]
                    ptrS += 1
                    ptrJ += 1
                    (ptrJ > nJ) && break
                end
            end
            ptrA += 1
        end
        rowptrS[i+1] = ptrS
    end
    return SparseMatrixCSR(nI, nI, rowptrS, colvalS, nzvalS)
end

function permute_cols!{Tv,Ti}(S::SparseMatrixCSR{Tv,Ti}, pJ::Vector{Int})
    (m, n) = size(S)
    rowptrS = S.rowptr; colvalS = S.colval; nzvalS = S.nzval
    # preallocate temporary sort space
    nc = min(nnz(S), n)
    colperm = Array(Int, nc)
    colvalTemp = Array(Ti, nc)
    nzvalTemp = Array(Tv, nc)

    for i in 1:m
        colrange = rowptrS[i]:(rowptrS[i+1]-1)
        nc = length(colrange)
        (nc > 0) || continue
        k = 1
        for j in colrange
            colA = colvalS[j]
            colvalTemp[k] = pJ[colA]
            nzvalTemp[k] = nzvalS[j]
            k += 1
        end
        sortperm!(pointer_to_array(pointer(colperm), nc), pointer_to_array(pointer(colvalTemp), nc))
        k = 1
        for j in colrange
            kperm = colperm[k]
            colvalS[j] = colvalTemp[kperm]
            nzvalS[j] = nzvalTemp[kperm]
            k += 1
        end
    end
    S
end

function getindex_general{Tv,Ti}(A::SparseMatrixCSR{Tv,Ti}, I::AbstractVector,
                                 J::AbstractVector)
    pJ = sortperm(J)
    @inbounds J = J[pJ]
    permute_cols!(getindex_J_sorted(A, I, J), pJ)
end

# the general case:
function getindex{Tv,Ti}(A::SparseMatrixCSR{Tv,Ti}, I::AbstractVector,
                         J::AbstractVector)
    (m, n) = size(A)

    if !isempty(J)
        minj, maxj = extrema(J)
        ((minj < 1) || (maxj > n)) && throw(BoundsError())
    end

    if !isempty(I)
        mini, maxi = extrema(I)
        ((mini < 1) || (maxi > m)) && throw(BoundsError())
    end

    if isempty(I) || isempty(J) || (0 == nnz(A))
        return spzeros(Tv, Ti, length(I), length(J))
    end

    if issorted(I)
        return getindex_J_sorted(A, I, J)
    else
        return getindex_general(A, I, J)
    end
end

# logical getindex - the methods immediately below are to avoid ambiguity errors
getindex(::SparseMatrixCSR, ::AbstractVector{Bool}, ::Range{Bool}) = error("Cannot index with Range{Bool}")
getindex{T<:Integer}(::SparseMatrixCSR, ::AbstractVector{T}, ::Range{Bool}) = error("Cannot index with Range{Bool}")
getindex(::SparseMatrixCSR, ::Range{Bool}, ::Range{Bool}) = error("cannot index with Range{Bool}")
getindex{T<:Integer}(::SparseMatrixCSR, ::Range{T}, ::Range{Bool}) = error("Cannot index with Range{Bool}")

getindex{T<:Integer}(A::SparseMatrixCSR, I::AbstractVector{Bool}, J::Range{T}) = A[find(I), J]
getindex{T<:Integer}(A::SparseMatrixCSR, I::Range{T}, J::AbstractVector{Bool}) = A[I,find(J)]
getindex(A::SparseMatrixCSR, I::Integer, J::AbstractVector{Bool}) = A[I,find(J)]
getindex(A::SparseMatrixCSR, I::AbstractVector{Bool}, J::Integer) = A[find(I),J]
getindex(A::SparseMatrixCSR, I::AbstractVector{Bool}, J::AbstractVector{Bool}) = A[find(I),find(J)]
getindex{T<:Integer}(A::SparseMatrixCSR, I::AbstractVector{T}, J::AbstractVector{Bool}) = A[I,find(J)]
getindex{T<:Integer}(A::SparseMatrixCSR, I::AbstractVector{Bool}, J::AbstractVector{T}) = A[find(I),J]

function getindex{Tv}(A::SparseMatrixCSR{Tv}, I::AbstractArray{Bool})
    checkbounds(A, I)
    n = sum(I)

    rowptrA = A.rowptr; colvalA = A.colval; nzvalA = A.nzval
    rowptrB = Int[1,n+1]
    colvalB = Array(Int, n)
    nzvalB = Array(Tv, n)
    c = 1
    colB = 1

    @inbounds for row in 1:A.m
        c1 = rowptrA[row]
        c2 = rowptrA[row+1]-1

        for col in 1:A.n
            if I[row, col]
                while (c1 <= c2) && (colvalA[c1] < col)
                    c1 += 1
                end
                if (c1 <= c2) && (colvalA[c1] == col)
                    nzvalB[c] = nzvalA[c1]
                    colvalB[c] = colB
                    c += 1
                end
                colB += 1
                (colB > n) && break
            end
        end
        (colB > n) && break
    end
    rowptrB[end] = c
    n = length(nzvalB)
    if n > (c-1)
        deleteat!(nzvalB, c:n)
        deleteat!(colvalB, c:n)
    end
    SparseMatrixCSR(1, n, rowptrB, colvalB, nzvalB)
end

function getindex{Tv,Ti}(A::SparseMatrixCSR{Tv,Ti}, I::AbstractArray)
    szA = size(A);
    nA = szA[1] * szA[2]
    rowptrA = A.rowptr
    colvalA = A.colval
    nzvalA = A.nzval

    n = length(I)
    outm = size(I, 1)
    outn = size(I, 2)
    szB = (outm, outn)
    rowptrB = zeros(Int, outm+1)
    colvalB = Array(Int, n)
    nzvalB = Array(Tv, n)

    rowB = colB = 1
    rowptrB[rowB] = 1
    idxB = 1

    @inbounds for i in 1:n
        ((I[i] < 1) | (I[i] > nA)) && throw(BoundsError())
        rowA, colA = ind2sub(szA, I[i])
        rowB, colB = ind2sub(szB, i)

        for c in rowptrA[rowA]:(rowptrA[rowA+1]-1)
            if colvalA[c] == colA
                rowptrB[rowB+1] += 1
                colvalB[idxB] = colB
                nzvalB[idxB] = nzvalA[c]
                idxB += 1
                break
            end
        end
    end

    rowptrB = cumsum(rowptrB)

    if n > (idxB-1)
        deleteat!(nzvalB, idxB:n)
        deleteat!(colvalB, idxB:n)
    end

    SparseMatrixCSR(outm, outn, rowptrB, colvalB, nzvalB)
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

function row_kron{TvA,TiA,TvB,TiB}(A::SparseMatrixCSR{TvA,TiA},
                                   B::SparseMatrixCSR{TvB,TiB})
    TvS = promote_type(Base.LinAlg.arithtype(TvA), Base.LinAlg.arithtype(TvB))
    TiS = promote_type(TiA, TiB)

    mA, nA = size(A)
    mB, nB = size(B)

    mA == mB || error(DimensionMismatch("A and B must have same number of rows"))

    rowptrA = A.rowptr; colvalA = A.colval; nzvalA = A.nzval
    rowptrB = B.rowptr; colvalB = B.colval; nzvalB = B.nzval

    rowptrS = Array(TiS, mA+1)
    colvalS = Array(TiS, nA*nB)  # overallocate then deleteat! to avoid cache misses
    nzvalS = Array(TvS, nA*nB)

    rowptrS[1] = 1
    ptrS = 1
    @inbounds for row = 1:mA
        cindA = rowptrA[row]:rowptrA[row+1]-1
        cindB = rowptrB[row]:rowptrB[row+1]-1

        for ca in cindA
            for cb in cindB
                colvalS[ptrS] = (colvalA[ca]-1)*nB + colvalB[cb]
                nzvalS[ptrS] = nzvalB[cb]*nzvalA[ca]
                ptrS += 1
            end
        end

        rowptrS[row+1] = ptrS
    end

    if nA*nB > (ptrS-1)
        deleteat!(nzvalS, ptrS:nA*nB)
        deleteat!(colvalS, ptrS:nA*nB)
    end

    SparseMatrixCSR(mA, nA*nB, rowptrS, colvalS, nzvalS)
end
