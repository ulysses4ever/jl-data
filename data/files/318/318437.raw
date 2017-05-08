module MatrixFunctions

import Base: size, full, eltype, show, showarray
import Base.LinAlg: (*), issym, ishermitian, isposdef

export AbstractMatrixFunction
export MatrixFunction

abstract AbstractMatrixFunction{Td} <: AbstractSparseMatrix{Td, Int}

immutable MatrixFunction{Td} <: AbstractMatrixFunction{Td}
    nrow :: Int
    ncol :: Int
    eltype :: Type{Td} # just a witness
    sym :: Bool
    hermitian :: Bool
    posdef :: Bool
    apply :: Function
end

function MatrixFunction{Td}(nrow :: Int, ncol :: Int, eltype :: Type{Td},
                            apply :: Function;
                            sym = false, hermitian = false, posdef = false)
    @assert (nrow == ncol) || (!sym && !hermitian)
    MatrixFunction(nrow, ncol, eltype,
                   sym, hermitian, posdef,
                   apply)
end

MatrixFunction(M :: AbstractMatrix) =
    MatrixFunction(size(M, 1), size(M, 2), eltype(M),
                   issym(M), ishermitian(M), isposdef(M),
                   v -> M * v)

size{Td}(f :: MatrixFunction{Td}) = (f.nrow, f.ncol)

issym{Td}(f :: MatrixFunction{Td}) = f.sym
ishermitian{Td}(f :: MatrixFunction{Td}) = f.hermitian
isposdef{Td}(f :: MatrixFunction{Td}) = f.posdef

function show(io :: IO, f :: MatrixFunction)
    show(io, size(f, 1))
    print(io, "x")
    show(io, size(f, 2))
    print(io, " ")
    show(io, typeof(f))
    print(io, ": ")
    show(io, f.apply)
end

function showarray(io :: IO, f :: MatrixFunction;
                   header = true, limit = false,
                   sz = (s = Base.tty_size(); (s[1]-4, s[2])), repr=false)
    if header
        show(io, size(f, 1))
        print(io, "x")
        show(io, size(f, 2))
        print(io, " ")
        show(io, typeof(f))
        print(io, ": ")
    end
    show(io, f.apply)
end

function full(f :: MatrixFunction)
    T = eltype(f)
    result = zeros(T, size(f))
    test = zeros(T, size(f, 2))
    for c = 1:size(f, 2)
        test[c] = 1
        result[:, c] = f.apply(test)
        test[c] = 0
    end
    return result
end

function (*){T, S}(g :: MatrixFunction{T}, f :: MatrixFunction{S})
    @assert g.ncol == f.nrow
    TS = promote_type(arithtype(T), arithtype(S))
    apply = v -> g.apply(f.apply(v))
    MatrixFunction(g.nrow, f.ncol, TS, apply)
end

function (*){T, S}(f :: MatrixFunction{T}, M :: AbstractMatrix{S})
    @assert f.ncol == size(M, 1)
    TS = promote_type(arithtype(T), arithtype(S))
    result = zeros(TS, (f.nrow, size(M, 2)))
    for c = 1:size(M, 2)
        result[:, c] = f.apply(M[:, c])
    end
    return result
end

function (*){T, S}(f :: MatrixFunction{T}, v :: AbstractVector{S})
    @assert f.ncol == size(v, 1)
    return f.apply(v)
end

end # module
