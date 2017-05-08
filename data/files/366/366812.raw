# Matrix tools for work on MCL with Julia
# Berkeley 2015 - Maxime Legrand

"""Matrix permutation
Input : A, square matrix
    perm, permutation vector (set to shuffle([1:size(A,1)]) to retrieve the former mat_shuffle
    rev, boolean
Output : A with perm applied to its base of representation 
    (set rev to true to apply reverse permutation)"""
function mat_perm(A, perm; rev=false)
    n = size(A,1)
    if rev
        return [A[perm[i],perm[j]] for i=1:n, j=1:n]
    else
        B = zeros(n,n)
        for i = 1:n
            for j = 1:n
                B[perm[i],perm[j]] = A[i,j]
            end
        end
        return B
    end
end

"""Matrix shuffle
Input : A, square matrix
Output : B, A with a shuffle applied to its base of representation 
    (vertices in the case of an adjacency matrix)"""
function mat_shuffle(A)
    return mat_perm(A,shuffle([1:size(A,1)]))
end

"""Vectors vector permutation
Input : C, vectors vector
perm, integers permutation vector
Output : Cp, C of which elements have been applied the given permutation"""
function vv_perm(C, perm)
    K = size(C,1)
    Cp = Vector[]
    for k = 1:K
        push!(Cp, map(x -> perm[x], C[k]))
    end
    return Cp
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