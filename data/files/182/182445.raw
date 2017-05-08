# duplication(n)
# Returns Magnus and Neudecker's duplication matrix of size n
# Luca Brugnolini 2014
# Based on Thomas P Minka (tpminka@media.mit.edu)

function duplication(n)

  a = tril(ones(n,n));
  i = find(a);
  a[i] = 1:size(i,1);       # here was length(EE)
  a = a + tril(a,-1)';
  j = vec(a);
  m = (n*(n+1)/2);
  m = itrunc(m)
  d = zeros(n*n,m)

 for r = 1:size(d,1)
     d[r, j[r]] = 1;

 end

    return d

end
