# irflp.m
# IRF Estimates and stdev of IRF by Local Projections
# Luca Brugnolini 2014
# Based on Kilian

function irflp(z, paic, H, A0inv, COVsig)

# Input : data z, lag order paic (Hx1 vector), horizon for IRF H,
#         A0inv- relationship btw sf & rf shocks estimated from VAR
#         COVsig- variance due to A0inv, estimated from VAR
# Output: IRF, Std error of IRF, reduced form IRF

(T,K) = size(z);

# IRF estimate and STdev of IRF for Horizon 0
A1 = vec(A0inv');                                # IRF for horizon 0
A2 = vec(eye(K));                                # Reduced form IRF
COVA1 = zeros(K^2,1);                            # Std(IRF0)=0

# IRF estimate and Stdev of IRF for Horizon 1~H
 for h = 1:H
     ph = paic[h];                     # lag-order for horizon h
     ph = itrunc(ph);
     ys = z[ph+h:T,:];

    # RHS variables: lags
     yt = z[ph:T-h,:];                 # RHS variable of interest: y(t)
     x = ones(T-ph-h+1,1);             # constant term

        for i = 2:ph
            x = [x z[ph+1-i:T-i-h+1,:]];  # other RHS variables: y(t-1)~y(t-p+1)

        end

     Mx = eye(size(x,1))-x/(x'*x)*x';         # annhilation matrix
     B1 = (yt'*Mx*yt)\(yt'*Mx*ys);            # IRF by Local Projection
     A1 = [A1 vec(A0inv'*B1)];                # structural IRF
     A2 = [A2 vec(B1)];                       # reduced form IRF

     # Newey-West HAC Estimator of Stdev (truncation point is h)
     u = Mx*ys - Mx*yt*B1;                                           # residual from LPs
     meanu = [mean(u[:,1]) mean(u[:,2]) mean(u[:,3]) mean(u[:,4])];
     u0 = u-kron(ones(size(u,1),1),meanu);
     R0 = (u0'*u0)./(size(u,1));         # here was length(u)                            # R(0): smpl cov(u)
     SIGu = R0;
     M = h;                                                          # truncation point

        for j = 1:M
            Rj = (u0[1:end-j,:]'*u0[j+1:end,:])./(size(u,1));   # R(j)
            SIGu = SIGu + (1-j/(M+1))*(Rj+Rj');                 # varcov(u)

        end

     invytMxyt  = inv(yt'*Mx*yt);
     SIGB1 = kron(SIGu, invytMxyt);                               # var(vec(B1))
     SIGA1 = kron(eye(K), A0inv')*SIGB1*kron(eye(K), A0inv')';     # var(vec(A0inv*B1))
     COVA1 = [COVA1 reshape(diag(SIGA1), K^2, 1)];

end

    stdA1 = sqrt(COVA1+COVsig);                                       # STD2 is variance due to

     return A1, stdA1, A2

end
