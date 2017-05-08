using FactCheck
using CollaborativeFiltering: cost_naive, cost_devec, grad_naive, grad_array, grad_pred

function tinydata()
  Y = [5 0 5; 0 5 -1]
  R = [true true true; true true false]
  X = [4 0; 1 5]
  Theta = [1 0; 0 1; 1 1]
  Y, R, X, Theta
end

function randdata(n_items = 10000, n_users = 2000, n_features = 300)
  X = randn(n_items, n_features)
  Theta = randn(n_users, n_features)
  Y = rand(n_items, n_users)
  R = randbool(n_items, n_users)
  Y, R, X, Theta
end

function grad_storage(fn, Y, R, X, Theta, lambda)
  storage = Array(Float64, size(X, 1)*size(X, 2) + size(Theta, 1)*size(Theta, 2))
  fn(Y, R, X, Theta, lambda, storage)
  storage
end

facts("naive cost function") do
  Y, R, X, Theta = tinydata()
  @fact cost_naive(Y, R, X, Theta, 0) => 1.5
  @fact cost_naive(Y, R, X, Theta, 1) => 24.5
end

facts("devectorized cost function") do
  Y, R, X, Theta = tinydata()
  @fact cost_devec(Y, R, X, Theta, 0) => 1.5
  @fact cost_devec(Y, R, X, Theta, 1) => 24.5
end

facts("cost_devec equal to cost_naive") do
  Y, R, X, Theta = randdata()
  lambda = 0.3
  naive = cost_naive(Y, R, X, Theta, lambda)
  devec = cost_devec(Y, R, X, Theta, lambda)
  @fact devec => roughly(naive)
end

facts("naive gradient function") do
  Y, R, X, Theta = tinydata()
  @fact grad_storage(grad_naive, Y, R, X, Theta, 0) => [-2.0,1.0,-1.0,0.0,-3.0,0.0,-4.0,5.0,0.0,0.0]
  @fact grad_storage(grad_naive, Y, R, X, Theta, 1) => [2.0,2.0,-1.0,5.0,-2.0,0.0,-3.0,5.0,1.0,1.0]
end

facts("grad_array equal to grad_naive") do
  Y, R, X, Theta = randdata(100, 200, 300) # fails if 100, 200, 300
  lambda = 0.3
  naive = grad_storage(grad_naive, Y, R, X, Theta, lambda)
  array = grad_storage(grad_array, Y, R, X, Theta, lambda)
  @fact array => roughly(naive)
end

facts("grad_pred equal to grad_naive") do
  Y, R, X, Theta = randdata(100, 200, 300)
  lambda = 0.3
  naive = grad_storage(grad_naive, Y, R, X, Theta, lambda)
  pred = grad_storage(grad_pred, Y, R, X, Theta, lambda)
  @fact pred => roughly(naive)
end
