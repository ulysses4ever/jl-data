# irflpest.m
# Luca Brugnolini 2014
# Based on Kilian code
# This function estimates reduced form IRFs by local projections

function irflpest(ys, yt, x)

# Input : dependent variables ys, lagged RHS variables (yt and x)
# Output: rf IRF for each horizon (K by K)
# Impulse Response by Local Projection

Mx = eye(size(x,1))-x/(x'*x)*x';         # annhilation matrix
B1 = (yt'*Mx*yt)\(yt'*Mx*ys);            # rf IRF by Local Projection


return B1

end
