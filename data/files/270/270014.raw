# Creates sparse spd band matrix w/ only upper triangle stored
function spgenband( m::Int64, b::Int64 )
  nnonzeros = div((2m-b)*(b+1),2)
  nzval = randn(nnonzeros)
  rowval = Array(Int64,nnonzeros)
  colptr = Array(Int64,m+1)
  k = 1
  for i = 1:m
    colptr[i] = k
    for j = max(i-b,1):i
      rowval[k] = j
      k = k+1
    end
  end
  colptr[m+1] = k
  return SparseMatrixCSC(m,m,colptr,rowval,nzval) + m*speye(m,m)
end
