function normalize(A::Matrix, dim::Int)
    if dim == 1
        A ./= repmat(sum(A,1), size(A,1), 1)
    elseif dim == 2
        A ./= repmat(sum(A, 2), 1, size(A,2))
    else
        println("dim error")
    end
    A
end
