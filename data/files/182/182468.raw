# varlagorder.m
# This program selects the lag order for VAR using the AIC, SIC, AICC, HQC
# Luca Brugnolini 2014
# Based on Kilian

function varlagorder(z,pbar)

# Inputs : data, maximum lag order to consider
# Outputs: lag-orders selected by the AIC, SIC, AICC and HQC

(T,K) = size(z);
t     = T-pbar;
AIC   = zeros(pbar,1);
# SIC   = zeros(pbar,1);
# AICC  = zeros(pbar,1);
# HQC   = zeros(pbar,1);
Y = z[pbar+1:T,:];                           # dependent variable

    for p = 1:pbar
        X = ones(t,1);

        for i = 1:p
           X = [X z[pbar+1-i:T-i,:]]              # construct lagged regressors

        end

        beta  = (X'*X)\(X'*Y);                    # estimate by multivariate LS **
        U     = Y-X*beta;                         # errors
        sig   = U'*U/t;                           # variance of errors
        # b = t/(t-(p*K+K+1));                    # COEFFICIENT FOR AICC
        AIC[p]     = log(det(sig))+2*p*K^2/t;                      # AIC statistic
        # SIC[p]   = log(det(sig))+(K^2*p)*log(t)/t;                # SIC statistic
        # AICC[p] = t*(log(det(sig))+K)+2*b*(K^2*p+K*(K+1)/2);     # AICC
        # HQC[p]   = log(det(sig))+2*log(log(t))*K^2*p/t; # HQC

    end

pa   = indmin(AIC);   paic  = pa;                       # paic is the lag-order by AIC
# ps   = indmin(SIC);   psic  = ps;                     # psic is the lag-order by SIC
# pac  = indmin(AICC); paicc = pac;                     # paicc is the lag-order by AICC
# hqc  = indmin(HQC);   phqc  = hq;                     # phqc is the lag-order by HQC

return paic

end
