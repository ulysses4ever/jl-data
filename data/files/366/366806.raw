# Matrix tools for work on MCL with Julia
# Berkeley 2015 - Maxime Legrand

"""Matrix shuffle
Input : A square matrix
Output : B with a shuffle applied to its base of representation 
    (vertices in the case of an adjacency matrix)"""
function mat_suffle(A)
    n = size(B,1)
    v = shuffle([1:n])
    B = [A[v[i],v[j]] for i=1:n, j=1:n]
    return B
end