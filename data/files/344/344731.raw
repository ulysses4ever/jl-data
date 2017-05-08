using CollaborativeFiltering

n_items = 10000
n_users = 2000
n_features = 300
X = randn(n_items, n_features)
Theta = randn(n_users, n_features)
Y = rand(n_items, n_users)
R = randbool(n_items, n_users)

for fn in (CollaborativeFiltering.cost_naive, CollaborativeFiltering.cost_devec)
  fn([1], [true], [1], [1], 1)
  @time fn(Y, R, X, Theta, 1)
end
