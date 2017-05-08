using Gadfly;

include("regression.jl")

data = readdlm("../../../datasets/ml-ex1/ex1data1.txt", ',')

oX = data[:,1]
X = [ones(m, 1) oX]
y = data[:,2]
m = length(X)

X = [ones(m, 1) data[:,1]]
theta = zeros(2, 1)

iterations = 1500
alpha = 0.0105

initial_cost = compute_cost(X, y, theta)

(ptheta, cost_history) = gradient_descent(X, y, theta, alpha, iterations)

