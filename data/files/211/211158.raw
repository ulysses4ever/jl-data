#=
function cpals(X;R=-1,init="singular",iterations=10)
  N=X.ndi

  if R==-1
    R=minimum(size(X))
  end
  if init=="random"
    A=[randn(size(X)[n],R) for n in 1:N]
  elseif init=="singular":
        A=hosvd(X,R=repmat([R],N)).matrices
  end
  for n in 1:N
    for i in size(A[n])[2]
      A[n][:,i]=A[n][:,i]/norm(A[n][:,i])
    end
  end

  for itr in 1:terations:
      for n in 1:N
          V=reduce(schurprod, [A[i]'*A[i] for i in [[1:n],[n+1:N]])
      end
        An=reduce(kr, [A[i] for i in [[N:-1:n-1],[n-2:-1:1]]])
        A[n]=X.unfold(n)*An*la.pinv(V)
        l=[la.norm(A[n][:,i]) for i in range(A[n].shape[1])]
        for i in range(A[n].shape[1]):
            A[n][:,i]=A[n][:,i]/l[i]
        end
      end
  end

  return [l,A]
end

function kruskal2Tensor(l,A)
    terms=[]
    for r in xrange(A[0].shape[1])
        term=l[r]*outer([A[n][:,r] for n in xrange(len(A))])
        terms.append(term)
    end
    return Tensor(sum(terms))
end

schurprod(A,B) = A.*B
#"Computes Khatri-Rao product of two matrices"
kr(A,B) = hcat([kron(A[:,k],B[:,k]) for k in 1:size(A,2)])

=#
