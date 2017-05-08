# boot_biaslp.m
# Luca Brugnolini 2014
# Based on Kilian code

# This function gives bootstrap bias estimates for each horizon of LP

function boot_biaslp(ys, yt, x, rfirf, block, sub)

# Input : dependent variables ys, lagged RHS variables (yt and x)
#         vec(reduced form IRF by LP) for a certain horizon
#         sub=1: sub-bootstrap (need to draw from pre-selected blocks)
#         sub=0: 1st round bootstrap (standard blocks-of-blocks bootstrap)
# Output: bias estimates for each horizon (K^2 by 1)

(T,K) = size(yt);

#  Bootstrap simulation for bias estimation
if sub == 0 nrep = 100                                # number of bootstrap replications sub==0 1000

elseif sub ==1  nrep = 100;                          # number of bootstrap replications sub==1 500

end

IRFrmat = zeros(nrep,K^2);               # IRF for each bootstrap replication

for j = 1:nrep
    pos = ceil(rand()*(size(ys,1)-block))+1;
    ysr = ys[pos:pos+block-1,:];
    ytr = yt[pos:pos+block-1,:];
    xr  = x[pos:pos+block-1,:];

# I  DO NOT UNDERSTAND THE TWO FOR CYCLE for ii BECAUSE THERE ARE NO ii IN THE CODE

if sub == 1

   for ii = 1:ceil(T/block)
   pos = block*ceil(rand()*(T/block-1))+1;
   ysr = [ysr; ys[pos:pos+block-1,:]];
   ytr = [ytr; yt[pos:pos+block-1,:]];
   xr  = [xr ;  x[pos:pos+block-1,:]];

   end

elseif sub == 0

       for ii = 1:ceil(size(ys,1)/block)
       pos = ceil(rand()*(size(ys,1)-block))+1;
       ysr = [ysr; ys[pos:pos+block-1,:]];
       ytr = [ytr; yt[pos:pos+block-1,:]];
       xr  = [xr ;  x[pos:pos+block-1,:]];

       end

end

    IRFrmat[j,:] = vec(irflpest(ysr, ytr, xr));         # IRF by LP for 1~H

end

bias = (mean(IRFrmat,1))'-rfirf;                        # bias estimates

return bias

end
