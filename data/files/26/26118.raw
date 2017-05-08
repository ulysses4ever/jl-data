# Rearrangle a Kronecker product in preparation for factorization
function kron_shuffle!{T}(B::Matrix{T}, A::Matrix{T}, outer_rows::Int, outer_cols::Int, inner_rows::Int, inner_cols::Int)
    for or in 1:outer_rows, oc in 1:outer_cols, ir in 1:inner_rows, ic in 1:inner_cols
        B[outer_rows * (oc-1) + or, inner_rows * (ic-1) + ir] = A[inner_rows * (or-1) + ir, inner_cols * (oc-1) + ic]
    end
    
    return B
end

kron_shuffle{T}(A::Matrix{T}, outer_rows::Int, outer_cols::Int, inner_rows::Int, inner_cols::Int) = kron_shuffle!(Matrix{T}(outer_rows * outer_cols, inner_rows * inner_cols), A, outer_rows, outer_cols, inner_rows, inner_cols);

function kron_unshuffle!{T}(B::Matrix{T}, A::Matrix{T}, outer_rows::Int, outer_cols::Int, inner_rows::Int, inner_cols::Int)
    for or in 1:outer_rows, oc in 1:outer_cols, ir in 1:inner_rows, ic in 1:inner_cols
        B[inner_rows * (or-1) + ir, inner_cols * (oc-1) + ic] = A[outer_rows * (oc-1) + or, inner_rows * (ic-1) + ir] 
    end
    
    return B
end

kron_unshuffle{T}(A::Matrix{T}, outer_rows::Int, outer_cols::Int, inner_rows::Int, inner_cols::Int) = kron_unshuffle!(Matrix{T}(outer_rows * inner_rows, outer_cols * inner_cols), A, outer_rows, outer_cols, inner_rows, inner_cols);

# Factorization of a Kronecker product into its nearest two matrix factors
function kron_factor{T}(A::Matrix{T}, outer_rows::Int, outer_cols::Int, inner_rows::Int, inner_cols::Int)
    F = svdfact(kron_shuffle(A, outer_rows, outer_cols, inner_rows, inner_cols))
    X = reshape(sqrt(F[:S][1]) * F[:U][:, 1], outer_rows, outer_cols)
    Y = reshape(sqrt(F[:S][1]) * F[:V][:, 1], inner_rows, inner_cols)
    
    return X, Y
end

# Kronecker sum: A ⊕ B ⊕ ... = A ⊗ I ⊗ ... + I ⊗ B ⊗ ... + I ⊗ I ⊗ ... + ...
kron_sum{T}(A::Matrix{T}, B::Matrix{T}) = kron(A, eye(B)) + kron(eye(A), B)
kron_sum{T}(A::Matrix{T}, B::Matrix{T}, C::Matrix{T}) = kron(A, eye(B), eye(C)) + kron(eye(A), B, eye(C)) + kron(eye(A), eye(B), C)
kron_sum{T}(A::Matrix{T}, B::Matrix{T}, C::Matrix{T}, D::Matrix{T}) = kron(A, eye(B), eye(C), eye(D)) + kron(eye(A), B, eye(C), eye(D)) + kron(eye(A), eye(B), C, eye(D)) + kron(eye(A), eye(B), eye(C), D)

join_blocks{T}(A::Matrix{Matrix{T}}) = hcat([vcat(A[:, i]...) for i in 1:size(A, 2)]...)

function split_blocks{T}(C::Matrix{T}, rows::Int, cols::Int)
    block_rows, block_cols = size(C)
    mod(block_rows, rows) != 0 && error("Number of rows in block matrix ($(block_rows)) not divisible by number of rows in individual matrices ($rows)")
    mod(block_cols, cols) != 0 && error("Number of columns in block matrix ($(block_cols)) not divisible by number of columns in individual matrices ($cols)")
    [C[(i-1)*rows + 1 : i*rows, (j-1)*cols + 1 : j*cols] for i in 1:fld(block_rows, rows), j in 1:fld(block_cols, cols)]
end

# Generate a rotation matrix using the Lie algebra vector [x, y, z]
@inbounds function rotation!{T}(R::Matrix{T}, x::T, y::T, z::T)
    θ = sqrt(x^2 + y^2 + z^2)
    g = sin(θ) / θ
    h = (1 - cos(θ)) / θ^2

    R[1, 1] = 1 - h*(z^2 + y^2)
    R[2, 1] = h*x*y + g*z
    R[3, 1] = h*x*z - g*y
    R[1, 2] = h*x*y - g*z
    R[2, 2] = 1 - h*(z^2 + x^2)
    R[3, 2] = h*y*z + g*x
    R[1, 3] = h*x*z + g*y
    R[2, 3] = h*y*z - g*x
    R[3, 3] = 1 - h*(y^2 + x^2)

    return R
end

rotation{T}(x::T, y::T, z::T) = rotation!(Matrix{T}(3, 3), x, y, z)
rotation!{T}(R::Matrix{T}, v::Vector{T}) = rotation!(R, v[1], v[2], v[3])
rotation{T}(v::Vector{T}) = rotation!(Matrix{T}(3, 3), v[1], v[2], v[3])

# Generate a rotation matrix using the Euler ZYZ parameterization
@inbounds function euler_zyz!{T}(R::Matrix{T}, α::T, β::T, γ::T)
    R[1, 1] = cos(γ)⋅cos(α)⋅cos(β) - sin(γ)⋅sin(α)
    R[2, 1] = sin(α)⋅cos(γ)⋅cos(β) + sin(γ)⋅cos(α)
    R[3, 1] = -sin(β)⋅cos(γ)
    R[1, 2] = -sin(γ)⋅cos(α)⋅cos(β) - cos(γ)⋅sin(α)
    R[2, 2] = -sin(γ)⋅sin(α)⋅cos(β) + cos(γ)⋅cos(α)
    R[3, 2] = sin(β)⋅sin(γ)
    R[1, 3] = sin(β)⋅cos(α)
    R[2, 3] = sin(β)⋅sin(α)
    R[3, 3] = cos(β)

    return R
end

euler_zyz{T}(α::T, β::T, γ::T) = euler_zyz!(Matrix{T}(3, 3), α, β, γ)
euler_zyz!{T}(R::Matrix{T}, v::Vector{T}) = euler_zyz!(R, v[1], v[2], v[3])
euler_zyz{T}(v::Vector{T}) = euler_zyz!(Matrix{T}(3, 3), v[1], v[2], v[3])

# Nearest orthogonal matrix to A
function nearest_orthogonal!{T}(O::Matrix{T}, A::Matrix{T})
    F = svdfact(A)
    copy!(O, F[:U] * F[:Vt])
end

nearest_orthogonal{T}(A::Matrix{T}) = nearest_orthogonal!(similar(A), A)

# Nearest special orthogonal matrix to A
function nearest_special_orthogonal!{T}(SO::Matrix{T}, A::Matrix{T})
    F = svdfact(A)
    D = eye(A)
    D[end, end] = det(F[:U] * F[:Vt])
    copy!(SO, F[:U] * D * F[:Vt])
end

nearest_special_orthogonal{T}(A::Matrix{T}) = nearest_special_orthogonal!(similar(A), A)

cayley(A::Matrix) = 2 * inv(I + A) - I

function rotation2skew(R::Matrix)
    θ = acos(0.5*(trace(R) - 1))
    (0.5*θ/sin(θ)) * (R - R')
end

@inbounds function vec2skew!{T}(K::Matrix{T}, k::Vector{T})
    K[1, 1] =  0    ; K[2, 1] =  k[3] ; K[3, 1] = -k[2]
    K[1, 2] = -k[3] ; K[2, 2] =  0    ; K[3, 2] =  k[1]
    K[1, 3] =  k[2] ; K[2, 3] = -k[1] ; K[3, 3] =  0

    return K
end

vec2skew{T}(k::Vector{T}) = vec2skew!(Matrix{T}(3, 3), k)

@inbounds function vec2skew!{T}(K::Matrix{T}, x::T, y::T, z::T)
    K[1, 1] = 0  ; K[2, 1] =  z ; K[3, 1] = -y
    K[1, 2] = -z ; K[2, 2] =  0 ; K[3, 2] =  x
    K[1, 3] =  y ; K[2, 3] = -x ; K[3, 3] =  0

    return K
end

vec2skew{T}(x::T, y::T, z::T) = vec2skew!(Matrix{T}(3, 3), x, y, z)

@inbounds function skew2vec!{T}(k::Vector{T}, K::Matrix{T})
    k[1] = K[3, 2]
    k[2] = K[1, 3]
    k[3] = K[2, 1]

    return k
end

skew2vec(K::Matrix) = K[3, 2], K[1, 3], K[2, 1]







