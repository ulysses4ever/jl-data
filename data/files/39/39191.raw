
include("solver.jl")
include("helpers.jl")

using Debug

## Neural Network structure 
type NeuralNet
	numLayers::Int   						
	numInputs::Int
	numOutputs::Int 
	numHidden::Array{Int} 
	activFunc::String 
	weights

	NeuralNet(L,inputs, outputs,units,activ, ws) = 
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


## Function for pre-processing training data 
##	Input: training data
##	Ouput: pair of feature matrix and class labels 
##  		- x is a n x d feature matrix
##			- y is an n-element vector with values from 1 to numOutputs
function extractSample(trainData)
	X, y
end


## Fitting functions 
@debug function fit(nn::NeuralNet, X, y, options::FitOptions, maxIter::Int)

	# assume trainData if preprocessed to make learning faster
	# e.g. successive examples come from different classes 
	L = nn.numLayers
	C = nn.numOutputs
	N = size(X,1)
	d = [nn.numInputs, reshape(nn.numHidden, length(nn.numHidden),1), nn.numOutputs]

	μ = 0.1

	# Initialize weights 
	initWeights(net, X)


	# Iteration of whole batch training
	for i = 1:maxIter
		if i % 10 == 0 println("Iteration: $i") end
  	for n = 1:N 
  		if n % 10 == 0 println("Sample: $n") end
  		# Local variables within scope of each iteration
  		xn, yn = X[n,:]', y[n]



  		# yn is encoded as one-of-C vector
  		yv = mask(ones(C), yn)
 		
  		# Compute output vectors x(l), l = 1,...,L+1
  		x, s = forwardPropagate(nn, xn)

  		# Softmax output
  		h = x[L+1]

  		# Compute sensitivity matrices Δ[l], l = 1,...,L	 
  		local Δ = backPropagate(nn, x)

  		# updateWeights(nn, x, y yv, h)
			# Gradient of error w.r.t softmax output vector
			∇e_h = - vec(yv ./ h)

  		# Gradient of error w.r.t weight matrix W[L] 
  		# assuming softmax output activation and cross-entropy error
  		# 
  		∇e_WL = zeros(Float64, d[L]+1,C)
  		for i in 1:d[L]+1
  		  for j in 1:C 
  				∇e_WL[i,j] = x[L][i] * (h[j] - yv[j]) 
  			end
  		end

  		# SGD update of weight matrix W[L]
  		nn.weights[L] = nn.weights[L] - μ * ∇e_WL

  		# Gradient of error w.r.t weight matrix @ input W[1] 
  		∇e_W1 = zeros(Float64, d[1],d[2])
  		for i in 1:d[1]

  		  for j in 1:C 
  				∇e_W1[i,j] = x[1][i] * dot(∇e_h, vec(Δ[1][:,j]))
  			end
  		end

  		# SGD update of weight matrix W[1]
  		nn.weights[1] = nn.weights[1] - μ * ∇e_W1

  		# Gradient of error w.r.t weight matrices of hidden layers
  		for l = 2:L-1  # changed from 1:L-1
  			# Gradient of error w.r.t weight matrix Wl
  			∇e_Wl = zeros(Float64, d[l]+1, d[l+1])
  				for i in 1:d[l]+1
  					for j in 1:d[l+1] 
  						∇e_Wl[i,j] = x[l][i] * dot(∇e_h, vec(Δ[l][:,j]))
  					end
					end

  			# SGD update the weight matrices 
  			nn.weights[l] = nn.weights[l] - μ * ∇e_Wl
  		end
  	end   	
	end

  # return in-sample error (optionally)
end

## Initialization of weights
function initWeights (nn::NeuralNet, X::Array{Float64})

	L = nn.numLayers
	N = size(X,1)
	d = [nn.numInputs, reshape(nn.numHidden, length(nn.numHidden),1), nn.numOutputs]
	
	# variance must be smaller than inverse of max_n{squaredNorm(xn)}
	σ = map(i -> norm(X[i,:]')^2, [1:N]) |> maximum |> sqrt

	# first layer 
	nn.weights[1] = 1e-3 * (1/σ) * randn(d[1],d[2])

	# subsequent layers
	for l = 2:L
		nn.weights[l] = 1e-3 * (1/σ) * randn(d[l]+1,d[l+1])
	end

	# return the new weights
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

	# set activation function 
	# θ = if nn.activFunc == "tanh" 
	# 			tanh
	# 	  elseif nn.activFunc == "logit" 
	# 	  	logit
	# 	  end
	
	# Cells containg L input vectors and L+1 output vectors
	s = cell(L,1) 	# inputs of all layers 
	x = cell(L+1,1) # outputs of all layers

	
	# Compute input s[l] and output x[l+1] at each layer
	x[1] = xn # Input has no bias node
  for l in 1:L-1
  	W = (nn.weights[l])
  	s[l] = W'*x[l] 
  	x[l+1] = [1, map(tanh, s[l])]
  end
  
  s[L] = (nn.weights[L])' * x[L]
  
  x[L+1] = if C == 1 
             map(logit,s[L])
           else 
           	 map(softmax,s[L])
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
@debug function backPropagate(nn::NeuralNet, x)
	# println("Back propagation..")
	# Network topology
	L = nn.numLayers   					 # number of all layers excluding input 
	C = nn.numOutputs
	d = [nn.numInputs, reshape(nn.numHidden, length(nn.numHidden),1), nn.numOutputs]
	Δ = cell(L,1) 	

	## Backward propagation

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
				
				# println("$k : $j")
				# println("W: $(size(W)) - Δ : $(size(Δ[l+1]))")
				
				Δ[l][k,j] = (1 - h[k]^2) * (W[j,:] * Δ[l+1][k,:]')[1]
			end
		end
	end

	# return sensitivity matrices for all layers ∀l = L,...,1
	Δ
end


## Prediction functions 
function predict(net::NeuralNet, testData)

	# return class labels 
end


##---- Test
net = NeuralNet(2, 2, 3, [5])

# net = NeuralNet(3, 2, 1, [7 3])
# initWeights(net, randn(20,2))
# x, s = forwardPropagate(net, randn(net.numInputs,1))
# backPropagate(net, x)

# # simple
# net = NeuralNet(2, 2, 3, [5])
# X = randn(30,2); y = rand(1:3,30)

# not simple
net = NeuralNet(4, 20, 3, [16 8 6])
X = randn(50,20); y = rand(1:3,50)


options = FitOptions()
fit(net, X, y, options::FitOptions, 100)
println(net.weights)