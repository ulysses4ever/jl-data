# Rearrangle a Kronecker product in preparation for factorization
function kronshuffle!{T}(B::Matrix{T}, A::Matrix{T}, outer_rows::Int, outer_cols::Int, inner_rows::Int, inner_cols::Int)
    for or in 1:outer_rows, oc in 1:outer_cols, ir in 1:inner_rows, ic in 1:inner_cols
        B[outer_rows * (oc-1) + or, inner_rows * (ic-1) + ir] = A[inner_rows * (or-1) + ir, inner_cols * (oc-1) + ic]
    end
    
    return B
end

kronshuffle{T}(A::Matrix{T}, outer_rows::Int, outer_cols::Int, inner_rows::Int, inner_cols::Int) = kronshuffle!(Matrix{T}(outer_rows * outer_cols, inner_rows * inner_cols), A, outer_rows, outer_cols, inner_rows, inner_cols);

function kronunshuffle!{T}(B::Matrix{T}, A::Matrix{T}, outer_rows::Int, outer_cols::Int, inner_rows::Int, inner_cols::Int)
    for or in 1:outer_rows, oc in 1:outer_cols, ir in 1:inner_rows, ic in 1:inner_cols
        B[inner_rows * (or-1) + ir, inner_cols * (oc-1) + ic] = A[outer_rows * (oc-1) + or, inner_rows * (ic-1) + ir] 
    end
    
    return B
end

kronunshuffle{T}(A::Matrix{T}, outer_rows::Int, outer_cols::Int, inner_rows::Int, inner_cols::Int) = kronunshuffle!(Matrix{T}(outer_rows * inner_rows, outer_cols * inner_cols), A, outer_rows, outer_cols, inner_rows, inner_cols);

# Factorization of a Kronecker product into its nearest two matrix factors
function kronfactor{T}(A::Matrix{T}, outer_rows::Int, outer_cols::Int, inner_rows::Int, inner_cols::Int)
    F = svdfact(kronshuffle(A, outer_rows, outer_cols, inner_rows, inner_cols))
    X = reshape(sqrt(F[:S][1]) * F[:U][:, 1], outer_rows, outer_cols)
    Y = reshape(sqrt(F[:S][1]) * F[:V][:, 1], inner_rows, inner_cols)
    
    return X, Y
end

# Kronecker sum: A ⊕ B ⊕ ... = A ⊗ I ⊗ ... + I ⊗ B ⊗ ... + I ⊗ I ⊗ ... + ...
kronsum{T}(A::Matrix{T}, B::Matrix{T}) = kron(A, eye(B)) + kron(eye(A), B)
kronsum{T}(A::Matrix{T}, B::Matrix{T}, C::Matrix{T}) = kron(A, eye(B), eye(C)) + kron(eye(A), B, eye(C)) + kron(eye(A), eye(B), C)
kronsum{T}(A::Matrix{T}, B::Matrix{T}, C::Matrix{T}, D::Matrix{T}) = kron(A, eye(B), eye(C), eye(D)) + kron(eye(A), B, eye(C), eye(D)) + kron(eye(A), eye(B), C, eye(D)) + kron(eye(A), eye(B), eye(C), D)

joinblocks{T}(A::Matrix{Matrix{T}}) = hcat([vcat(A[:, i]...) for i in 1:size(A, 2)]...)

# Generate a rotation matrix using the Lie algebra vector [x, y, z]
function rotation!{T}(R::Matrix{T}, x::T, y::T, z::T)
    θ = sqrt(x^2 + y^2 + z^2)
    K = [0 -z/θ y/θ ; z/θ 0 -x/θ ; -y/θ x/θ 0]
    copy!(R, I + sin(θ)*K + (1-cos(θ))*K^2)
end

# Nearest orthogonal matrix to A
function nearest_orthogonal!{T}(O::Matrix{T}, A::Matrix{T})
    F = svdfact(A)
    copy!(O, F[:U] * F[:Vt])
end

# Nearest special orthogonal matrix to A
function nearest_special_orthogonal!{T}(SO::Matrix{T}, A::Matrix{T})
    F = svdfact(A)
    D = eye(A)
    D[end, end] = det(F[:U] * F[:Vt])
    copy!(SO, F[:U] * D * F[:Vt])
end

# Memory allocating function variants
rotation{T}(x::T, y::T, z::T) = rotation!(Matrix{T}(3, 3), x, y, z)
nearest_orthogonal{T}(A::Matrix{T}) = nearest_orthogonal!(similar(A), A)
nearest_special_orthogonal{T}(A::Matrix{T}) = nearest_special_orthogonal!(similar(A), A)
