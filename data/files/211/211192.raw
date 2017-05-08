function unfold(A,n::Integer)
    R = n
    C = setdiff(1:ndims(A), n)
    I = size(A)
    J = prod(I[R])
    K = prod(I[C])
    Y = reshape(permutedims(A,[R,C]), J,K)
    return Y
end

function fold(m,dims,n::Integer)
    R = n
    C = setdiff([1:length(dims)], R)
    I = dims 
    I[n] = size(m)[1]
    J = prod(I[R])
    K = prod(I[C])
    axes = [I[R] I[C]]
    return permutedims((m,axes),axes)
end
