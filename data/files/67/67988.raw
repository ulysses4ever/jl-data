#############################################################
# ============================================================
# Feedforward - Backpropagation Neural Network
# ============================================================
#############################################################

# Pkg.clone("https://github.com/johnmyleswhite/MNIST.jl.git")
# Pkg.add("Winston")
# Pkg.installed()

using MNIST
using Winston

###########################################
# computes the sigmoid of z.
###########################################
function sigmoid(z)
  g = 1.0 ./ (1.0 + exp(-z));
  return g;
end

########################################################################
# computes the gradient of the sigmoid function
# evaluated at z.
########################################################################
function sigmoidGradient(z)
  g = zeros(size(z));
  return sigmoid(z).*(1-sigmoid(z));
end

#############################################################
# computes the cost and gradient of the neural network. The
# parameters for the neural network are "unrolled" into the vector
# nn_params and need to be converted back into the weight matrices.
#
# The returned parameter grad should be a "unrolled" vector of the
# partial derivatives of the neural network.
#############################################################
function costFunction(input_layer_size, hidden_layer_size, output_layer_size, X, y, Theta1, Theta2, lambda)
  # ===================
  # Feedforward process
  # ===================
  # input layer
  # add one bias element
  activation1 = [ones(size(X,1),1) X];

  # hidden layer
  z2 = activation1*Theta1';
  activation2 = sigmoid(z2);
  # add one bias element
  activation2 = [ones(size(activation2,1),1) activation2];

  # output layer
  z3 = activation2*Theta2';
  activation3 = sigmoid(z3);
  hessian=activation3;

  # ==========
  # find cost
  # ==========
  J=0;
  eyeY = eye(outputLayerSize);
  intY = [convert(Int64,i)+1 for i in y];
  yInter = Array(Int64,length(y),outputLayerSize);
  for i = 1:m
    yInter[i,:] = eyeY[intY[i],:];
  end

  JInter = zeros(m,1);
  for i=1:m
    JInter[i,:] = (-yInter[i,:]*log(hessian[i,:]')) - ((1-yInter[i,:])*log(1-hessian[i,:]'));
  end

  # regularization term
  reg = (lambda/(2*m))*(sum(sum(Theta1[:,2:end].^2)) + sum(sum(Theta2[:,2:end].^2)));

  J = (1/m)*sum(JInter) + reg;

  # ========================
  # Backpropagation process
  # ========================
  Theta1_grad = zeros(size(Theta1));
  Theta2_grad = zeros(size(Theta2));

  delta3 = activation3 - yInter;
  delta2 = (delta3*Theta2[:, 2:end]).*sigmoidGradient(z2) ;

  grad2 = delta3'*activation2;
  grad1 = delta2'*activation1;

  reg_theta1 = ((lambda/m)*Theta1);
  reg_theta1[:,1] = 0;
  Theta1_grad = grad1/m + reg_theta1;

  reg_theta2 = ((lambda/m)*Theta2);
  reg_theta2[:,1] = 0;
  Theta2_grad = grad2/m + reg_theta2;

  # return
  return J, Theta1_grad, Theta2_grad;
end

##########################################################################
# outputs the predicted label of X given the
# trained weights of a neural network (Theta1, Theta2)
# Similar to feedforward process.
##########################################################################
function predict(Theta1, Theta2, X)
  m = size(X, 1);
  num_labels = size(Theta2, 1);
  p = zeros(size(X, 1), 1);
  h1 = sigmoid([ones(m, 1) X] * Theta1');
  h2 = sigmoid([ones(m, 1) h1] * Theta2');
  for i=1:m
    p[i,:] = indmax(h2[i,:])-1;
  end
 return p;
end

###############################################
# calculate the accuracy of the prediction
###############################################
function accuracy(truth, prediction)
  m = length(truth);
  if m!=length(prediction)
    error("truth and prediction length mismatch");
  end

  sum =0;
  for i=1:m
    if y[i,:] == pred[i,:]
      sum = sum +1;
    end
  end
  return (sum/m)*100;
end

############################################################ <MNIST backpropagation> ############################################################
# ===================
# Load training data
# ===================
X,y = traindata();
X=X';

m = size(X, 1);

# ======================
# Initialize parameters
# ======================
inputLayerSize = size(X,2);
hiddenLayerSize = 25;
outputLayerSize = 10;

epsilon_init = 0.12;
# including one bias neuron in input layer
# weights for the links connecting input layer to the hidden layer
Theta1 = rand(hiddenLayerSize, inputLayerSize+1)* 2 * epsilon_init - epsilon_init;
# including one bias neuron in hidden layer
# weights for the links connecting hidden layer to the output layer
Theta2 = rand(outputLayerSize, hiddenLayerSize+1)* 2 * epsilon_init - epsilon_init;

# Weight regularization parameter
lambda = 1;
# learning rate
alpha = 0.1;
# number of iterations
epoch = 500;
# cost per epoch
J = zeros(epoch,1);
for i = 1:epoch
  J[i,:], Theta_grad1, Theta_grad2 = costFunction(inputLayerSize, hiddenLayerSize, outputLayerSize, X, y, Theta1, Theta2, lambda);
  Theta1 = Theta1 - alpha* Theta_grad1;
  Theta2 = Theta2 - alpha* Theta_grad2;
end

# plot the cost per iteration
plot(1:length(J), J);

# make prediction
pred = predict(Theta1, Theta2, X);

# calculate accuracy
println("train accuracy: ", accuracy(y, pred));

# ===============
# load test data
# ===============
XTest,yTest = testdata();
XTest=XTest';

# make prediction
predTest = predict(Theta1, Theta2, XTest);

# calculate accuracy
println("test accuracy: ", accuracy(yTest, predTest));
