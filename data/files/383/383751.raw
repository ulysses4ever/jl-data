using Optim

x = [1.0, 2.0, 3.0]
y = 1.0 + 2.0 * x + [-0.3, 0.3, -0.1]

function sqerror(betas)
    err = 0.0
    for i in 1:length(x)
        pred_i = betas[1] + betas[2] * x[i]
        err += (y[i] - pred_i)^2
    end
    return err
end

res = optimize(sqerror, [0.0, 0.0], LBFGS())
@show res
