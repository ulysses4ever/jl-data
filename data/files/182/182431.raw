# boot.m
# Luca Brugnolini 2014
# Based on Kilian code
# This function gives the Kilian bootstrap inverval for IRF by VAR

function boot(A, u, y, p, H)

# Input : Parameter estimates(intercept,slope), estimated residual, data
# Output: Bias-corrected bootstrap 95% confidence interval (Kilian 1999)

(T,K) = size(y);
nrep = 100;                              # number of bootstrap replications 2000
IRFrmat = zeros(nrep, K^2*(H+1));       # IRF for each bootstrap replication
u = u*sqrt((T-p)/(T-p-K*p-1));          # rescaling residual (Stine, JASA 1987)

#  Bootstrap simulation

 for j = 1:nrep

    # Draw block of initial pre-sample values
    yr = zeros(K,T);                             # bootstrap data
    pos = itrunc((rand()*(T-p+1)))+1;            # position of initial draw
    yr[:,1:p] = y[pos:pos+p-1,:]';               # drawing pre-sample obs

    # Draw innovations
    ur = zeros(K,T);                             # bootstrap innovations
    index = itrunc((rand(T-p)*(T-p))+1);         # index for innovation draws
    ur[:, p+1:T] = u[:, index];                  # drawing innovations

    # Recursively construct sample

    for i = p+1:T
            yr[:,i] = A[:,1]+ur[:,i];

        for jj = 1:p
            yr[:,i] = yr[:,i] + A[:,(jj-1)*K+2:jj*K+1]*yr[:,i-jj];

        end

    end

    yr = yr';

    for i=1:K                                   # demean yr bootstrap data
        yr[:,i] = yr[:,i] - mean(yr[:,i]);

    end

    # pbar = 4;
    # pr = varlagorder(yr,pbar);                 # lag-order selection for bootstrap data
    pr = p;
    (A1r,SIGMA1r) = olsvar(yr,pr);
    Ar = [A1r[:,2:end]; [eye(K*(pr-1)) zeros(K*(pr-1),K)]];   # Slope parameter estimates in companion form
    SIGMAr = [SIGMA1r zeros(K,K*pr-K); zeros(K*pr-K,K*pr)];   # variance of residuals in companion form

# Bias correction: if the largest root of the companion matrix
# is less than 1, do BIAS correction

if ~ any(abs(eigvals(Ar)).>=1)
     Ar = asybc(Ar,SIGMAr,T,K,pr);

end

    Ar = real(Ar)
    IRFr = irfvar1(Ar[1:K,1:K*pr], SIGMAr[1:K,1:K], pr, H);
    IRFrmat[j,:] = vec(IRFr')';

    end;                              # end bootstrap

# Calculate 95 perccent interval endpoints
CILv = zeros(1,size(IRFrmat,2));
CIHv = zeros(1,size(IRFrmat,2));

for i = 1:size(IRFrmat,2)
    CILv[:,i] = quantile(vec(IRFrmat[:,i]),0.025);
    CIHv[:,i] = quantile(vec(IRFrmat[:,i]),0.975);

end

CI = [CILv; CIHv];

                return CI

end
