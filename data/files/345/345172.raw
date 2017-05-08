#####################################
# Contains the following functions: #
#####################################

# getIndex(n, folds, B): Return indicies for train and test data.

# kFoldCVneuralNet(X, Y, architecture, lambda, alpha, maxIter, folds):
#   Use k-fold cross validation to evaluate the cost and zero-one error
#   for a neural network given data and hyper parameters.

# CVneuralNet(X, Y, architecture, lambda, alpha, maxIter, nTest):
#   Use cross validation to evaluate the cost and zero-one error
#   for a neural network given data and hyper parameters.


# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
#                                                                                       #
# Both kFoldCVneuralNet and CVneuralNet will be useful to the user.  The first function #
# will partition X and Y a number of times equal to folds.  For each partition, a       #
# neural network will be trained on all the data not in the given partition, and then   #
# data in the partition will be used as a test set.  Thus, each data point will be      #
# tested on exactly once.  The drawback of this method is that it can be time           #
# consuming.  If folds is equal to 4, then four separate networks must be trained.      #
#                                                                                       #
# CVneuralNet will randomly draw a test set of size nTest from X and Y.  The remaining  #
# data points will be used as training and the resulting network will be used on the    #
# test set.  Cost and zero-one error are reported.  This method will be faster than     #
# k-fold cross validation, but could be viewed as being less robust.                    #
#                                                                                       #
# Below is an explanation of the inputs and outputs of both CV functions:               #
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
# folds - Number of folds to use in k-fold cross validation                             #
# nTest - Desired size of test set.  The training set will be of size (N - nTest)       #
#                                                                                       #
# Outputs:                                                                              #  
# cost - Value of the cost function when the trained NN is used on the test set.        #
# err - Zero-one error on the test set.                                                 #
#                                                                                       #
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #


function getIndex(n, folds, B)
  ## Helper fucntion for k-fold cross validation

  partSize = int(floor(n/folds))
  trainIndex = zeros(n - partSize)
  testIndex = zeros(partSize)
  if B == 1
    trainIndex = [(partSize + 1):n]
    testIndex = [1:partSize]
  elseif B == folds
    trainIndex = [1:((B-1)*partSize)]
    testIndex = [((B-1)*partSize + 1):n]
  else
    trainIndex = cat(1, [1:((B-1)*partSize)], [(B*partSize + 1):n])
    testIndex = [((B-1)*partSize + 1):(B*partSize)]  
  end

  return trainIndex, testIndex
end


function kFoldCVneuralNet(X, Y, architecture, lambda, alpha, maxIter, folds)
  ####################################################################
  ## Build and perform k-fold cross calidation for a neural network ##
  ## given data and hyper parameters.  Return both the final value  ##
  ## of the cost function and the number of incorrect predictions   ## 
  ## (i.e. zero-one loss).                                          ##
  ####################################################################

  n = length(Y)
  numFeature = size(X, 2)
  mix = randperm(n)
  X = X[mix,:]
  Y = Y[mix]
  numLambda = length(lambda)

  cost = zeros(numLambda)
  err = zeros(numLambda)
  numIter = 1
  totalIter = numLambda * folds
  for L in 1:numLambda

    for B in 1:folds
      ## Split data into train and test, use the former to train a NN
      trainIndex, testIndex = getIndex(n, folds, B)
      nTest = length(testIndex)
      Xtrain = X[trainIndex,:]
      Ytrain = Y[trainIndex]
      weights, costt, meanVec, stdVec = neuralNet(Xtrain, Ytrain, architecture, lambda[L], alpha, maxIter)

      Xtest = X[testIndex,:]
      Ytest = Y[testIndex]

      ## Normalize test data using the same normaliztion used for the training data
      meanMat = repmat(meanVec, nTest, 1)
      XtestNorm = Xtest - meanMat
      for i in 1:numFeature
        if stdVec[i] != 0
          XtestNorm[:,i] = XtestNorm[:,i] / stdVec[i]
        end
      end
      XtestNorm = hcat(ones(nTest, 1), XtestNorm)

      ## Transform the test labels into vector form
      numClass = length(unique(Ytest))
      if numClass != 2
        response = zeros(nTest, numClass)
        classes = sort(unique(Ytest))
        for i in 1:nTest
          response[i,1:end] = indexin(classes,[Ytest[i]])
        end
        Ytest = response
      end
      
      ## Calculate both cost and zero-one loss
      cost[L] = cost[L] + calcCost(XtestNorm, Ytest, weights, 0) * (nTest / n)
      hypothesis = classify(XtestNorm, weights)
      guess = zeros(nTest);
      for i in 1:nTest
        guess = findin(hypothesis[i,:], [maximum(hypothesis[i,:])])[1]
        if Ytest[i, guess] == 0
          err[L] = err[L] + 1
        end
      end

    print("Finished iteration ", numIter, " out of ", totalIter, ".\n")
    numIter = numIter + 1
    end

  end

  return cost, err
  
end


function CVneuralNet(X, Y, architecture, lambda, alpha, maxIter, nTest)
  ####################################################################
  ## Build and perform cross calidation for a neural network        ##
  ## given data and hyper parameters.  Return both the final value  ##
  ## of the cost function and the number of incorrect predictions   ## 
  ## (i.e. zero-one loss).                                          ##
  ####################################################################

  n = length(Y);
  nTrain = n - nTest
  numFeature = size(X, 2);
  mix = randperm(n);
  X = X[mix,:];
  Y = Y[mix];

  ## Define train and test data
  Xtrain = X[1:nTrain,:];
  Ytrain = Y[1:nTrain];
  Xtest = X[(nTrain + 1):end,:];
  Ytest = Y[(nTrain + 1):end];

  ## Use training data to train a NN
  weights, cost, meanVec, stdVec = neuralNet(Xtrain, Ytrain, architecture, lambda, alpha, maxIter);

  ## Normalize test data using the same normaliztion used for the training data
  meanMat = repmat(meanVec, nTest, 1);
  XtestNorm = Xtest - meanMat;
  for i in 1:numFeature
    if stdVec[i] != 0
      XtestNorm[:,i] = XtestNorm[:,i] / stdVec[i];
    end
  end
  XtestNorm = hcat(ones(nTest, 1), XtestNorm);

  ## Transform test labels
  numClass = length(unique(Ytest));
  if numClass != 2
    response = zeros(nTest, numClass);
    classes = sort(unique(Ytest));
    for i in 1:nTest
      response[i,:] = indexin(classes,[Ytest[i]]);
    end
    Ytest = response;
  end

  ## Calculate both cost and zero-one loss
  hypothesis = classify(XtestNorm, weights);
  wrong = 0
  for i in 1:nTest
    guess = findin(hypothesis[i,:], [maximum(hypothesis[i,:])])[1]
    if Ytest[i, guess] == 0
      wrong = wrong + 1
    end
  end
  cost = calcCost(XtestNorm, Ytest, weights, 0)
  err = wrong / nTest

  return cost, err

end

