#####################################
# Contains the following functions: #
#####################################

# sig(z): Return f(z) where f is the sigmoid function.

# classify(X, weights): Return hypothesis given data and parameters.

# classifyRaw(X, weights, meanVec, stdVec): Return hypothesis given
#   data and parameters after normalizing data.

# calcCost(X, Y, weights, lambda): Evaluate the cost function.

# calcGrad(X, Y, weights, lambda): Calculate the gradient of the
#   cost function.

# calcGradAlt(X, Y, weights, lambda): Calculate the gradient of the
#   cost function numerically.

# neuralNet(X, Y, architecture, lambda, alpha, maxIter): Train a
#   neural network with the desired hyperparameters.

# neuralNetCont(X, Y, architecture, lambda, alpha, maxIter, weights):
#   Same as neuralNet, except it requires a set of weights.


# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
#                                                                                       #
# The two functions that the user should be concerned with are classifyRaw and          #
# neuralNet (as well as neuralNetCont).  The function neuralNet uses given data to      #  
# train a neural network (detail below).  neuralNetCont is identical to neuralNet       #
# except it expects weights to be provided.  neuralNet uses stochastic gradient         # 
# descent to optimize the weights, and depending on the size of the network can take    #
# a rather long time to run.  One is able to run neuralNet, and then further optimize   #
# the weights at a later time using neuralNetCont.                                      #
#                                                                                       #
# The function classifyRaw forms a hypothesis on the given X values using the provided  #
# weights.  It is identical to classify except that it expects non-normalized (raw)     #
# data.  Weights are trained using normalized data, so new points must be normalized    #
# in the same manner.                                                                   #
#                                                                                       #
# Below is an explanation of the inputs and outputs of neuralNet:                       #
#                                                                                       #
# Inputs:                                                                               #
# X - NxM data matrix.  N is the number of records and M is the number of features.     #
# Y - N-length vector of labels.                                                        #
# architecture - An L-length vector where L is the number of hidden layers.  The        #
#                contents of architecture should be the desired size of the hidden      #
#                layers in order from lowest level to highest.                          #
# lambda - Regularization parameter.  Function currently uses L-2 regularization.       #
# alpha - Learning rate for gradient descent.                                           #
# maxIter - Number of epochs gradient descent will run for                              #
#                                                                                       #
# Outputs:                                                                              #
# weights - Trained parameters of the neural network                                    #
# cost - The cost function is evaluated every 2000 iterations of gradient descent.      #
#        Check this to make sure gradient descent is behaving properly.                 #
# meanVec - Column means of X.  For new examples, use these for normalization.          #
# stdVec - Column standard deviations.  For new examples, use these for normalization.  #
#                                                                                       #
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #


function sig(z)
  ## Return f(z) where f is the sigmoid function
  return ( 1 / (1 + exp(-1*z)) )
end


function classify(X, weights)
  ####################################################
  ## Use weights on given data to form a hypothesis ##
  ####################################################

  n = size(X, 1)
  lengthWeights = length(weights)

  aMat = cell(lengthWeights)
  z = weights[1] * X'
  aMat[1] = vcat(ones(1, n), sig(z))'
  for i in 2:lengthWeights
    z = weights[i] * aMat[i-1]'
    aMat[i] = vcat(ones(1, n), sig(z))'
  end
  aMat[end] = aMat[end][:,2:end]

  hypothesis = aMat[end]
  return hypothesis

end


function classifyRaw(X, weights, meanVec, stdVec)
  ###################################################################
  ## Use weights on given non-normalized data to form a hypothesis ##
  ###################################################################

  n = size(X, 1)
  numFeature = size(X, 2)

  meanVec = mean(X, 1)
  stdVec = std(X, 1)
  for i in 1:numFeature
    X[:,i] = X[:,i] - meanVec[i]
    if stdVec[i] != 0
      X[:,i] = X[:,i] / stdVec[i]
    end
  end
  X = hcat(ones(n, 1), X)

  hypothesis = classify(X, weights)
  return hypothesis

end


function calcCost(X, Y, weights, lambda)
  ##############################################
  ## Calculate the value of the cost function ##
  ##############################################

  n = size(X, 1)
  numClass = size(Y, 2)
  hypothesis = classify(X, weights)

  ## Calculate the cost due to error
  cost = 0
  for i in 1:n
    for k in 1:numClass
      cost = cost + ( -1 * Y[i,k] * log(hypothesis[i,k]) - (1 - Y[i,k]) * log(1 - hypothesis[i,k]) )
    end
  end
  cost = cost/n;

  ## Calculate the cost due to regularization
  regCost = 0
  for B in 1:length(weights)
    regCost = regCost + sum(weights[B][:,2:end].^2) 
  end
  regCost = (regCost * lambda) / (2*n);

  ## Total cost is the sum of error plus regularization
  totalCost = cost + regCost
  return totalCost

end


function calcGrad(X, Y, weights, lambda)
  ###########################################################################
  ## Calculate the gradient of the parameters with respect to the cost     ##
  ## function.  Used for gradient descent or other optimization algorithm. ##
  ###########################################################################

  n = size(X, 1)
  lengthWeights = length(weights)

  ## Calculate each activation value
  aMat = cell(lengthWeights)
  z = weights[1] * X'
  aMat[1] = vcat(ones(1, n), sig(z))'
  for i in 2:lengthWeights
    z = weights[i] * aMat[i-1]'
    aMat[i] = vcat(ones(1, n), sig(z))'
  end
  aMat[end] = aMat[end][:, 2:end]

  ## Calculate deltas for use in backprop
  deltaMat = cell(lengthWeights)
  deltaMat[end] = aMat[end] - Y
  for i in (lengthWeights-1):-1:1
    deltaMat[i] = (weights[i+1]' * deltaMat[i+1]')' .* (aMat[i] .* (ones(size(aMat[i])) - aMat[i]))
    deltaMat[i] = deltaMat[i][:, 2:end]
  end
 
  ## Use activation and delta values to calulate the gradient
  grad = cell(lengthWeights)
  grad[1] = deltaMat[1]' * X
  for i in 2:lengthWeights
    grad[i] = deltaMat[i]' * aMat[i-1]
  end

  ## Adjust for regularization
  for i in 1:lengthWeights
    grad[i][1:end, 2:end] = grad[i][1:end, 2:end] + lambda * weights[i][1:end, 2:end]
    grad[i] = grad[i] / n
  end

  return grad

end


function calcGradAlt(xi, yi, weights, lambda)
  ##################################################################################
  ## Calculate the gradient numerically.  Very slow, only used for grad checking. ##
  ##################################################################################

  grad = cell(length(weights))
  for i in 1:length(weights)
    grad[i] = zeros(size(weights[i]))
  end

  for B in 1:length(weights)
    for i in 1:size(weights[B], 1)
      for j in 1:size(weights[B], 2)
        weightsPE = deepcopy(weights)
        weightsPE[B][i, j] = weights[B][i, j] + .0001
        weightsME = deepcopy(weights)
        weightsME[B][i, j] = weights[B][i, j] - .0001
        costPE = calcCost(xi, yi, weightsPE, lambda)
        costME = calcCost(xi, yi, weightsME, lambda)
        grad[B][i, j] = (costPE - costME) / .0002
      end
    end
  end

  return grad
end


function neuralNet(X, Y, architecture, lambda, alpha, maxIter)

  ####################################
  ##  1. Preprocessing              ## 
  ##                                ##
  ####################################

  n = length(Y)
  numFeature = size(X, 2)

  ##1.a  Construct the response Y
  numClass = length(unique(Y))
  if numClass != 2
    response = zeros(n, numClass)
    classes = sort(unique(Y))
    for i in 1:n
      response[i,1:end] = indexin(classes,[Y[i]])
    end
    Y = response
  end

  ##1.b  Normalize features
  meanVec = mean(X, 1)
  stdVec = std(X, 1)
  for i in 1:numFeature
    X[:,i] = X[:,i] - meanVec[i]
    if stdVec[i] != 0
      X[:,i] = X[:,i] / stdVec[i]
    end
  end
  X = hcat(ones(n, 1), X)

  ##1.c  Initialize weights
  numLayers = 2 + length(architecture)
  weights = cell(numLayers - 1)
  weights[1] = (2*rand(architecture[1], size(X, 2)) - 1) * (1 / sqrt(size(X, 2)))
  weights[numLayers-1] = (2*rand(numClass, architecture[end]+1) - 1) * (1 / sqrt(architecture[end]))
  if length(architecture) > 1
    for i in 2:length(architecture)
      weights[i] = (2*rand(architecture[i], architecture[i-1]+1) - 1) * (1 / sqrt(architecture[i-1]))
    end
  end

  ####################################
  ##  2. Optimize Parameters        ## 
  ##                                ##
  ####################################

  ##2.a  Randomize ordering
  mix = randperm(n)
  X = X[mix,:]
  Y = Y[mix,:]
  
  ##2.b  Perform stochastic gradient descent
  costVec = zeros(1 + int(floor(n*maxIter/2000)))
  costIndex = 0
  for B in 1:maxIter
    for i in 1:n
      grad = calcGrad(X[i,:], Y[i,:], weights, lambda)
      #gradAlt = calcGradAlt(X[i,:], Y[i,:], weights, lambda)  # Gradient Check (SLOW)
      for k in 1:(numLayers - 1)
        weights[k] = weights[k] - alpha*grad[k]
      end
      iter = n*(B-1) + i
      if iter == 1 || (iter % 2000) == 0
        costIndex = costIndex + 1
        costVec[costIndex] = calcCost(X, Y, weights, lambda)
      end
    end
  
  end

  return weights, costVec, meanVec, stdVec

end


function neuralNetCont(X, Y, architecture, lambda, alpha, maxIter, weights)
  #############################################################################
  ## Identical to neuralNet, except instead of randomly initializing weights ##
  ## this function takes weights as input.  This allows the user to "save    ##
  ## their progress" from a previous run of gradient descent.                ##
  #############################################################################

  n = length(Y)
  numFeature = size(X, 2)

  numClass = length(unique(Y))
  if numClass != 2
    response = zeros(n, numClass)
    classes = sort(unique(Y))
    for i in 1:n
      response[i,1:end] = indexin(classes,[Y[i]])
    end
    Y = response
  end

  meanVec = mean(X, 1)
  stdVec = std(X, 1)
  for i in 1:numFeature
    X[:,i] = X[:,i] - meanVec[i]
    if stdVec[i] != 0
      X[:,i] = X[:,i] / stdVec[i]
    end
  end
  X = hcat(ones(n, 1), X)

  mix = randperm(n)
  X = X[mix,:]
  Y = Y[mix,:]
  
  costVec = zeros(1 + int(floor(n*maxIter/2000)))
  costIndex = 0
  for B in 1:maxIter
    for i in 1:n
      grad = calcGrad(X[i,:], Y[i,:], weights, lambda)
      for k in 1:length(weights)
        weights[k] = weights[k] - alpha*grad[k]
      end
      iter = n*(B-1) + i
      if iter == 1 || (iter % 2000) == 0
        costIndex = costIndex + 1
        costVec[costIndex] = calcCost(X, Y, weights, lambda)
      end
    end
  
  end

  return weights, costVec, meanVec, stdVec

end


