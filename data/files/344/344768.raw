using FactCheck
using CollaborativeFiltering: cost0, cost1

Y = [5 0 5; 0 5 -1]
R = [true true true; true true false]
# n_features = 2
# n_users = size(Y, 1)
# n_items = size(Y, 2)
X = [4 0; 1 5]
Theta = [1 0; 0 1; 1 1]

facts("tests for cost function") do
    @fact cost0(Y, R, X, Theta, 0) => 1.5
    @fact cost0(Y, R, X, Theta, 1) => 24.5
end

facts("tests for cost1 function") do
    @fact cost1(Y, R, X, Theta, 0) => 1.5
    @fact cost1(Y, R, X, Theta, 1) => 24.5
end

function benchmark()
  n_items = 10000
  n_users = 2000
  n_features = 300
  X = randn(n_items, n_features)
  Theta = randn(n_users, n_features)
  Y = rand(n_items, n_users)
  R = randbool(n_items, n_users)
  @time cost0(Y, R, X, Theta, 1)
  @time cost1(Y, R, X, Theta, 1)
end
benchmark()
