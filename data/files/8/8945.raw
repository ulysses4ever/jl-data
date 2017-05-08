type SGDRegressor
    weights::Vector{Float64}
    bias::Float64
    SGDRegressor() = new(Vector{Float64}(), 0)
end


function fit!(lm::SGDRegressor, X::Matrix{Float64}, y::Vector{Float64},
              loss='squared_loss', penalty='l2', alpha=0.0001,
              l1_ratio=0.15, fit_intercept=true, n_iter=5, shuffle=True,
              verbose=0, epsilon=0.1, learning_rate='constant', eta0=0.01,
              power_t=0.25)
    lm.weights = randn(size(X)[2])
    lm.bias = 0.0
    inds = 1:endof(y)
    if shuffle:
        inds = collect(inds)
    for i = 1:n_iter
        if shuffle:
            shuffle!(inds)
        for j = inds
            pred = predict(lm, X[j, :])[1]
            lm.weights -= eta0 * (pred - y[j]) * vec(X[j, :])
            lm.bias -= eta0 * (pred - y[j])
        end
    end
    return lm
end

function predict(lm::SGDRegressor, X::Matrix{Float64})
    return X * lm.weights + lm.bias
end


function _update_learning_rate(learning_rate='constant', current_lr, alpha, power_t, iter)
    if learning_rate == 'constant':
        return current_lr
    elseif learning_rate == 'inv_scaling'
        return
