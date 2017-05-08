# vech function
# Luca Brugnolini 2014
# Based on Kilian code

function vech(m)

# h = vech(m)
# h is the column vector of elements on or below the main diagonal of m.
# m must be square.

r = repmat(1:size(m,1), 1, size(m,2));
c = repmat((1:size(m,2))', size(m,1), 1);

# c <= r is same as tril(ones(size(m)))
h = m[find(c .<= r)];

return h

end
