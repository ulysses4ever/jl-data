
include("solver.jl")
include("helpers.jl")

using Debug

##----------------------------------------------------------------------
## Neural Network structure 
type NeuralNet
	numLayers::Int   					# Number of layers (excluding input)		
	numInputs::Int 						# Input dimension (no bias node)
	numOutputs::Int 					# Output dimension
	numHidden::Array{Int} 		# Number of units at each hidden layer
	activFunc::String 				# Activation function of hidden units
	weights 									# Weight matrices 

	NeuralNet(L,inputs, outputs,units,activ, ws) = 
		# assert dimensions agree
	  if length(units) != L-1 
	  	error("numHidden must be a vector of length $(L-1)")
	  elseif ∉(activ, ["tanh", "logit"])
	    error("Activation function must be set to \"tanh\" or \"logit\"")
	  else 
	  	ws = cell(L,1); new(L, inputs,outputs, units,activ, ws)
	  end 
end

# Default architecture (3,3,..,3)
NeuralNet(L, inputs, outputs) = NeuralNet(L, inputs, outputs, 3 * ones(L-1,1), "tanh", cell(L,1))
NeuralNet(L, inputs, outputs, units) = NeuralNet(L, inputs, outputs, units, "tanh", cell(L,1))

##----------------------------------------------------------------------
## Function for pre-processing training data 
##	Input: training data
##	Ouput: pair of feature matrix and class labels 
##  		- X is a n x d feature matrix
##			- y is an n-element vector with values from 1 to numOutputs
##----------------------------------------------------------------------
function extractSample(Xtrain, Ytrain, n)
	X, y
end

##----------------------------------------------------------------------
## Fit: train the neural network model 
## Inputs:
##		- Neural network structure
##		- Matrix of features X with dimension N x p
##		- Class label vector of dimension N x 1 (yn ∈ {1,...,C})
##		- fitting options 
##		- maximum number of optimization iterations 
##----------------------------------------------------------------------
@debug function fit!(nn::NeuralNet, X, y, options::FitOptions, maxIter::Int)

	# assume trainData if preprocessed to make learning faster
	# e.g. successive examples come from different classes 
	L = nn.numLayers
	C = nn.numOutputs
	N = size(X,1)
	d = [nn.numInputs, reshape(nn.numHidden, length(nn.numHidden),1), nn.numOutputs]

	# Initialize weights 
	initWeights!(nn, X)

	# Iteration of whole batch training
	for i = 1:maxIter
		if i % 10 == 0 tic; println("Pass data Iteration: $i") end
  	for n = 1:N 
  		if n % 50 == 0 println("Samples: $n") end
  		# Local variables within scope of each iteration
  		xn, yn = X[n,:]', y[n]
 		
  		# Compute output vectors x(l), l = 1,...,L+1
  		x, s = forwardPropagate(nn, xn)

  		# Compute sensitivity matrices Δ[l], l = 1,...,L	 
  		local Δ = backPropagate(nn, x)

  		# Update the weights
  		updateWeights!(nn, Δ, x, yn)
  	end  
  	if i % 10 == 0 toc end  	
	end

  # return in-sample error (optionally)
end

##----------------------------------------------------------------------
## initWeights: initializate weights matrices
## Inputs:
##		- Neural network structure
##		- Sensitivity matrices Δ[l], ∀l ∈ {1,..,L}
##		- Output vectors x[l], ∀l ∈ {1,..,L+1} 
##		- Class label of example: yn 
##----------------------------------------------------------------------

@debug function initWeights!(nn::NeuralNet, X::Array{Float64})
	L = nn.numLayers
	N = size(X,1)
	d = [nn.numInputs, reshape(nn.numHidden, length(nn.numHidden),1), nn.numOutputs]
	
	# variance must be smaller than inverse of max_n{squaredNorm(xn)}
	σ = map(i -> norm(X[i,:]')^2, [1:N]) |> maximum |> sqrt

	# first layer 
	nn.weights[1] = 1e-1 * (1/σ) * randn(d[1],d[2])

	# subsequent layers
	for l = 2:L
		nn.weights[l] = 1e-1 * (1/σ) * randn(d[l]+1,d[l+1])
	end

	# return the initial weights
	nn.weights
end

##----------------------------------------------------------------------
## Forward propagation subroutine
## Inputs: 
## 		- Training example: xn
## 		- Neural network structure: number of layers, number of units
## Outputs: 
##		- L+1 output vectors x[l] (including input vector x[1] = xn)
##		- L input vectors s[l] 
##----------------------------------------------------------------------
@debug function forwardPropagate(nn::NeuralNet, xn::Array{Float64})
	# println("Forward propagation..")
	# Network topology
	L = nn.numLayers   					 # number of all layers excluding input 
	C = nn.numOutputs
	
	# Cells containg L input vectors and L+1 output vectors
	s = cell(L,1) 	# inputs of all layers 
	x = cell(L+1,1) # outputs of all layers

	# Compute input s[l] and output x[l+1] at each layer
	# Input vector x[1] has no bias node
	x[1] = xn 
	# Hidden layers
  for l in 1:L-1
  	W = (nn.weights[l])
  	s[l] = W'*x[l] 
  	x[l+1] = [1, map(tanh, s[l])]   # use tanh
  end
  # Output layer
  s[L] = (nn.weights[L])' * x[L]
  x[L+1] = if C == 1 
             logit(s[L])
           else 
           	 softmax(s[L])
           end

	# return output and input vectors
  x, s
end

##----------------------------------------------------------------------
## Backpropagation subroutine
## Inputs: 
##		- L+1 output vectors x[l] (including input vector x[1] = xn)
##		- L input vectors s[l] 
## Outputs: 
## 		- Sensitivity matrices Δ[l] for all layer l = 1,...,L
##----------------------------------------------------------------------
function backPropagate(nn::NeuralNet, x)
	# println("Back propagation..")
	# Network topology
	L = nn.numLayers   					 # number of all layers excluding input 
	C = nn.numOutputs
	d = [nn.numInputs, reshape(nn.numHidden, length(nn.numHidden),1), nn.numOutputs]
	Δ = cell(L,1) 	

	# Output vector
	h = x[L+1]	

	# Sensitivy matrix for output layer
	Δ[L] = [ h[i]*(δ(i,j) - h[j]) for i in 1:C, j in 1:C ]

	# Sensitivy matrix for inner layers
	for l = L-1:-1:1
		Δ[l] = zeros(Float64, C, d[l+1]) 
		W = nn.weights[l+1]
		for k in 1:C
			for j in 1:d[l+1]
				# assuming tanh activation function at hidden units				
				Δ[l][k,j] = (1 - h[k]^2) * (W[j,:] * Δ[l+1][k,:]')[1]
			end
		end
	end

	# return sensitivity matrices for all layers ∀l = L,...,1
	Δ
end


##----------------------------------------------------------------------
## updateWeights: update and return the weight matrices at each iteration
## Inputs:
##		- Neural network structure
##		- Sensitivity matrices Δ[l], ∀l ∈ {1,..,L}
##		- Output vectors x[l], ∀l ∈ {1,..,L+1} 
##		- Class label of example: yn 
## Output: 
##		- weights matrices
##----------------------------------------------------------------------
function updateWeights!(nn::NeuralNet, Δ, x, yn)

	L = nn.numLayers
	C = nn.numOutputs
	d = [nn.numInputs, reshape(nn.numHidden, length(nn.numHidden),1), nn.numOutputs]

	# Softmax output
	h = x[L+1]

	# Step size
	μ = 0.1

	# yn is encoded as one-of-C vector
	yv = mask(ones(C), yn)

	# Gradient of error w.r.t softmax output vector
	∇e_h = - vec(yv ./ h)

	# Gradient of error w.r.t weight matrix W[L] 
	# assuming softmax output activation and cross-entropy error
	∇e_WL = zeros(Float64, d[L]+1,C)
	for i in 1:d[L]+1
	  for j in 1:C 
			∇e_WL[i,j] = x[L][i] * (h[j] - yv[j]) 
		end
	end
	# SGD update of weight matrix W[L]
	nn.weights[L] = nn.weights[L] - μ * ∇e_WL

	# Gradient of error w.r.t weight matrix @ input W[1] 
	# Input has no bias node: W1 is d[1] x d[2] matrix
	∇e_W1 = zeros(Float64, d[1],d[2])
	for i in 1:d[1]
	  for j in 1:C 
			∇e_W1[i,j] = x[1][i] * dot(∇e_h, vec(Δ[1][:,j]))
		end
	end

	# SGD update of weight matrix W[1]
	nn.weights[1] = nn.weights[1] - μ * ∇e_W1

	# Gradient of error w.r.t weight matrices of hidden layers
	for l = 2:L-1  
		# Gradient of error w.r.t weight matrix Wl
		# x[l] has bias node: Wl is (d[l]+1) x d[l+1] matrix
		∇e_Wl = zeros(Float64, d[l]+1, d[l+1])
		for i in 1:d[l]+1
			for j in 1:d[l+1] 
				∇e_Wl[i,j] = x[l][i] * dot(∇e_h, vec(Δ[l][:,j]))
			end
		end

		# SGD update the weight matrices 
		nn.weights[l] = nn.weights[l] - μ * ∇e_Wl
	end
	nn.weights
end	

##----------------------------------------------------------------------
## predict: predict the labels of new samples using forward propagation 
## Inputs:
##		- Neural network structure
##		- New samples of size N x p 
## Output: a vector of pairs containing:
##		- Maximum posterior probability of predicted class 
##		- Label of predicted class ∈ {1,...,C}
##----------------------------------------------------------------------
function predict(net::NeuralNet, xnew)
	x,s = forwardPropagate(net, xnew)
	prob, class = findmax(x[end])
end

# test
# # not simple
# net = NeuralNet(4, 20, 3, [16 8 6])
# X = randn(100,20); y = rand(1:3,100)