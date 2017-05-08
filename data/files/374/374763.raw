module MatrixFunctions

import Base: size, full, eltype, show, showarray
import Base.LinAlg: (*), (+), (.*), issym, ishermitian, isposdef

export AbstractMatrixFunction
export MatrixFunction

arithtype(T) = T
arithtype(::Type{Bool}) = Int

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

MatrixFunction(u :: AbstractVector) =
    MatrixFunction(1, length(u, 2), eltype(u),
                   false, false, false,
                   v -> u' * v)

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

function (*){T, S}(M :: Matrix{S}, f :: MatrixFunction{T})
    MatrixFunction(M) * f
end

function (*){T, S}(f :: MatrixFunction{T}, v :: AbstractVector{S})
    @assert f.ncol == size(v, 1)
    return f.apply(v)
end

function (*){T, S}(v :: Vector{S}, f :: MatrixFunction{T})
    MatrixFunction(v) * f
end

function (+){T, S}(f :: MatrixFunction{T}, g :: MatrixFunction{S})
    @assert f.nrow == g.nrow
    @assert f.ncol == g.ncol
    TS = promote_type(arithtype(T), arithtype(S))
    function sum_apply(src)
        dst = g.apply(src)
        dst += f.apply(src)
    end
    MatrixFunction(f.nrow, f.ncol, TS, sum_apply;
                   sym = f.sym && g.sym,
                   hermitian = f.hermitian && g.hermitian,
                   posdef = f.posdef && g.posdef)
end

function (.*){T <: Number, S}(scalar :: T, f :: MatrixFunction{S})
    TS = promote_type(arithtype(T), arithtype(S))
    function scalar_apply(src)
        dst = f.apply(src)
        scale!(scalar, dst)
        return dst
    end
    MatrixFunction(f.nrow, f.ncol, TS, scalar_apply;
                   sym = f.sym,
                   hermitian = f.hermitian && isreal(scalar),
                   posdef = f.posdef && isreal(scalar) && scalar > 0)
end

end # module
