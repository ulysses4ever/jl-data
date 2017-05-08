# bcbootlp.m
# Luca Brugnolini 2014
# Based on Kilian code
# This function gives bias-corrected blocks-of-blocks bootstrap 95%inverval
# for IRF by LP.
# Bias is estimated by bootstrap from the original data.
# For structural-form IRFs, bootstrap replication of SIGMA* is drawn from
# the asymptotic distribution of SIGMA hat estimated by VAR

function bcbootlp(z, rfirfl, SIGMA, paic, block, H)

# Input : data, reduced form IRF estimated by LP
#         SIGMA hat estimated from VAR, lag-order (Hx1 vector)
#         size of blocks for consecutive draws
# Output: bias-corrected blocks-of-blocks bootstrap 95% confidence interval

(T,K) = size(z);

#  Bootstrap for bias estimation
bias = zeros(K^2, H+1);

    for h = 1:H

        p = paic[h];                      # lag-order for horizon h
        p = itrunc(p);

        # Creating blocks of data from which bootstrap sample will be drawn
        # To preserve serial correlation of original data
        ys = z[p+h:T,:];                  # LHS variable: y(t+1)~y(t+H)
        yt = z[p:T-h,:];                  # RHS variable of interest: y(t)
        x = ones(T-p-h+1,1);                # constant term

        for i = 2:p
            x = [x z[p+1-i:T-i-h+1,:]];   # other regressor:y(t-1)~y(t-p+1)

        end

        bias[:,h+1] = boot_biaslp(ys, yt, x, rfirfl[:,h+1], block, 0);

    end

#  Bootstrap simulation for CI
nrep = 100;                             # number of bootstrap replications 2000
IRFrmat = zeros(nrep,K^2*(H+1));       # IRF for each bootstrap replication

     for j = 1:nrep                         # Starting bootstrap cycle
         IRFr = zeros(K^2,H+1);

         # Drawing SIGMA* from asymptotic distribution of SIGMA hat
         D = duplication(K);                                                    # duplication matrix
         Dplus = (D'*D)\D';                                                     # ***
         SIGSIG = 2*Dplus*kron(SIGMA,SIGMA)*Dplus';                             # SIGMA(vech(SIGMA))
         m = sum(1:K);                                                          # number of draws
         vechSIGMAr = chol(SIGSIG)'*randn(m,1)/sqrt(T)+vech(SIGMA);             # SIGMA(vech(SIGMA*))
         vecSIGMAr = duplication(K)*vechSIGMAr;                                 # vec(SIGMA*)
         SIGMAr = devec(vecSIGMAr,K);                                           # recover SIGMA*
         Pr = chol(SIGMAr)';                                                    # A0inv*
         IRFr[:,1] = vec(Pr');                                                  # IRF for horizon 0

         for h = 1:H                           # Horizons cycle
             p = paic[h];                      # lag-order for horizon h
             p = itrunc(p);

             # Creating blocks of data from which bootstrap sample will be drawn
             # To preserve serial correlation of original data
             ys = z[p+h:T,:];                  # LHS variable: y(t+1)~y(t+H)
             yt = z[p:T-h,:];                  # RHS variable of interest: y(t)
             x = ones(T-p-h+1,1);              # constant term

             for i = 2:p
                 x = [x z[p+1-i:T-i-h+1,:]];   # other regressor:y(t-1)~y(t-p+1)

             end

         # Drawing blocks of bootstrap data from the blocks of original data
         # ysr = []; ytr = []; xr = [];
         pos = ceil(rand()*(size(ys,1)-block))+1;
         ysr = ys[pos:pos+block-1,:];
         ytr = yt[pos:pos+block-1,:];
         xr  = x[pos:pos+block-1,:];

         for ii = 1:ceil(size(ys,1)/block)                               # Here was length(ys)
             pos = ceil(rand()*(size(ys,1)-block))+1;
             ysr = [ysr; ys[pos:pos+block-1,:]];
             ytr = [ytr; yt[pos:pos+block-1,:]];
             xr  = [xr; x[pos:pos+block-1,:]];

         end

        IRFr[:,h+1] = vec(Pr'*(irflpest(ysr, ytr, xr)-reshape(bias[:,h+1], K, K)));     # bias correction

     end                                                 # End horizons cycle

     IRFrmat[j,:] = vec(IRFr')';

end                                                   # End bootstrap cycle


# Calculate 95 percent interval endpoints
CILl = zeros(1,size(IRFrmat,2));
CIHl = zeros(1,size(IRFrmat,2));

for i = 1:size(IRFrmat,2)
    CILl[:,i] = quantile(vec(IRFrmat[:,i]),0.025);
    CIHl[:,i] = quantile(vec(IRFrmat[:,i]),0.975);

end

CI = [CILl; CIHl];

        return CI

end
