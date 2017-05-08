
include("solver.jl", "helpers.jl") 

## Neural Network structure 
type NeuralNet
	numLayers::Int   						
	numHidden::Array{Int} 
	numOutput::Array{Int} 
	activFunc::String 
	weights::Array{Any}

	NeuralNet(L,units,activ, ws) = 
	  if length(units) != L
	  	error("numHidden must be a vector of length $(L-1)")
	  elseif ∉(activ, ["tanh", "logit"])
	    error("Activation function must be set to \"tanh\" or \"logit\"")
	  else 
	  	ws = cell(L,1); new(L, units, activ, ws)
	  end 
end

# Default architecture (3,3,...,3,1)
NeuralNet(L) = NeuralNet(L, 3 * ones(L-1,1), 1, "tanh", cell(L,1))
NeuralNet(L, units, outputs) = NeuralNet(L, units, outputs, "tanh", cell(L,1))


## Function for extracting sample from training data 
##	Input: training data
##	Ouput: pair of feature and class labels 
##  		- x is a d-element vector 
##			- y is an integer from 1 to numOutputs
function extractSample(trainData, n)
	xn, yn
end


## Fitting functions 
function fit(nn::NeuralNet, trainData, options::FitOptions, maxIter::Int)

	# assume trainData if preprocessed to make learning faster
	# e.g. successive examples come from different classes 
	L = nn.numLayers
	C = nn.numOutputs

	# Iteration of whole batch training
	for i = 1:maxIter
  	for n = 1:numSamples 

  		# Local variables within scope of each iteration
  		xn, yn = extractSample(trainData, n)

  		# Compute output vectors x(l), l = 1,...,L+1
  		x, s = forwardPropagate(nn, xn)

  		# Compute sensitivity vectors δ(l), l = 1,...,L	 
  		δ = backPropagate(nn, x, s)

  		# Gradient of error En w.r.t softmax outputs  
  		# assuming y is encoded as one-of-C 
  		∇En = 1/x[L+1] * mask(ones(C), yn)

  		# for each layer
  		for l = 1:L

  			# Update matrix for weights going to layer l using sample n 
  			ΔGn = ∇En .* (x[l] * δ[l]')

  			# Update the weight matrices 
  			nn.weights[l] = nn.weights[l] - 0.01 * ΔGn
  		end
  	end   	
	end

  # return in-sample error (optionally)
end

## Initialization of weights
function initWeights (nn:NeuralNet)
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
function forwardPropagate(nn::NeuralNet, xn::Vector{Float64})

	# Network topology
	L = nn.numLayers   					 # number of all layers excluding input 
	C = nn.numOutputs
	numUnits = nn.numUnits 		   # dimensions of all layers excluding input

	# set activation function 
	θ = if nn.activFunc == "tanh" 
				tanh
		  elseif nn.activFunc == "logit" 
		  	logit
		  end
	
	# Cells containg L input vectors and L+1 output vectors
	s = cell(L,1) 	# inputs of all layers 
	x = cell(L+1,1) # outputs of all layers

	# Compute input s[l] and output x[l+1] at each layer
	x[1] = xn
  for l in 1:L-1
  	W = nn.weights[l] 
  	s[l] = W'*x[l] 
  	x[l+1] = [1, θ(s[l])]
  end
  s[L] = (nn.weights[L])' * x[L]
  x[L+1] = C == 1 ? logit(s(L)) : softmax(s[L])

	# return output and input vectors
  x, s
end

##----------------------------------------------------------------------
## Backpropagation subroutine
## Inputs: 
##		- L+1 output vectors x[l] (including input vector x[1] = xn)
##		- L input vectors s[l] 
## Outputs: 
## 		- Sensisitivity vectors δ[l] for all layer l = 1,...,L
##----------------------------------------------------------------------
function backPropagate(nn::NeuralNet, x::Array{Float64})

	# Network topology
	L = nn.numLayers   					 # number of all layers excluding input 
	C = nn.numOutputs
	δ = cell(L,1) 	

	# Backward propagation
	# Assume: softmax or logistic activation output functions
	δ[L] = x[L+1] .* (1 - x[L+1])		

	for l = L-1:-1:1
		∇θ = (1 - x[l] .* x[l]) 
		W = nn.weights[l+1]
		δ[l] = ∇θ[2:end] .* (W * δ[l+1])[2:end] 
	end
	# return sensitivity vectors for all layers ∀l = L,...,1
	δ
end


## Prediction functions 
function predict(net::NeuralNet, testData)

	# return class labels 
end

