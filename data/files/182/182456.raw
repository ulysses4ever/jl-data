# Luca Brugnolini
# Ph.D. in Economics, Law and Institutions
# I am starting programming in Julia
# Base my code on Kilian (2009) Local Projection
# I modify the code to implement it in Julia and to improve performance
# First Draft 30/11/2
# This Version 02/12/2014
# ** Denotes some performance improvements I have implemented. If you'll find some errors try to check these parts.

#cd("C:/Users/asus/Desktop/Luke/UniversitÃ /PhD/My Paper/About Local Projection/Local Projection/MATLAB/Killian Original Code")
z = readcsv("data.csv");
tic()
DY    = z[2:end,1]; # CFNAI
DP    = (log(z[2:end,2])-log(z[1:end-1,2]))*1200;  # D(log(CPI))
DPCOM = ((log(z[2:end,3])-log(z[2:end,2])) - (log(z[1:end-1,3])-log(z[1:end-1,2])))*1200; # D(log(real PCOM)): CRB
FF    = z[2:end,4];  #FedFound

# DEMINING FOR BC BOOTSTRAP
# FULL SAMPLE (1970-2007)
DY = DY - mean(DY);
DP = DP - mean(DP);
DPCOM = DPCOM - mean(DPCOM);
FF = FF - mean(FF);
z = [DY DP DPCOM FF];
p = 12;
H = 24;

# DGP: 4-Variable VAR(12)- Output, Inflation, Real Commodity-P inf, FFrate
(irftrue, std, P, Btrue) = irfvar(z, p, H);             # IRF for DGP

# SIMULATION
(T,K) = size(z);
nmc   = 1;                                 # number of Monte Carlo trials
throw = 300;                                 # initial obs to be discarded
pbar  = 12;                                  # max lag order for AIC

# Initialization
BIASv = zeros(K^2,H+1);   MSEv  = zeros(K^2,H+1);   # point estimates
BIASl = zeros(K^2,H+1);   MSEl  = zeros(K^2,H+1);

CVGvd = zeros(K^2,H+1);   LGTvd = zeros(K^2,H+1);   # inference - delta
CVGld = zeros(K^2,H+1);   LGTld = zeros(K^2,H+1);

CVGvb = zeros(K^2,H+1);   LGTvb = zeros(K^2,H+1);   # inference - bootstrap
CVGlb = zeros(K^2,H+1);   LGTlb = zeros(K^2,H+1);

# Monte-Carlo Trials
for n = 1:nmc                                       # loop for MC traials

#---GENERATE DATA
    y = zeros(T+throw,K);
    u = randn(T+throw,K);

    for i = p+1:T+throw
    y[i,:] = (Btrue[:,1]+P*u[i,:]')';

        for jj = 1:p
        y[i,:] = y[i,:] + (Btrue[:,(jj-1)*K+2:jj*K+1]*y[i-jj,:]')';

        end

     end

    y = y[throw+1:end,:]                          # discarding initial obs

    for i=1:K                                   # demean y
        y[:,i] = y[:,i] - mean(y[:,i]);
    end

#---IRF POINT ESTIMATE AND STDEV ESTIMATED BY VAR AND LP
    pv =  varlagorder(y,pbar);            # lag-order for VAR
    (irfv, stdv, Phat, B, SIGMA, U, rfirfv, COVsig) = irfvar(y, pv, H); # IRF by VAR

    pl = lplagorder(y,pbar,H);                                       # lag-order for LP
    (irfl, stdl, rfirfl) = irflp(y, pl, H, Phat, COVsig);            # IRF by LP


#---BIAS, MSE of IRF ESTIMATES
    BIASv = BIASv + (irfv-irftrue);                    # sum of BIAS
    BIASl = BIASl + (irfl-irftrue);

    MSEv  = MSEv  + (irfv-irftrue).^2;                 # sum of squared error
    MSEl  = MSEl  + (irfl-irftrue).^2;

#---BIAS-CORRECTED BOOTSTRAP INTERVAL FOR VAR: KILLIAN -- for VAR(12)
    # translating estimates into the companion form
    A = [B[:,2:end];[eye(K*(p-1)) zeros(K*(p-1),K)]];  # slope estimate
    V = [B[:,1];zeros(K*(p-1),1)];                     # intercept
    SIGMAc = [SIGMA zeros(K,K*p-K);zeros(K*p-K,K*p)];  # sigma

# Bias correction: if the largest root of the companion matrix
# is less than 1, do BIAS correction
   eigv = abs(eigvals(A));

   if ~ any(eigv.>=1)
        A = asybc(A,SIGMAc,T,K,p);

   end

   A = real(A);

# Bias-corrected estimate is the bootstrap DGP
   CIv = boot([V[1:K,1] A[1:K,1:K*p]], U, y, p, H);
   CILv  = reshape(CIv[1,:]',H+1,K^2)';               # lower bound
   CIHv  = reshape(CIv[2,:]',H+1,K^2)';               # upper bound

#---BLOCK BOOTSTRAP INTERVAL FOR LOCAL PROJECTIONS
   block = 8;                                         # block size
   CIl = bcbootlp(y, rfirfl, SIGMA, pl, block, H);    # bootstrap interval
   CILl = reshape(CIl[1,:]',H+1,K^2)';                # lower bound
   CIHl = reshape(CIl[2,:]',H+1,K^2)';                # upper bound

#---COVERAGE RATES
    for k=1:K^2

        for h=1:H+1

            if (irftrue[k,h]>=irfv[k,h]-1.96*stdv[k,h]) && (irftrue[k,h]<=irfv[k,h]+1.96*stdv[k,h])
               CVGvd[k,h] = CVGvd[k,h]+1;

            end

            if (irftrue[k,h]>=irfl[k,h]-1.96*stdl[k,h]) && (irftrue[k,h]<=irfl[k,h]+1.96*stdl[k,h])
               CVGld[k,h] = CVGld[k,h]+1;

            end

            if (irftrue[k,h]>=CILv[k,h]) && (irftrue[k,h]<=CIHv[k,h])
               CVGvb[k,h] = CVGvb[k,h]+1;

            end

            if (irftrue[k,h]>=CILl[k,h]) && (irftrue[k,h]<=CIHl[k,h])
               CVGlb[k,h] = CVGlb[k,h]+1;

            end

        end

    end

#---AVERAGE LENGTHS
    LGTvd = LGTvd + 1.96*2*stdv;
    LGTld = LGTld + 1.96*2*stdl;
    LGTvb = LGTvb + abs(CIHv-CILv);
    LGTlb = LGTlb + abs(CIHl-CILl);
end                                              # end loop for MC trials

BIASv = BIASv/nmc;                               # BIAS
BIASl = BIASl/nmc;
MSEv  = MSEv /nmc;                               # MSE
MSEl  = MSEl /nmc;
STDv  = sqrt(MSEv-BIASv.^2);                     # stdev
STDl  = sqrt(MSEl-BIASl.^2);

CVGvd  = CVGvd/nmc;                              # coverage rates
CVGld  = CVGld/nmc;
CVGvb  = CVGvb/nmc;
CVGlb  = CVGlb/nmc;

LGTvd  = LGTvd/nmc;                              # average lengths
LGTld  = LGTld/nmc;
LGTvb  = LGTvb/nmc;
LGTlb  = LGTlb/nmc;
toc()
