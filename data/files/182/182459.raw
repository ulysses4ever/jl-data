# irfvar1.m AAA
# Luca Brugnolini 2014
# Based on Kilian code
# This function gives impulse response estimates by VAR

function irfvar1(A, SIGMA, p, H)

# Input : Slope parameter estiamtes, variance of estimated residual,
#         lag order, impulse response horizons
# Output: IRF estimates

K = size(SIGMA,1);
A = [A;[eye(K*(p-1)) zeros(K*(p-1),K)]];   # translating to companion form
J = [eye(K,K) zeros(K,K*(p-1))];
P = chol(SIGMA)';                          # recursive structure assumption
IRF = reshape((J*A^0*J'*P)',K^2,1);

for i = 1:H
IRF = [IRF reshape((J*A^i*J'*P)',K^2,1)];

end

    return IRF

end
