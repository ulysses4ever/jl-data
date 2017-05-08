type TuckerOperator
  coretensor
  matrices
end

# function perminverse(s)
#     X = [1:length(s)]
#     X[[s]] = [1:length(s)]
#     return X
# end
    
function unfold(A,n::Integer)
    R = n
    C = setdiff(1:ndims(A), n)
    I = size(A)
    J = prod(I[R])
    K = prod(I[C])
    Y = reshape(permutedims(A,[R,C]), J,K)
    return Y
end

function fold{Dimensions<:Integer}(m,dims::Vector{Dimensions},n::Integer)
    R = n
    C = setdiff([1:length(dims)], R)
    I = dims 
    I[n] = size(m,1)
    J = prod(I[R])
    K = prod(I[C])
    axes = [I[R],I[C]]
    trl = invperm([R,C])
    Z = reshape(m,axes...)
    return permutedims(Z,trl)
end

function modemult(t, m, mode::Integer)
    ut = unfold(t,mode)
    s = [size(t)...]
    s[mode] = size(m,1)
    return fold(m*ut, s, mode)
end


function modemult_list(t, mode_matrix_list)
    for (mode,m) in mode_matrix_list
        t=modemult(t, m, mode)
    end
    return t
end

scalarmult(t1,t2) = sum(vec(t1)'*vec(t2))

frobeniusnorm(t) = sqrt(scalarmult(t,t))

function left_singular_vectors{T<:FloatingPoint}(m::Matrix{T})
    mmt=Symmetric(m*m')
    u=eigvecs(mmt)
    return u
end

function left_singular_vectors{T<:Complex}(m::Matrix{T})
    mmct = Hermitian(m*m')
    u = eigvecs(mmct)
    return u
end

function hosvd(t, r=size(t))
    an=Array(Any, 0)
    for n=[1:ndims(t)]
        m = unfold(t,n)
        u = left_singular_vectors(m)
        push!(an,u[:,end-r[n]+1:end])
    end
    g = modemult_list(X, enumerate([a' for a in an]))
    return TuckerOperator(g, an)
end

