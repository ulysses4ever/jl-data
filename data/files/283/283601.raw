using CollaborativeFiltering

n_items = 100
n_users = 200
n_features = 300
X = randn(n_items, n_features)
Theta = randn(n_users, n_features)
Y = rand(n_items, n_users)
R = randbool(n_items, n_users)

for fn in (CollaborativeFiltering.grad_naive, CollaborativeFiltering.grad_array, CollaborativeFiltering.grad_pred)
  fn([1], [true], [1], [1], 1, Array(Float64, 2))
  storage = Array(Float64, size(X, 1)*size(X, 2) + size(Theta, 1)*size(Theta, 2))
  @time fn(Y, R, X, Theta, 1, storage)
end
