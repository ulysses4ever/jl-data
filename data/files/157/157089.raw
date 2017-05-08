function ichol(K, D, T)
  # Based on http://www.kernel-methods.net/matlab/algorithms/cholesky.m
  #
  # Performs incomplete cholesky of the kernel matrix K.
  #
  # This is very handy as it gives an approximate rank T decomposition of a
  # DxD pos.def. matrix in O(T^2 D) steps instead of O(D^3). Why not at least O(D^2)?
  # because it doesn't even need to evaluate all the entries of K, hence passing it
  # lazily as a function not a matrix. As a result it's sort of quick and dirty, but
  # seems to do OK on a bunch of kernel methods stuff.
  # Main thing is that it's linear in the amount of data.
  #
  #INPUTS
  # K = the kernel matrix, given lazily as a function (Int,Int)->Float
  # D = size of K
  # T = rank of the approximation
  #
  #OUTPUTS
  # R = the T first cholesky components of K
  # K =approx= R^T R
  # unlike the exact cholesky, R is not exactly upper triangular.
  R = zeros(T,D)
  d = zeros(D)
  for i = 1:D
      d[i] = K(i,i)
  end
  for j = 1:T
    a, I = findmax(d)
    for i = 1:D
      x = K(I,i)
      for t = 1:T
        x -= R[t,i]*R[t,I]
      end
      v = x / sqrt(a)
      R[j,i] = v
      d[i] -= v*v
    end
  end
  R
end
