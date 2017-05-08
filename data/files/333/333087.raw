function gradientDescentMulti(X, y, theta, alpha, num_iters)

  # Initialize some useful values
  m = length(y); # number of training examples
  J_history = zeros(num_iters, 1);

  for iter = [1:num_iters]
    theta = theta - alpha*(X'*(X*theta-y))/m

    # Save the cost J in every iteration    
    J_history[iter] = computeCostMulti(X, y, theta);
  end
  return (theta,J_history)
end
