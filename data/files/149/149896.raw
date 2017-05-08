# create response (y) and matrix of covariates (x)
x1  = [4.17,5.58,5.18,6.11,4.50,4.61,5.17,4.53,5.33,5.14];
y = [4.81,4.17,4.41,3.59,5.87,3.83,6.03,4.89,4.32,4.69];
a = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1];
x = reshape([a, x1], 10, 2);

# fit minimal linear model (method = "qr" default)
# minlmfit return a MinLmfit type object
mylm = minlmfit(x, y)

# extract characteristics of interest from MinLmfit object
# corr is the scaled vcov matrix, i.e., inv(x'*x)
coef(mylm)
residuals(mylm)
resid(mylm)
corr(mylm)

Pkg.clone("git://github.com/jpfrench81/GeoLM.jl.git")