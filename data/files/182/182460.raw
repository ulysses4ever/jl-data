# lplagorder.m
# Luca Brugnolini 2014
# Based on Kilian
# This program selects the lag order for local projections using AIC, SIC , AICC and HCQ

function lplagorder(z,pbar,H)

# Inputs : data, maximum lag order to consider, IRFs horizons
# Outputs: lag-orders for H horizons selected by AIC and SIC (Hx1 vectors)

(T,K) = size(z);
t     = T-pbar;
paic  = zeros(H,1);
# psic  = zeros(H,1);                       # FOR SIC
# paicc = zeros(H,1);                       # FOR HURVICH AND TSAI
# phqc  = zeros(H,1);                       # FOR HQ
Ys = z[pbar+1:T,:];
Yt = z[pbar:T-1,:];                  # RHS variable of interest: y(t)
X = ones(T-pbar,1);                  # constant term

    for j=2:pbar
       X = [X z[pbar+1-j:T-j,:]];           # other RHS variables: y(t-1)~y(t-p+1)

    end

    for j=1:H                                          # loop for horizon h of IRF
        AIC = zeros(pbar,1);                       # the vector of AIC(p)
        # SIC = zeros(pbar,1);                     # the vector of SIC(p)
        # AICC = zeros(pbar,1);                    # FOR HURVICH AND TSAI
        # HQC = zeros(pbar, 1);                    # FOR HQ
        ys = Ys[j:end,:];                          # dependent variable: yt+s
        yt = Yt[1:end-j+1,:];                      # regressor of interest: yt

    for m=1:pbar                             # loop for lag order selection
        x = X[1:end-j+1,1:(m-1)*K+1];        # other independent variables
        Mx = eye(size(x,1))-x/(x'*x)*x';     # annhilation matrix **
        B1 = (yt'*Mx*yt)\(yt'*Mx*ys);        # IRF by Local Projection **
        U = Mx*ys - Mx*yt*B1;                # residual from LPs
        SIG = U'*U/t;                        # variance of errors
        # b = t/(t-(m*K+K+1));
        AIC[m]  = log(det(SIG)) + 2*(K^2*m)/t;                        # AIC statistic
        # SIC[m]  = log(det(SIG)) + (K^2*m)*log(t)/t;                 # SIC statistic
        # AICC[m] = t*(log(det(SIG))+K) + 2*b*(K^2*m+K*(K+1)/2);      # FOR HURVICH AND TSAI
        # HQC[m]  = log(det(SIG)) + 2*log(log(t))*K^2*m/t;            # FOR HQ
    end

        paic[j] = indmin(AIC)                      # paic is the lag-order by AIC
        # psic[j]  = indmin(SIC);                  # paic is the lag-order by AIC
        # paicc[j] = indmin(AICC);                 # FOR HURVICH AND TSAI
        # phqc[j]  = indmin(HQC);                  # FOR HQ

    end

return paic

end
