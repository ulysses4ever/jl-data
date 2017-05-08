function spgenspd( n, p )
  nzval = Float64[]
  rowval = Int64[]
  colptr = Array(Int64,n+1)
  k = 1
  for j = 1:n
    colptr[j] = k
    push!(rowval, j)
    push!(nzval, randn() + n)
    k = k+1
    for row in randsubseq(1:j-1,p)
      push!(nzval, randn())
      push!(rowval, row)
      k = k+1
    end
  end
  colptr[n+1] = k
      
  return SparseMatrixCSC(n,n,colptr,rowval,nzval)
end

function genspd( n )
  A = randn(n,n)
  A = A+A' + n*eye(n)
  return A
end
