using FactCheck
using CollaborativeFiltering: cost0, cost1

Y = [5 0 5; 0 5 -1]
R = [true true true; true true false]
# n_features = 2
# n_users = size(Y, 1)
# n_items = size(Y, 2)
X = [4 0; 1 5]
Theta = [1 0; 0 1; 1 1]

facts("cost0") do
    @fact cost0(Y, R, X, Theta, 0) => 1.5
    @fact cost0(Y, R, X, Theta, 1) => 24.5
end

facts("cost1") do
    @fact cost1(Y, R, X, Theta, 0) => 1.5
    @fact cost1(Y, R, X, Theta, 1) => 24.5
end

function testdata()
  n_items = 10000
  n_users = 2000
  n_features = 300
  X = randn(n_items, n_features)
  Theta = randn(n_users, n_features)
  Y = rand(n_items, n_users)
  R = randbool(n_items, n_users)
  Y, R, X, Theta
end

facts("cost1 equal to cost0") do
  Y, R, X, Theta = testdata()
  lambda = 0.3
  c0 = cost0(Y, R, X, Theta, lambda)
  c1 = cost1(Y, R, X, Theta, lambda)
  @fact c1 => roughly(c0)
end
