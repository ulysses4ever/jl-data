
include("solver.jl") 

## Neural Network structure 
type NeuralNet
	numLayers::Int   						
	numUnits::Array{Int} 
	activFunc::String 
	weights::Array{Any}

	NeuralNet(L,units,activ, ws) = 
	  if length(units) != L
	  	error("numHiddenUnits must have length $L")
	  elseif ∉(activ, ["tanh", "logit"])
	    error("Activation function must be set to \"tanh\" or \"logit\"")
	  else 
	  	ws = cell(L-1,1); new(L, units, activ, ws)
	  end 
end

NeuralNet(L) = NeuralNet(L, 3 * ones(L,1), "tanh", cell(L-1,1))
NeuralNet(L, units) = NeuralNet(L, units, "tanh", cell(L-1,1))


## Fitting functions 
function fit(nn::NeuralNet, trainData, options::FitOptions)

	# return array of incoming weight matrices ∀l = 1,...,L
	nn.weightMatrices = W::cell{Matrix{Float64}} 
end

## Forward propagation subroutine
function forwardPropagate(nn::NeuralNet, x_input::Vector{Float64})

	# Network topology
	L = nn.numLayers   					 # total number of layers, including input and output
	numUnits = nn.numUnits 		   # only in hidden and output layers

	# set activation function 
	θ = if nn.activFunc == "tanh" 
				tanh
		  elseif nn.activFunc == "logit" 
		  	(x) -> 1/(1+exp(-x))
		  end
	
	# Cells containg L input vectors and L output vectors
	s = cell(L-1,1) # inputs of all layers except input
	x = cell(L-1,1) # outputs of all layers except input
	

	# Forward propagation chain
	# for each hidden or output layer
	x[1] = x_input
  for l in 1:L 
  	W = nn.weights[l] 
  	s[l] = W'*x[l] 
  	x[l+1] = [1, θ(s[l])]
  end

	# return output vectors and estimated target
  x[L+1], x
end

## Backpropagation subroutine
function backPropagate(nn::NeuralNet, x::Array{Float64})

	

	# Initialization


	# Backward propagation
	

	# return sensitivity vectors for all layers ∀l = L,...,1
	δ::Array{Vector{Float64}}
end


## Prediction functions 
function predict(net::NeuralNet, testData)

	# return class labels 
end

