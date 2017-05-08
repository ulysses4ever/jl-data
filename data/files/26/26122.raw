function random_orthogonal(n::Int)
    F = qrfact!(randn(n, n))
    Q = full(F[:Q])
    R = F[:R]
    for i in size(R, 1)
        d = sign(R[i, i])
        for j in size(Q, 2)
            Q[i, j] *= d
        end
    end

    return Q
end

random_permutation(n::Int) = eye(Int, n)[:, randperm(n)]
