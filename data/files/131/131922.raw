

module M

function make_matrix(n, s=5.0)
    A = randn(n,n)
    for i = 1:n
        A[i,i] += s
    end
    A
end

nonsymm2symm(A) = (A + A')/2.0
make_symmat(n) = nonsymm2symm(make_matrix(n))

type MatrixDecomp
    nb::Int
    ni::Int
    Abb::Array{Float64,2}
    Aii::Array{Float64,2}
    Abi::Array{Float64,2}
    Aib::Array{Float64,2}
    
    function MatrixDecomp(A, nb, ni)
        Abb = A[1:nb, 1:nb]
        Abi = A[1:nb, (nb+1):end]
        Aib = A[(nb+1):end, 1:nb]
        Aii = A[(nb+1):end, (nb+1):end]
        
        new(nb, ni, Abb, Aii, Abi, Aib)
    end
end


using Base.LinAlg.LAPACK.getrf!
using Base.LinAlg.LAPACK.getrs!
using Base.LinAlg.BLAS.gemm!
using Base.LinAlg.BLAS.gemv!

type StaticCond
    nb::Int
    ni::Int
    B::Array{Float64,2}
    iAii::Array{Float64,2}
    X::Array{Float64,2}
    Aib::Array{Float64,2}
    ipiv::Array{Int,1}
    ipiv2::Array{Int,1}
    function StaticCond(A::MatrixDecomp)
        nb = A.nb
        ni = A.ni
        B = zeros(nb, nb)
        iAii = copy(A.Aii)
        iAii, ipiv, info = getrf!(iAii)
        X = A.Abi'
        getrs!('T', iAii, ipiv, X)
        
        B = copy(A.Abb)
        gemm!('T', 'N', -1.0, X, A.Aib, 1.0, B)
        B, ipiv2, info = getrf!(B)
        
        new(nb, ni, B, iAii, X, copy(A.Aib), ipiv, ipiv2)
    end
end
using Base.LinAlg.LAPACK.potrf!
using Base.LinAlg.LAPACK.potrs!

type ChoStaticCond
    nb::Int
    ni::Int
    B::Array{Float64,2}
    iAii::Array{Float64,2}
    X::Array{Float64,2}
    function ChoStaticCond(A::MatrixDecomp)
        nb = A.nb
        ni = A.ni
        iAii = copy(A.Aii)
        iAii, info = potrf!('L', iAii)
        X = copy(A.Aib)
        potrs!('L', iAii, X)

        B = copy(A.Abb)
        gemm!('T', 'N', -1.0, X, A.Aib, 1.0, B)

        B, info = potrf!('L', B)
        
        new(nb, ni, B, iAii, X)
    end
end


    
function mysolve(A::StaticCond, f)
    nb = A.nb
    ni = A.ni
    
    fb = f[1:nb]
    fi = f[(nb+1):end]

    gemv!('T', -1.0, A.X, fi, 1.0, fb)

    getrs!('N', A.B, A.ipiv2, fb)
    
    gemv!('N', -1.0, A.Aib, fb, 1.0, fi)

    getrs!('N', A.iAii, A.ipiv, fi)

    [fb, fi]
end

function mysolve(A::ChoStaticCond, f)
    nb = A.nb
    ni = A.ni

    fb = f[1:nb]
    fi = f[(nb+1):end]

    gemv!('T', -1.0, A.X, fi, 1.0, fb)
    potrs!('L', A.B, fb)

    potrs!('L', A.iAii, fi)
    gemv!('N', -1.0, A.X, fb, 1.0, fi)

    [fb, fi]
end


function teste(n=15, nb=10, ni=5)

    A = make_symmat(n)
    Abi = MatrixDecomp(A, nb, ni)

    iA = inv(A)
    f = linspace(1, n, n)

    x = iA * f

    S1 = StaticCond(Abi)

    x1 = mysolve(S1, f)

    S2 = ChoStaticCond(Abi)
    x2 = mysolve(S2, f)

    hcat(x, x1, x2)
end


end # Module

