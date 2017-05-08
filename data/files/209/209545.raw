#########
# EM Algorithm
# Param. estimation with missing data
# Date: August 15, 2015
# Author: Paul Stey
#########

using DataArray
using Distributions

function loglk(y, mu, sig2, n)
    soln = -0.5*n*log(2*pi*sig2) - 0.5*sum((y - mu).^2)/sig2
    return soln
end


function em_norm(y, thresh = 0.001)
    n = length(y)
    yobs = dropna(y)
    n_mis = n - length(yobs)
    mut = 0
    sit = 1
    lltm1 = loglk(yobs, mut, sit, n)
    iterate = true

    while iterate
        ## E-step
        EY = sum(yobs) + n_mis*mut
        EY2 = sum(yobs.^2) + n_mis*(mut^2 + sit)

        ## M-step
        mut1 = EY/n
        sit1 = EY2/n - mut1^2

        mut = mut1                                  # update estimates
        sit = sit1
        llt = loglk(yobs, mut, sit, n)              # re-compute loglikelihood
        println(mut, ' ', sit, ' ', llt)            # track progress
        if abs(lltm1 - llt) < thresh 
            iterate = false
        end
        lltm1 = llt
    end
    return [mut, sqrt(sit)]                         # return mean and SD
end



# Simuation

gauss = Normal(100, 10)                             # set up distribution
x = rand(gauss, 25)                                 # simulate data
x = DataArray(x)

x[1:7] = NA                                         # make data missing


em_norm(x)
