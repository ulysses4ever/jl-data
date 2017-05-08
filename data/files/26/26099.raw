function kronshuffle!{T<:Number}(B::Matrix{T}, A::Matrix{T}, outer_rows::Int, outer_cols::Int, inner_rows::Int, inner_cols::Int)
    for or in 1:outer_rows, oc in 1:outer_cols, ir in 1:inner_rows, ic in 1:inner_cols
        B[outer_rows * (oc-1) + or, inner_rows * (ic-1) + ir] = A[inner_rows * (or-1) + ir, inner_cols * (oc-1) + ic]
    end
    
    return B
end

kronshuffle{T<:Number}(A::Matrix{T}, outer_rows::Int, outer_cols::Int, inner_rows::Int, inner_cols::Int) = kronshuffle!(Matrix{T}(outer_rows * outer_cols, inner_rows * inner_cols), A, outer_rows, outer_cols, inner_rows, inner_cols);

function kronfactor{T<:Number}(A::Matrix{T}, outer_rows::Int, outer_cols::Int, inner_rows::Int, inner_cols::Int)
    F = svdfact(kronshuffle(A, outer_rows, outer_cols, inner_rows, inner_cols))
    X = reshape(sqrt(F[:S][1]) * F[:U][:, 1], outer_rows, outer_cols)
    Y = reshape(sqrt(F[:S][1]) * F[:V][:, 1], inner_rows, inner_cols)
    
    return X, Y
end
