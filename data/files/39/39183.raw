using DeepLearn 
using HDF5 

# Load MNIST datasets
trainData = h5read("./data/train.hdf5", ".")
testData = h5read("./data/test.hdf5", ".")

numTrainSamples = 300
numTestSamples = 50

Xtrain = reshape(trainData["features"], 28*28,numTrainSamples)'
# assume 0 is class 1, 1 is class 2, ...
Ytrain = reshape(trainData["label"], numTrainSamples,1) + 1  
Xtest = reshape(testData["features"],numTestSamples,28*28)'
# assume 0 is class 1, 1 is class 2, ...
Ytest = reshape(testData["label"], numTestSamples,1) + 1

numInputs = size(Xtrain,2)
numOutputs = 10
numLayers = 2
numHiddenUnits = [800]

# Create Neural network model 
net = NeuralNet(numLayers, numInputs, numOutputs, numHiddenUnits)

println(net)
# Train network
maxIterations = 4
fit!(net, Xtrain, Ytrain, FitOptions(), maxIterations)

# # Predict labels on test data
# yhat = map((x) -> predict(net, x), map(i -> vec(xtest[i,:]), 1:size(xtest,1)))