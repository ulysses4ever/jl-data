# olsvar.m
# Luca Brugnolini 2014
# Based on Kilian code

function olsvar(y,p)

# Input : data y, lag order p
# Output: coefficient estimate B, estimate of Cov(U), residual U

(T,K) = size(y);
Y = (y[p+1:T,:])';                     # LHS variable
X = ones(1,T-p);                       # constant term

for j=1:p                              # RHS variable
    Z = [y[p+1-j:T-j,:]]';
    X = [X;Z];

end

B = (Y*X')/(X*X');                     # OLS estimator
U = Y-B*X;                             # estimated residuals
SIGMA = U*U'/(T-p-p*K-1);              # estimated variance of disturbances

return B, SIGMA, U

end
