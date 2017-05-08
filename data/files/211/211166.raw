type KruskalOperator{T}
  lambdas::Array{T}
  vectors::Array{Matrix{T}}
end

function cpals(X::AbstractArray, rank::Int64; iterations::Int64=100)
  N=ndims(X)
  # Initialize matrices
  A = [randn(size(X,n), rank) for n in 1:N]

  # Normalize column vectors
  for n in 1:N
    for i in size(A[n],2)
      A[n][:,i] = A[n][:,i]/norm(A[n][:,i])
    end
  end

  lambdas=[]
  for itr in 1:iterations
    for n in 1:N
      #reduce(schurprod, [A[i]'*A[i] for i in [[1:n-1],[n+1:N]]])
      V = A[1]'*A[1]
      for i in [[2:n-1],[n+1:N]]
        V .*= A[i]'*A[i]
      end
      An = reduce(kr, [A[i] for i in [[N:-1:n+1],[n-1:-1:1]]])
      A[n] = unfold(X,n)*An*pinv(V)
      lambdas = [norm(A[n][:,i]) for i in 1:size(A[n],2)]
      for i in 1:size(A[n],2)
        A[n][:,i] = A[n][:,i]/lambdas[i]
      end
    end
  end
  return KruskalOperator(lambdas,A)
end

function reconstruct(ko::KruskalOperator; rank::Int64=size(ko.vectors[1],2))
  T = ko.lambdas[1]*outer([ko.vectors[n][:,1] for n in 1:length(ko.vectors)]...)
  for r in 2:rank
    T += ko.lambdas[r]*outer([ko.vectors[n][:,r] for n in 1:length(ko.vectors)]...)
  end
  T
end

schurprod(A,B) = A.*B

# Computes Khatri-Rao product of two matrices
kr(A,B) = hcat([kron(A[:,k],B[:,k]) for k in 1:size(A,2)]...)

# Computes outer product of vectors
function outer(args...)
  if all(i->ndims(i)==1, args)
    return reshape(foldr(kron, reverse(args)), map(length, args)...)
  else
    error("all arguments have to be one dim arrays")
  end
end
