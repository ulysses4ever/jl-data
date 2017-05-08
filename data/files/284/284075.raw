# Here is a toy neural network example.  The data is a subset of the MNIST
# data set (info here: https://www.kaggle.com/c/digit-recognizer/data).  Labels
# are in the first column, and the remaining 784 columns are features.  This
# example trains a neural network with two hidden layers.  Depending on your
# hardware, it might take a few minutes to run.  After the network is trained,
# we use it to classify the training data and measure cost and zero-one error
# on the training set.


## Read in data, define X and Y
data = readcsv("exampleNN.csv");
X = data[:,2:end];
Y = data[:,1];
n = length(Y)

## Train the NN!
weights, cost, meanVec, stdVec = neuralNet(X, Y, [400, 50], .0001, .02, 12);

## Use the NN to classify the training set
hypothesis = classifyRaw(X, weights, meanVec, stdVec);
classification = zeros(n);
for i in 1:n
  postProb = maximum(hypothesis[i,:]);
  classification[i] = findin(hypothesis[i,:], [postProb])[1] - 1;
end

## The cost function evaluated every 2000 iterations of gradient descent.
cost

## Check zero-one training error
err = sum(classification .!= Y) / n


