TuckerType = Union{Real, Complex}

immutable TuckerOperator{T<:TuckerType}
  coretensor::Array{T}
  matrices::Vector{Matrix{T}}
end

function size(t::TuckerOperator)
  size(t.coretensor)
end

function size(t::TuckerOperator, n::Int)
  size(t.coretensor, n)
end

function unfold(A::Array, n::Integer)
    C = setdiff(1:ndims(A), n)
    I = size(A)
    J = prod(I[n])
    K = prod(I[C])
    Y = reshape(permutedims(A,[n; C]), J, K)
    return Y
end

function fold{T<:Integer}(A::Matrix, dims::Vector{T}, n::Integer)
    C = setdiff(1:length(dims), n)
    I = dims
    I[n] = size(A, 1)
    J = prod(I[n])
    K = prod(I[C])
    axes = [I[n]; I[C]]
    trl = invperm([n; C])
    Z = reshape(A, axes...)
    return permutedims(Z, trl)
end

function modemult(t::Array, m::Matrix, mode::Integer)
    ut = unfold(t,mode)
    s = [size(t)...]
    s[mode] = size(m,1)
    return fold(m*ut, s, mode)
end

function modemult_list(t::Array, mode_matrix_list)
    nt = deepcopy(t)
    for (mode,m) in mode_matrix_list
        nt = modemult(nt, m, mode)
    end
    return nt
end

scalarmult(t1::Array, t2::Array) = sum(vec(t1)'*vec(t2))

frobeniusnorm(t::Array) = sqrt(scalarmult(t,t))

left_singular_vectors{T<:Real}(m::Matrix{T}, k::Integer=size(m, 1)) = eigvecs(Symmetric(m*m'))[:,end:-1:end-k+1]
left_singular_vectors{T<:Complex}(m::Matrix{T}, k::Integer=size(m, 1)) = eigvecs(Hermitian(m*m'))[:,end:-1:end-k+1]

for (M, N) in [(Real, Float64), (Complex, Complex128)]
  @eval function hosvd{T<:$M}(t::Array{T}, r=size(t))
    an = Matrix{$N}[]
    for n=1:ndims(t)
      m = unfold(t, n)
      u = left_singular_vectors(m, r[n])
      push!(an, u)
    end
    g = modemult_list(t, enumerate([a' for a in an]))
    return TuckerOperator(g, an)
  end
end

reconstruct(t::TuckerOperator) = modmult_list(t.coretensor, enumerate(t.matrices))

function reconstruct(t::TuckerOperator, r=size(t.coretensor))
  ranges=[1:r[i] for i in 1:length(r)]
  ct = copy(t.coretensor[ranges...])
  for (i, m) in enumerate(t.matrices)
    U = m[:,1:r[i]]
    ct = modemult(ct, U, i)
  end
  return(ct)
end
