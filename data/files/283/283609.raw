module CollaborativeFiltering

using Devectorize

function costregularization0(params::Vector{Float64})
  sum(params.^2)*lambda
end
function regularization(params::Vector{Float64})
  @devec reg = sum(params.^2)
  reg*lambda
end

cost0(Y, R, X, Theta, lambda) =
  sum(((X*Theta'-Y).^2).*R)/2 + lambda/2*sum(Theta.^2) + lambda/2*sum(X.^2)

function cost1(Y, R, X, Theta, lambda)
  predictions = X*Theta'
  @devec cost = sum(((predictions-Y).^2).*R) # predictions.*R if Y == 0 where R == true
  @devec reg = sum(X.^2) + sum(Theta.^2)
  (cost + reg*lambda)/2
end

function extract(params::Vector{Float64})
  X = reshape(params[1:num_movies*num_features], num_movies, num_features)
  Theta = reshape(params[num_movies*num_features+1:end], num_users, num_features)
  X, Theta
end

end # module
