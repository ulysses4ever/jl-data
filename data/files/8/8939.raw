type SGDRegressor
    weights::Array{Float64,2}
    bias::Float64
    params::Dict
end


function fit(::Type{SGDRegressor}, X::Matrix{Float64}, y::Array,
             shuffle=true, lr=0.01, n_iter=500)
    params = Dict("shuffle"=>shuffle, "lr"=>lr, "n_iter"=>n_iter)
    lm = SGDRegressor(randn(size(X)[1])', 0.0, params)
    inds = 1:endof(y)
    if shuffle
        inds = collect(inds)
    end
    for i = 1:n_iter
        if shuffle
            shuffle!(inds)
        end
        for j = inds
            pred = predict(lm, X[:, j:j])[1]
            lm.weights -= lr* (pred - y[j]) * X[:, j]'
            lm.bias -= lr * (pred - y[j])
        end
    end
    return lm
end

function predict(lm::SGDRegressor, X::Matrix{Float64})
    return lm.weights * X + lm.bias
end

X = randn(10,1000)
w = randn(10)'
y = w * X + 5
