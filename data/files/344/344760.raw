module CollaborativeFiltering

using Devectorize


function cost_naive(Y, R::AbstractArray{Bool}, X, Theta, lambda)
  sum(((X*Theta'-Y).^2).*R)/2 + lambda/2*sum(Theta.^2) + lambda/2*sum(X.^2)
end

function cost_devec(Y, R::AbstractArray{Bool}, X, Theta, lambda)
  predictions = X*Theta'
  @devec cost = sum(((predictions-Y).^2).*R) # predictions.*R if Y == 0 where R == true
  @devec reg = sum(X.^2) + sum(Theta.^2)
  (cost + reg*lambda)/2
end

function grad_naive(Y, R::AbstractArray{Bool}, X, Theta, lambda, storage::Vector{Float64})
  X_grad = zeros(size(X))
  Theta_grad = zeros(size(Theta))
  n_items = size(Y, 1)
  n_users = size(Y, 2)

  for i=1:n_items  #### 35% gc time
    for j=1:n_users # colum based array access!
      if R[i,j]
        X_grad[i,:] = X_grad[i,:] + (Theta[j,:]*X[i,:]'-Y[i,j]) .* Theta[j,:]   # Y != 0 where R == 0
        Theta_grad[j,:] = Theta_grad[j,:] + (Theta[j,:]*X[i,:]'-Y[i,j]) .* X[i,:]
      end
    end
  end

  X_grad = X_grad + lambda*X
  Theta_grad = Theta_grad + lambda*Theta
  updated = [X_grad[:]; Theta_grad[:]] # unroll
  for i=1:length(updated) # @simd?
    storage[i] = updated[i]
  end
end

function grad_array(Y, R::AbstractArray{Bool}, X, Theta, lambda, storage::Vector{Float64})
  X_grad = zeros(size(X))
  Theta_grad = zeros(size(Theta))
  n_items = size(Y, 1)
  n_users = size(Y, 2)

  for j=1:n_users
    for i=1:n_items
      if R[i,j]
        X_grad[i,:] = X_grad[i,:] + (Theta[j,:]*X[i,:]'-Y[i,j]) .* Theta[j,:]
        Theta_grad[j,:] = Theta_grad[j,:] + (Theta[j,:]*X[i,:]'-Y[i,j]) .* X[i,:]
      end
    end
  end

  X_grad = X_grad + lambda*X
  Theta_grad = Theta_grad + lambda*Theta
  updated = [X_grad[:]; Theta_grad[:]] # unroll
  for i=1:length(updated) # @simd?
    storage[i] = updated[i]
  end
end

function grad_pred(Y, R::AbstractArray{Bool}, X, Theta, lambda, storage::Vector{Float64})
  X_grad = zeros(size(X))
  Theta_grad = zeros(size(Theta))
  n_items = size(Y, 1)
  n_users = size(Y, 2)

  pred = X*Theta'
  for i=1:n_items
    for j=1:n_users
      if R[i,j]
        X_grad[i,:] = X_grad[i,:] + (pred[i,j]-Y[i,j]) .* Theta[j,:]
        Theta_grad[j,:] = Theta_grad[j,:] + (pred[i,j]-Y[i,j]) .* X[i,:]
      end
    end
  end

  X_grad = X_grad + lambda*X
  Theta_grad = Theta_grad + lambda*Theta
  updated = [X_grad[:]; Theta_grad[:]] # unroll
  for i=1:length(updated) # @simd?
    storage[i] = updated[i]
  end
end

function grad_error(Y, R::AbstractArray{Bool}, X, Theta, lambda, storage::Vector{Float64})
  X_grad = zeros(size(X))
  Theta_grad = zeros(size(Theta))
  n_items = size(Y, 1)
  n_users = size(Y, 2)

  pred = X*Theta'
  error = pred - Y
  for i=1:n_items
    for j=1:n_users
      if R[i,j]
        X_grad[i,:] = X_grad[i,:] + error[i,j] .* Theta[j,:]
        Theta_grad[j,:] = Theta_grad[j,:] + error[i,j] .* X[i,:]
      end
    end
  end

  X_grad = X_grad + lambda*X
  Theta_grad = Theta_grad + lambda*Theta
  updated = [X_grad[:]; Theta_grad[:]] # unroll
  for i=1:length(updated) # @simd?
    storage[i] = updated[i]
  end
end

function grad_simd(Y, R::AbstractArray{Bool}, X, Theta, lambda, storage::Vector{Float64})
  X_grad = zeros(size(X))
  Theta_grad = zeros(size(Theta))
  n_items = size(Y, 1)
  n_users = size(Y, 2)
  n_features = size(X, 2)

  pred = X*Theta'
  for i=1:n_items
    for j=1:n_users
      if R[i,j]
        X_grad[i,:] = X_grad[i,:] + (pred[i,j]-Y[i,j]) .* Theta[j,:]
        Theta_grad[j,:] = Theta_grad[j,:] + (pred[i,j]-Y[i,j]) .* X[i,:]
      end
    end
  end

  X_grad = X_grad + lambda*X
  Theta_grad = Theta_grad + lambda*Theta

  for f=1:n_features
    @simd for i=1:n_items
      @inbounds storage[f*i] = X_grad[i,f]
    end
  end
  offset = n_items * n_features
  for f=1:n_features
    @simd for j=1:n_users
      @inbounds storage[f*j+offset] = Theta_grad[j,f]
    end
  end
end

function extract(params::Vector{Float64})
  X = reshape(params[1:num_movies*num_features], num_movies, num_features)
  Theta = reshape(params[num_movies*num_features+1:end], num_users, num_features)
  X, Theta
end

end # module
