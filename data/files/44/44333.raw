function cur(A, nSamples)
  """
  C,U,R = cur(A, nSamples) calculates a low rank approximation C*U*R of A,
  where C and R consists of columns of A which preserves sparsity and interpretability.
  Based on the paper "CUR Matrix Decompositions for Improved Data Analysis" by Mahoney and Drineas, 2008.
  """
  rowPDF = getprobabilities(A)
  colPDF = getprobabilities(A')
  rowCDF = cumsum(rowPDF)
  colCDF = cumsum(colPDF)

  chosenRows = getsamples(rowCDF, nSamples)
  chosenCols = getsamples(colCDF, nSamples)

  C = A[:,chosenCols]
  U = pinv(full(A[chosenRows,chosenCols]))
  R = A[chosenRows,:]
  return C,U,R
end

function getprobabilities(A)
  nRows = size(A)[1]
  rowPDF = zeros(nRows)
  for i = 1:nRows
    rowPDF[i] = vecnorm(A[i,:])
  end
  rowPDF = rowPDF/vecnorm(A)
  return rowPDF
end

function getsamples(cdf, N)
  samples = zeros(N)
  for k in 1:N
    r = rand()
    k2 = 1
    while(cdf[k2] < r)
      k2 = k2 + 1
    end
    samples[k] = k2
  end
  return samples
end

print("\ntesting cur(A)\n")
A = rand(2,3)
C,U,R = cur(A,2)
print((C,U,R))

print("\ntesting cur(::sparse S)\n")
S = sparse(A)
C,U,R = cur(A,2)
print((C,U,R))
