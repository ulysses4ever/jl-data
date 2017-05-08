############
# Linear Regression Model 
# Using Gradient Descent for Regression Modeling
# Date: August 16, 2015
# Author: Paul Stey
############



function sq_error_loss(X, y, beta, n)
	## X is our matrix of predictors
	## y is our outcome
	## beta is our matrix of regression coefs.

	h = X*beta

	J = 1/(2*n) * sum((h-y).^2)

	return J
end




function gradient_des(X, y, beta, alpha, iters)
	## X is our matrix of predictors
	## y is our outcome
	## beta is our matrix of regression coefs.
	## alpha is our learning rate or step size
	## iters is the max number of iterations

    n, p = size(X)

    tmp = zeros(p)

    j_hist = zeros(iters)

    for i = 1:iters

    	for j = 1:p

        	tmp[j] = beta[j] - alpha * (1/n) * sum((X*beta - y).*X[:, j])  
        end

        ## update parameter estimates
        beta = tmp

        j_hist[i] = sq_error_loss(X, y, beta, n)

        if i > 1 && abs(j_hist[i] - j_hist[i-1]) < 0.0001

        	break
        end
    end

    return beta
end




function linreg(X, y)

	p = size(X, 2)

	beta = zeros(p)	  							# initialize param est.

	a = 0.01  									# learning rate

	iter = 1000   								# max iterations

	beta = gradient_des(X, y, beta, a, iter)

	return beta
end




###
# simulate some data
###

X = randn(1000, 5)

X = [ones(1000) X]

beta = [1, 2, 1, 2, 3, 4]

y = X*beta + randn(1000)



linreg(X, y)



