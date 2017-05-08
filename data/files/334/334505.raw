using LinearLeastSquares
# Dimensions and true w,v.
srand(1)
n = 50
N = 300
w_true = randn(n)
v_true = 5

# Generate training data X, y.
X = randn(n, N)
y = sign(X'w_true .+ v_true + 10*randn(N))

# Generate test data X_test, y_test.
N_test = 100
X_test = randn(n, N_test)
y_test = sign(X_test'w_true .+ v_true + 10*randn(N_test))

# Find w,v for part (a).
# YOUR CODE HERE.

# Report classification error on train and test set.
train_error = sum(abs(y - sign(X'w .+ v)))/(2*N)
println("Classification error on training set: ", train_error)
test_error = sum(abs(y_test - sign(X_test'w .+ v)))/(2*N_test)
println("Classification error on test set: ", test_error)

using Gadfly
# Compute trade-off curve of classification error versus lambda.
lambda_vals = logspace(-1, 4, 100)
train_error = zeros(length(lambda_vals))
test_error = zeros(length(lambda_vals))
for i=1:length(lambda_vals)
    lambda = lambda_vals[i]
    # Find w,v with regularization for part (b).
    # YOUR CODE HERE.

    # Record train and test error.
    train_error[i] = sum(abs(y - sign(X'w .+ v)))/(2*N)
    test_error[i] = sum(abs(y_test - sign(X_test'w .+ v)))/(2*N_test)
end

# Plot trade-off curve of classification error versus lambda.
layer1 = layer(x=lambda_vals, y=train_error, Geom.line,
               Theme(default_color=color("blue")))#, label="train error")
layer2 = layer(x=lambda_vals, y=test_error,  Geom.line,
                Theme(default_color=color("red")))#, label="test error")
plot(layer1, layer2, Scale.x_log10,
         Guide.XLabel("lamdba"),
         Guide.YLabel("classification error")
)
