if Pkg.installed("CUDArt") != nothing
    using CUDArt
    using CUBLAS
    using CUSPARSE

    import Base: A_mul_B!

    axpy!{T<:Number}(α::T, x::CudaVector{T}, y::CudaVector{T}) =
        CUBLAS.axpy!(α, x, y)

    A_mul_B!{T<:Number}(α::T, A::CudaMatrix{T},
                        x::CudaVector{T},
                        β::T, y::CudaVector{T}) =
                            CUBLAS.gemv!('N', α, A, x, β, y)

    A_mul_B!{T<:Number}(α::T, A::AbstractCudaSparseMatrix{T},
                        x::CudaVector{T},
                        β::T, y::CudaVector{T}) =
                            CUSPARSE.mv!('N', α, A, x, β, y, 'O')

    KindOfVector = Union{AbstractVector,CudaVector}
    KindOfMatrix = Union{AbstractMatrix,CudaMatrix,AbstractCudaSparseMatrix}

    import Base: sub
    function sub{T}(M::CUDArt.CudaVector{T}, i::UnitRange)
        m = size(M,1)
        ptr = M.ptr + (minimum(i)-1)*m*sizeof(T)
        CudaVector{T}(ptr, (length(i),), M.dev)
    end

    function sub{T}(M::CUDArt.CudaMatrix{T}, ::Colon, j::Int)
        m = size(M,1)
        ptr = M.ptr + (j-1)*m*sizeof(T)
        CudaVector{T}(ptr, (m,), M.dev)
    end

    function sub{T}(M::CUDArt.CudaMatrix{T}, ::Colon, j::UnitRange)
        m = size(M,1)
        ptr = M.ptr + (minimum(j)-1)*m*sizeof(T)
        CudaMatrix{T}(ptr, (m,length(j)), M.dev)
    end

    export sub
end
