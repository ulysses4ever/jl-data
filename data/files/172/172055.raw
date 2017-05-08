
function compute_cost(X, y, theta)
  return sum(((theta' * X')' - y).^2) / (2 * length(y))
end

function gradient_descent(X, y, theta, alpha, iterations)
  cost_history = zeros(iterations, 1)
  for i in collect(1:iterations)
    theta = (theta' - ((alpha / length(y)) * sum((sum((theta' .* X), 2) - y).*X, 1)))'
    cost_history[i] = compute_cost(X, y, theta)
  end
  return theta, cost_history
end

