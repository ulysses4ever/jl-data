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

function MatrixFunction(M :: AbstractMatrix)
    function apply(dst, src)
        dst = M * src
        return dst
    end
    MatrixFunction(size(M, 1), size(M, 2), eltype(M),
                   issym(M), ishermitian(M), isposdef(M),
                   apply)
end

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
        f.apply(result[:, c], test)
        test[c] = 0
    end
    return result
end

function (*){Td}(g :: MatrixFunction{Td}, f :: MatrixFunction{Td})
    @assert g.ncol == f.nrow
    sym = false # generally
    hermitian = false # generally
    function apply(dst, src)
        g.apply(dst, f.apply(f.nrow, src))
    end
    MatrixFunction (g.nrow, f.ncol, sym, hermitian, apply)
end

function (*){Td}(f :: MatrixFunction{Td}, M :: AbstractMatrix{Td})
    @assert f.ncol == size(M, 1)
    result = zeros(Td, (f.nrow, size(M, 2)))
    for c = 1:size(M, 2)
        f.apply(result[:, c], M[:, c])
    end
    return result
end

function (*){Td}(f :: MatrixFunction{Td}, v :: AbstractVector{Td})
    @assert f.ncol == size(v, 1)
    f.apply(zeros(Td, f.nrow), v)
end

end # module
