# Softmax function 
softmax(x) = exp(x) ./ sum(exp(x))

# Logistic function # defined in StatsBase.logit
# logit(x) = 1/(1+exp(-x))

# Mask elements of x not in indices i to zero
function mask(x, i) 
 y = zeros(size(x)); y[i] = x[i]; y
end

# Kronecker delta 
δ = (i,j) -> i == j ? 1 : 0
