# Matrix tools for work on MCL with Julia
# Berkeley 2015 - Maxime Legrand

"""Matrix shuffle
Input : A, square matrix
Output : B, A with a shuffle applied to its base of representation 
    (vertices in the case of an adjacency matrix)"""
function mat_shuffle(A)
    n = size(A,1)
    v = shuffle([1:n])
    B = [A[v[i],v[j]] for i=1:n, j=1:n]
    return B
end

"""SBM clusters
Input : l, vector of clusters lengths
Output : C, corresponding vector of clusters (for SBM)"""
function sbm_clust(l)
    K = length(l)
    C = Vector[]
    s = 1
    for k = 1:K
        push!(C, [s:(s+l[k]-1)])
        s += l[k]
    end
    return C
end