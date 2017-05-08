import Base: call, (+), (*)

type LinOp{T<:Number}
    prod::Function
end

call{T<:Number}(op::LinOp{T},
                y::KindOfVector,
                x::KindOfVector,
                α = one(T), β = zero(T)) = op.prod(y, x, α, β)

function call{T<:Number}(op::LinOp{T},
                         x::KindOfVector,
                         α = one(T))
    y = similar(x)
    op.prod(y, x, α, zero(T))
    y
end


# Scalar operator

LinOp{T<:Number}(a::T) =
    LinOp{T}((y,x,α,β) -> begin
             scale!(y, β)
             axpy!(α*a, x, y)
             end)

# Single matrix operator
LinOp(A::KindOfMatrix) = LinOp{eltype(A)}((y,x,α,β) -> A_mul_B!(α, A, x, β, y))

# Chained/transformed operators
(*){T<:Number}(a::Number, O::LinOp{T}) = LinOp{T}((y,x,α,β) -> O(y,x,a*α,β))

# y <- α(A+B)x + βy
(+){T<:Number}(A::LinOp{T}, B::LinOp{T}) =
    LinOp{T}((y,x,α,β) -> begin
             A(y,x,α,β)
             B(y,x,α,one(T))
             end)

export LinOp
