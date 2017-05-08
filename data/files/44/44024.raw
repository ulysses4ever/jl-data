#NN.jl


#Working!!!! (for odd functions with sigmoids only...)
#TODO: fix relu figure out a smart way to do regression (scale all y's to 0-1, descale?
#TODO: something that prescales and post scaling on predictions?
#TODO: pretrain stuff, inputs that result in max activations as opt prob
#TODO: calulate loss function during training (vs iter), see if efficient way to do
#TODO: code profiling
#TODO: LSTM/RNN stuff!!!
#NOTE: can probably reduce parameter size Float64->Float32 because papers

module NN

import Base.length
export buildNN, train, predict #, pretrain

include("NNaux.jl")
include("neurons.jl")

function buildNN(sizes,c::Float64;neuron_type::String="reLu",reg_type::String="L2",verbose::Bool=True,init_type::String="zero")
  #initialize weights and build neural network type based on these inputs
  if verbose
    println("Initializing Neural Network")
  end

  if lowercase(neuron_type) == "relu"
    neuron = reLu
    gradient = GreLu
  elseif lowercase(neuron_type) == "leakyrelu"
    neuron = leakyReLu
    gradient = GleakyReLu
  elseif lowercase(neuron_type) == "tanh"
    neuron = tanh
    gradient = Gtanh
  elseif lowercase(neuron_type) == "sigm"
    neuron = sigm
    gradient = Gsigm
  elseif lowercase(neuron_type) == "softplus"
    neuron = softplus
    gradient = Gsoftplus
    error("Gradient not working")
  else
    error(string("Undefined neuron type ",neron_type))
  end

  #some kind of switch-like object for the regularization

  #initialize weights and biases from sizes somehow

  #assume full connectivity
  sizes_ = [(sizes[i+1],sizes[i]) for i = 1:length(sizes)-1]

  if lowercase(init_type) == "rand"
    weights = randweights(sizes_)
  elseif lowercase(init_type) == "zero"
    weights= zero(sizes_)
  else
    error(string("no such weight initialization method: ", init_type))
  end
  biases = zero(sizes[2:end])


  nn = NeuralNetwork(weights, biases, neuron, gradient, c, reg_type, verbose)

  #maybe do some pretraining with stacked denoising autoencoders?
end

function pretrain(X::Array{Real,2},Y::Array{Real,2},nn::NeuralNetwork;
                  rho::Float64=0.05,alpha::Float64=0.01,beta::Float64=0.1,minibatch_size::Int=100,num_epochs::Int=10)
  #rho = sparsity parameter
  #beta = sparsity penalty

  #pretraining might not be necessary if using relu/softplus units?
  if nn.neuron == reLu || nn.neuron == softplus
    error("Can only pretrain with sigmoid or tanh units")
  end
  error("Not yet implemented")

  if nn.verbose
    println("Pretraining...")
  end
  #need data: X and Y
  #pretrain with AE or RBM?

  m = size(X,2)
  assert(m == size(Y,2))
  L = length(nn.biases)

  for l = 2:L-1
    #ignore input and output layers

    #something

    #pass through data to estimate rho_
    for i = 1:m

    end
    #pass through data to do SGD
    for epoch = 1:num_epochs
      for i = 1:m
        #minibatch GD stuff
        #for each example, need feed forward pass, and backprop pass
      end
    end #epoch

  end #l

  return nn
end

#maybe also have a train! function, probably not necessary though
function train(X::Array{Float64,2},Y::Array{Float64,2},nn::NeuralNetwork;
               alpha::Float64=0.01,mu::Float64=0.9,minibatch_size::Int=100,num_epochs::Int=10,update_type::String="momentum")
  #each column of X is a training example, same with Y--we do this to access things in memory order
  m = size(X,2)
  assert(m == size(Y,2))

  L = length(nn.biases)

  dW = zero(nn.weights)#Dict{Int,Array{Float64,2}}([i=>zeros(size(nn.weights[i])) for i = 1:L])
  db = zero(nn.biases)#Dict{Int,Array{Float64,2}}([i=>zeros(size(nn.biases[i])) for i = 1:L])
  #momentum update stuff
  vW = zero(nn.weights)
  vb = zero(nn.biases)

  if m < minibatch_size
    minibatch_size = m
    num_epochs = 1
    #^^ probably not a good idea to use the same data multiple times if you've only got 1 batch
  end

  count = 0
  batch = 1
  s = ""
  for epoch = 1:num_epochs
    p = randperm(m)
    for i_ = 1:m
      i = p[i_]
      x = X[:,i]
      y = Y[:,i]
      y_, a, z = feedforward(x,nn)
      dW_, db_ = backprop(a,z,y,nn)

      add!(dW,dW_)
      add!(db,db_)

      #increment dW, db
      if mod(count,minibatch_size) == 0
        # fold all of this into a GDupdate function?
        if nn.verbose
          print(repeat("\b \b",length(s)))
          s = string("Minibatch: ",batch)
          print(s)
        end
        #update weights, biases (maybe include another function to make this cleaner)
        #might be a cleaner way to do this (make a function over weights than nn holds?)
        if nn.reg == "L2" || nn.reg == "Ridge"
          reg = deepcopy(nn.weights)

        elseif nn.reg == "L!" || nn.reg == "Lasso"
          reg = deepcopy(nn.weights)
          for i = 1:L
            reg[i][find(reg[i])] = 1
          end
        end
        #might be a neater way to do this
        if lowercase(update_type) == "momentum"
          #velocity update
          vW = mu*vW+(-alpha)*(((1./minibatch_size)*dW) + (nn.c*reg))
          vb = mu*vb + (-alpha/minibatch_size)*db
          #vW = add!(mult!(vW,mu),mult!(add!(mult!(dW,1./minibatch_size),mult!(reg,nn.c)),-alpha))
          #vb = add!(mult!(vb,mu),mult!(db,-alpha/minibatch_size))

          #"position" update
          nn.weights += vW
          nn.biases += vb
          #add!(nn.weights,vW)
          #add!(nn.biases,vb)
        elseif lowercase(update_type) == "nesterov"
          #nesterov momentum
          vW_ = deepcopy(vW)
          vb_ = deepcopy(vb)

          vW = mu*vW + (-alpha)*((1./minibatch_size)*dW + nn.c*reg)
          vb = mu*vb + (-alpha/minibatch_size)*db

          #vW = add!(mult!(vW,mu),mult!(add!(mult!(dW,1./minibatch_size),mult!(reg,nn.c)),-alpha))
          #vb = add!(mult!(vb,mu),mult!(db,-alpha/minibatch_size))

          nn.weights += (-mu)*vW_+(1+mu)*vW
          nn.biases += (-mu)*vb_ + (1+mu)*vb

          #add!(nn.weights,add!(mult!(vW_,-mu),mult!(vW,1+mu)))
          #add!(nn.biases,add!(mult!(vb_,-mu),mult!(vb,1+mu)))

        elseif lowercase(update_type) == "sgd"
          #vanilla SGD
          nn.weights += (-alpha)*((1./minibatch_size)*dW+nn.c*reg)
          nn.biases += (-alpha/minibatch_size)*db

          #add!(nn.weights,mult!(add!(mult!(dW,1./minibatch_size),mult!(reg,nn.c)),-alpha))
          #add!(nn.biases,mult!(db,-alpha/minibatch_size))
        else
          error(string("No update rule: ",update_type))
        end


        dW = zero(nn.weights)
        db = zero(nn.biases)

        #reset dW, db
        batch += 1
      end

      count += 1
    end #i_
  end #epoch

  return nn

end

function feedforward(x::Array{Float64,1},nn::NeuralNetwork)
  L = length(nn.biases)
  a = zero(nn.biases)#Dict{Int,Array{Float64,1}}([i=>zeros(length(nn.biases[i])) for i = 1:L])
  z = zero(nn.biases)#0 #same form as a
  a[0] = deepcopy(x)

  #i think i screwed up something here--last level should just be a linear function approximator i think
  #so for i=L, it would be teh same except a[L][:] = z[L][:]
  #maybe have something that would make it a sigmoid for classification or whatever

  for i = 1:L-1 #L
    z[i][:] = nn.weights[i]*a[i-1]+nn.biases[i]
    a[i][:] = nn.neuron(z[i])
  end
  z[L][:] = nn.weights[L]*a[L-1]+nn.biases[L]
  a[L][:] = z[L]

  return a[L], a,z
end

function backprop(a::NNWeights,z::NNWeights,y::Array{Float64,1},nn::NeuralNetwork)
  L = length(nn.biases)
  dW = zero(nn.weights)#Dict{Int,Array{Float64,2}}([i=>zeros(size(nn.weights[i])) for i = 1:L])
  db = zero(nn.biases)#Dict{Int,Array{Float64,2}}([i=>zeros(size(nn.biases[i])) for i = 1:L])

  #indexing error with the weights--check it over
  #since im screwing up the things, I think the first gradient term should just be 1 since its just a linear classifier->f(Wx+b)=Wx+b
  #stil screwing things out, need to pen and paper fix things up

  #note: can save time if using sigm by letting the gradient be a.*(1-a) rather than sigm(z).*(1-sigm(z))
  del = zero(nn.biases)#Dict{Int,Array{Float64,2}}([i=>zeros(size(1)) for i = 1:L])
  del[L] = -(y-a[L]).*ones(size(z[L]))#nn.gradient(z[L])
  for l = L:-1:1
    #=
    println("Layer $l")
    println(size(nn.weights[l]))
    println(size(del[l]))
    println(size(a[l]))
    println(size(z[l]))
    println(size(nn.gradient(z[l])))
    println(size(nn.weights[l]'*del[l]))
    println(size((nn.weights[l]'*del[l]).*nn.gradient(z[l])))
    println(size(del[l]*a[l]'))
    =#
    if l > 1
      #println(size(del[l-1]))
      del[l-1] = (nn.weights[l]'*del[l]).*nn.gradient(z[l-1])
    end
    dW[l] = del[l]*a[l-1]'
    db[l] = del[l]
  end

  return dW, db

end

function backprop(a::NNWeights,z::NNWeights,y::Float64,nn::NeuralNetwork)
  L = length(nn.biases)
  dW = zero(nn.weights)#Dict{Int,Array{Float64,2}}([i=>zeros(size(nn.weights[i])) for i = 1:L])
  db = zero(nn.biases)#Dict{Int,Array{Float64,2}}([i=>zeros(size(nn.biases[i])) for i = 1:L])

  #check indices
  del = zero(nn.biases)#Dict{Int,Array{Float64,2}}([i=>zeros(size(1)) for i = 1:L])
  del[L] = -(y-a[L]).*nn.gradient(z[L])
  for l = L:-1:1
    if l > 1
      del[l-1] = (nn.weights[l]'*del[l]).*nn.gradient(z[l-1])
    end
    dW[l] = del[l]*a[l-1]'
    db[l] = del[l]
  end

  return dW, db

end

function predict(nn::NeuralNetwork, x::Float64)
  y, a, z = feedforward(x,nn)
  return y
end


function predict(nn::NeuralNetwork, x::Array{Float64,1})
  y, a, z = feedforward(x,nn)
  return y
end

function predict(nn::NeuralNetwork, X::Array{Float64,2})
  L = length(nn.biases)
  m = size(X,2)
  Y = zeros(length(nn.biases[L]),m)
  for i = 1:m
    y, a, z = feedforward(X[:,i],nn)
    Y[:,i] = y
  end
  return Y
end

end #module
