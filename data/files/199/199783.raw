module GramSchmidt

export gram_schmidt

# Runs the Gram-Schmidt algorithm for the given set of vectors.
#
# parameters:
#   A   - An array of column vectors 
#
# returns:
#   If 'A' is a set of n linearly independent vectors, then 
#   gram_schmidt returns an array n of orthonormal vectors.
#
#   If 'A' is not a set of linearly independent vectors, then
#   gram_schmidt returns an array of m < n vectors.
#
# usage:
#   julia> gram_schmidt({[1;0],[0;1][1;1]})
#   1-element Array{Any,1}:
#   [1.0,0.0]
#
#   julia> gram_schmidt({[1;0;0],[0;1;0],[0;0;1]})
#   3-element Array{Any,1}:
#    [1.0,0.0,0.0]
#    [0.0,1.0,0.0]
#    [0.0,0.0,1.0]
#    
function gram_schmidt(A)
  epsilon = 1e-6
  k = length(A)
  n = length(A[1])
  qs = {}
  for i = 1:k
    q_i = A[i]
    # orthogonalization with previous vectors
    for j = 1:length(qs)
      q_i -= (qs[j]'A[i]).*qs[j]
    end
    # check for dependence, quit if q_i ~= 0
    if norm(q_i) <= epsilon
      break
    end
    # normalize and store the result
    q_i = q_i/norm(q_i)
    push!(qs,q_i)
  end
  return qs
end

end
