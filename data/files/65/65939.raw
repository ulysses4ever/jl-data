using CUDArt
using CUBLAS

import Base: A_mul_B!, eltype

using BandedMatrices

type CudaBandedMatrix{T<:Number}
    data::CudaMatrix{T}
    m::Int
    l::Int
    u::Int
end
CudaBandedMatrix{T<:Number}(BM::BandedMatrix{T}) =
    CudaBandedMatrix{T}(CudaArray(BM.data),BM.m,BM.l,BM.u)

A_mul_B!{T<:Number}(α::T, A::CudaBandedMatrix{T},
                    x::CudaVector{T},
                    β::T, y::CudaVector{T}) =
                        CUBLAS.gbmv!('N',A.m,A.l,A.u,α,A.data,x,β,y)

eltype{T}(M::CudaBandedMatrix{T}) = T

export CudaBandedMatrix
