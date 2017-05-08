import Base: A_mul_B!, convert

using BandedMatrices

function Base.convert{BM<:BandedMatrix,T<:Union{SymTridiagonal,Tridiagonal}}(::Type{BM},M::T)
    m,n = size(M,1),size(M,2)
    ret=BandedMatrix(eltype(BM)==Any?eltype(M):promote_type(eltype(BM),eltype(M)),m,n,1,1)

    for i = 1:m
        ret[i,i] = M[i,i]
    end
    for i = 1:m-1
        ret[i,i+1] = M[i,i+1]
        ret[i+1,i] = M[i+1,i]
    end
    ret
end

function Base.convert{BM<:BandedMatrix}(::Type{BM},M::Diagonal)
    m,n = size(M,1),size(M,2)
    ret=BandedMatrix(eltype(BM)==Any?eltype(M):promote_type(eltype(BM),eltype(M)),m,n,0,0)

    for i = 1:m
        ret[i,i] = M[i,i]
    end
    ret
end

A_mul_B!{T<:Number}(α::T, A::BandedMatrix{T},
                    x::AbstractVector{T},
                    β::T, y::AbstractVector{T}) =
                        BLAS.gbmv!('N',A.m,A.l,A.u,α,A.data,x,β,y)
