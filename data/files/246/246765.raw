module PolynomialOperators
using Polynomials
using LinearOperators
using IterativeSolvers

type PolynomialOperator <: AbstractLinearOperator
    A::AbstractLinearOperator
    p::Poly

    nrow::Integer
    ncol::Integer
    dtype::DataType
    symmetric::Bool
    hermitian::Bool
    prod::Function
    tprod::Nullable{Function}
    ctprod::Nullable{Function}
end

function poly_prod(p::Poly, A::AbstractLinearOperator,
                   v::StridedVector, tmp::StridedVector)
    w = zeros(promote_type(eltype(v), A.dtype), A.ncol)
    tmp[:] = v
    for k = 1:(length(p.a)-1)
        w += p.a[k]*tmp
        tmp[:] = A*tmp[:]
    end
    w += p.a[end]*tmp
    w
end

solve!{T<:Number}(x::StridedVector{T}, A::PolynomialOperator, B::StridedVector{T}) = gmres!(x,A,B)

import Polynomials: polyval
function polyval(p::Poly, A::AbstractLinearOperator, tmp::StridedVector)
    PolynomialOperator(A, p,
                       A.nrow, A.ncol, A.dtype,
                       A.symmetric, A.hermitian,
                       v -> poly_prod(p, A, v, tmp),
                       Nullable{Function}(v -> poly_tprod(p, A, v, tmp)),
                       Nullable{Function}(v -> poly_ctprod(p, A, v, tmp)))
end

import Base: *
(*)(op::PolynomialOperator, M::Vector) = op.prod(M)
(*)(op::PolynomialOperator, M::StridedVecOrMat) = op.prod(M)

export PolynomialOperator, solve!, polyval
end # module
