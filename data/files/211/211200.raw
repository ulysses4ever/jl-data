type TuckerOperator
  coretensor::AbstractArray
  matrices::AbstractArray
end

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
    nt = deepcopy(t)
    for (mode,m) in mode_matrix_list
        nt = modemult(nt, m, mode)
    end
    return nt
end

scalarmult(t1,t2) = sum(vec(t1)'*vec(t2))

frobeniusnorm(t) = sqrt(scalarmult(t,t))

#=
function decreesing_eigvecs(m::Union(Symmetric, Hermitian), k=1)
  u = eigvecs(m,k:end)
  u = u[:,end:-1:1]
end
=#

left_singular_vectors{T<:Real}(m::Matrix{T}, k::Integer=size(m)[1]) = eigvecs(Symmetric(m*m'))[:,end:-1:end-k+1]
left_singular_vectors{T<:Complex}(m::Matrix{T}, k::Integer=size(m)[1]) = eigvecs(Hermitian(m*m'))[:,end:-1:end-k+1]

function hosvd(t, r=size(t))
  an=Array(Any, 0)
  for n=[1:ndims(t)]
    m = unfold(t,n)
    u = left_singular_vectors(m, r[n])
    println(size(u))
    push!(an,u)
  end
  g = modemult_list(t, enumerate([a' for a in an]))
  return TuckerOperator(g, an)
end

reconstruct(t::TuckerOperator) = modmult_list(t.coretensor, enumerate(t.matrices))

function reconstruct(t::TuckerOperator, r=size(t.coretensor))
  ct = t.coretensor
  for (i, m) in enumerate(t.matrices)
    ct = modemult(ct, m[:,1:r[i]], i)
  end
  return(ct)
end
