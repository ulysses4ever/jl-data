# Generate a random orthogonal matrix
function random_orthogonal!{T}(O::Matrix{T}, n::Int)
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

random_orthogonal(n::Int) = random_orthogonal!(Matrix{Float64}(n, n), n)

# Generate a random 3D rotation matrix
function random_rotation()
    Q = random_orthogonal(3)
    det(Q) * Q
end

# Generate a random permutation matrix
random_permutation(n::Int) = eye(n)[:, randperm(n)]
