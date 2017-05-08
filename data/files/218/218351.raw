
# Satisfly constrains 2 and 3 (zero mean, unit variance)
# Subtracts each column's mean (if center=true),
# divides by each column's standard deviation (if scale=true).
function whiten(X::Matrix)
    # zero mean
    X = X.-mean(X,1)

    # unit variance
    X = X./std(X,1)
    return X
end