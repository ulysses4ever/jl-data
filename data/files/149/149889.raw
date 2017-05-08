# define type for storage of results
type MinLmfit <: RegressionModel
    coeff::Vector	# ols regression coefficients
    resid::Vector	# ols residuals
	xtxi::Array		# inv(x'*x)	
end

# create minimal function performing a regression of the vector y
# on the matrix of predictors x.  Model can be fit using either
# the qr decomposition approach (method = "qr") or the cholesky decomposition 
# approach (method != "qr").
function minlmfit(x::Array, y::Vector, method::String)
    if(method == "qr")
    	(Q, R) = qr(x)
		coeff = R\(Q'*y)
	else
		R = chol(x'*x)
		coeff = R\(R'\(x'*y))
    end
    
	Ri = inv(R)
	xtxi = Ri*Ri'
	res = y - x*coeff
    
    MinLmfit(coeff, res, xtxi)
end
# default method is qr for minlmfit
minlmfit(x::Array, y::Vector) = minlmfit(x, y, "qr") 

# create helper functions to extract components of MinLmfit type
coef(x::MinLmfit) = x.coeff # extract estimated coefficients
residuals(x::MinLmfit) = x.resid # extract residuals
# shorter function name for extracting residuals
function resid(x::MinLmfit)
	x.resid
end

# extract xtxi (the correlation of the estimated regression coefficients)
function corr(x::MinLmfit)
	x.xtxi
end

x1  = [4.17,5.58,5.18,6.11,4.50,4.61,5.17,4.53,5.33,5.14]
y = [4.81,4.17,4.41,3.59,5.87,3.83,6.03,4.89,4.32,4.69]
a = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
x = reshape([a, x1], 10, 2)

myfit = minlmfit(x, y, "qr")
minlmfit(x, y)

coef(myfit)
residuals(myfit)
resid(myfit)
corr(myfit)