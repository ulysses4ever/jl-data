# Generate a random orthogonal matrix
function random_orthogonal{T}(O::Matrix{T}, n::Int)
    F = qrfact!(randn(n, n))
    Q = full(F[:Q])
    R = F[:R]
    for i in 1:size(R, 1)
        d = sign(R[i, i])
        for j in 1:size(Q, 2)
            Q[i, j] *= d
        end
    end

    return copy!(O, Q)
end

# Generate a random 3D rotation matrix
random_rotation{T}(R::Matrix{T}) = rotation(R, randn(), randn(), randn())

# Generate a random permutation matrix
random_permutation{T}(P::Matrix{T}, n::Int) = copy!(P, eye(T, n)[:, randperm(n)])

# Memory allocating function variants
random_orthogonal(n::Int) = random_orthogonal(Matrix{Float64}(n, n), n)
random_rotation() = random_rotation(Matrix{Float64}(3, 3))
random_permutation(n::Int) = random_permutation(Matrix{Int}(n, n), n)
