
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

function timediff(X::Matrix)
    # TODO - add a matlab-like implementation of filter
    # XD = filter([1 -1], [1], X)

    XD = diff(X, 1)
    XDD = [X[1, :] ; XD]
    return XDD
end


function timediff!(X::Matrix)
    X =  [X[1, :] ; diff(X, 1)]
end