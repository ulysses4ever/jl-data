############
# Linear Regression Model 
# Using Gradient Descent for Regression Modeling
# Date: August 16, 2015
# Author: Paul Stey
############


function sq_error_loss(X, y, beta, n)
    h = X*beta
    J = 1/(2n) * sum((h-y).^2)

    return J
end


function gradient_des(X, y, beta, a, iters)
    ## a is our learning rate or step size
    ## iters is the max number of iterations

    n, p = size(X)
    tmp = zeros(p)
    j_hist = zeros(iters)

    for i = 1:iters
        for j = 1:p
            tmp[j] = beta[j] - a * (1/n) * sum((X*beta - y).*X[:, j])  
        end
        beta = tmp                                # update parameter estimates

        j_hist[i] = sq_error_loss(X, y, beta, n)

        if i > 1 && abs(j_hist[i] - j_hist[i-1]) < 0.0001
            break
        end
    end

    return beta
end


function lmfit(X, y, intercpt = true, a = 0.01, iter = 1000)
    n = length(y)
    if intercpt
        X = [ones(n) X]
    end

    p = size(X, 2)
    beta = zeros(p)                                # initialize param est.
    beta = gradient_des(X, y, beta, a, iter)

    return beta
end

# simulate some data
X = randn(1000, 5)
X = [ones(1000) X]
beta = [1, 2, 1, 2, 3, 4]

y = X*beta + randn(1000)

lmfit(X, y, false, 0.005, 1500)
