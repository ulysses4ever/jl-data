import Base: A_mul_B!

axpy!{T<:Number}(α::T, x::AbstractVector{T}, y::AbstractVector{T}) =
    BLAS.axpy!(α, x, y)


A_mul_B!{T<:Number}(α::T, A::AbstractMatrix{T},
                    x::AbstractVector{T},
                    β::T, y::AbstractVector{T}) =
                        BLAS.gemv!('N', α, A, x, β, y)

KindOfVector = AbstractVector
KindOfMatrix = AbstractMatrix
