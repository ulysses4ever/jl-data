function irfvar(y,p,H)

# Luca Brugnolini 2014
# Based on Kilian code
# Point estimates and stdev of structural IRFs identified by recursive structure
# Input : data y, lag order p, horizon for impulse response H
# Output: IRF, Std error of IRF, A0inv for structural identification,
#         slope parameter estimates B, cov matrix of estimated residual SIG
#         estimated residual U, reduced form IRF

(T,K) = size(y);

# OLS
Y = (y[p+1:T,:])';                           # LHS variable for OLS
X = ones(1,T-p);                             # constant term

for j=1:p
    X = [X; y[p+1-j:T-j,:]'];                # RHS variable for OLS

end

B   = (Y*X')/(X*X');                         # OLS estimates **
A   = B[:,2:end];                            # OLS estimates w/o intercept
U   = Y-B*X;                                 # estimated residual
SIG = (Y-B*X)*(Y-B*X)'/(T-p-p*K-1);          # estimated sigma(U)
SIGb = kron(inv(X*X'/(T-p)),SIG);            # varcov of vec(B):(K^2*p+K)^2
SIGa = SIGb[K+1:end,K+1:end];                # varcov of vec(A):(K^2*p)^2

# IRF and stdev(IRF)
#  Calculation of stdev follows Lutkepohl(2005) p.111,93
A = [A; eye(K*(p-1)) zeros(K*(p-1),K)];         # Companion form
A0inv = chol(SIG)';                              # recursive str assumption
rfIRF = zeros(K^2,H+1);                          # reduced form IRF
IRF   = zeros(K^2,H+1);                          # structural IRF
STD   = zeros(K^2,H+1);                          # stdev of structural IRF
COV2   = zeros(K^2,H+1);                         # COV of structural IRF due to SIG
J = [eye(K) zeros(K,K*(p-1))];                   # J matrix
L = elimat(K);                                   # elimination matrix
Kk = commutation(K,K);                           # commutation matrix
Hk = L'/(L*(eye(K^2)+Kk)*kron(A0inv,eye(K))*L');  # H matrix **
D = duplication(K);                              # duplication matrix
Dplus = (D'*D)\D';
SIGsig = 2*Dplus*kron(SIG,SIG)*Dplus';           # sigma(vech(sigma))
Cbar0 = kron(eye(K),J*eye(K*p)*J')*Hk;           # Cbar
rfIRF[:,1] = vec((J*eye(K*p)*J')');
IRF[:,1] = vec((J*eye(K*p)*J'*A0inv)');
STD[:,1] = vec((reshape(diag(real(sqrt(complex(Cbar0*SIGsig*Cbar0'/(T-p))))),K,K))')
COV2[:,1] = vec((reshape(diag((Cbar0*SIGsig*Cbar0'/(T-p))),K,K))');


for h=1:H
    Gi = zeros(K^2,K^2*p);

    for m=0:(h-1)
        Gi += kron(J*(A')^(h-1-m),J*(A^m)*J');
    end;

    C = kron(A0inv',eye(K))*Gi;
    Cbar = kron(eye(K),J*A^h*J')*Hk;

    rfIRF[:,h+1] = vec((J*A^h*J')');
    IRF[:,h+1] = vec((J*A^h*J'*A0inv)');
    STD[:,h+1] = vec((reshape(diag(real(sqrt(complex(C*SIGa*C'+Cbar*SIGsig*Cbar')/(T-p)))),K,K))')
    COV2[:,h+1] = vec((reshape(diag(((Cbar*SIGsig*Cbar')/(T-p))),K,K))');

end

    return IRF,STD,A0inv,B,SIG,U,rfIRF,COV2;

end
