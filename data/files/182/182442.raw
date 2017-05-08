# devec.m
# Luca Brugnolini 2014
# Based on Kilian code
# For a vector (m*n,1), returns A (m,n) (see Hamilton p. 265)
# ------NOTE: pass the function the number of rows in the matrix A!!!
# code: --> A = devec(v,m)

function devec(v,m);

l = size(v,1);
n = itrunc(l/m);
A = zeros(n,n);

  for i = 1:n;
      A[:,i] =  v[((i-1)*m)+1:i*m]

  end;

    return A

end
