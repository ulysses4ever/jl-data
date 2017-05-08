#NN.jl


#Working!!!! (for odd functions with sigmoids only...)
#TODO: figure out nice way to do learning rate annealing, changing the loss function: L2/MSE, L1, softmax?, huber!?!?
#TODO: pretrain stuff, inputs that result in max activations as opt prob
#TODO: code profiling
#TODO: LSTM/RNN stuff!!!
#NOTE: can probably reduce parameter size Float64->Float32 because papers
#NOTE: might be more efficient to have explicit Integer and Float versions rather than casting everything as real

module NN

import Base.length, Base.norm, Base.sqrt
export buildNN, train, predict #, pretrain

include("NNaux.jl")
include("neurons.jl")

function buildNN(sizes,c::Float64,yl::Array{Float64,1},yu::Array{Float64,1};
                 neuron_type::String="reLu",reg_type::String="L2",verbose::Bool=True,init_type::String="zero",output_neuron_type::String="none")
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


  if lowercase(output_neuron_type) == "relu"
    output_neuron = reLu
    output_neuron_gradient = GreLu
  elseif lowercase(output_neuron_type) == "leakyrelu"
    output_neuron = leakyReLu
    output_neuron_gradient = GleakyReLu
  elseif lowercase(output_neuron_type) == "tanh"
    output_neuron = tanh
    output_neuron_gradient = Gtanh
  elseif lowercase(output_neuron_type) == "sigm"
    output_neuron = sigm
    output_neuron_gradient = Gsigm
  elseif lowercase(output_neuron_type) == "softplus"
    output_neuron = softplus
    output_neuron_gradient = Gsoftplus
    error("Gradient not working")
  elseif lowercase(output_neuron_type) == "none"
    output_neuron = (x)->x
    output_neuron_gradient = (x)->ones(size(x))
  else
    error(string("Undefined neuron type ",neron_type))
  end

  assert(length(yl) == length(yu))
  assert(!( false in (yl.<yu) ) )

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


  nn = NeuralNetwork(weights, biases, neuron, gradient,output_neuron,output_neuron_gradient, c, reg_type, yu, yl,[0],[0], verbose)

  return nn
  #maybe do some pretraining with stacked denoising autoencoders?
end

function buildNN(sizes,c::Float64,yl::Float64,yu::Float64;
                 neuron_type::String="reLu",reg_type::String="L2",verbose::Bool=True,init_type::String="zero",output_neuron_type::String="none")
  return buildNN(sizes,c,[yl],[yu],neuron_type=neuron_type,reg_type=reg_type,verbose=verbose,init_type=init_type,output_neuron_type=output_neuron_type)
end

function pretrain(X::Array{Real,2},Y::Array{Real,2},nn::NeuralNetwork;
                  rho::Float64=0.05,alpha::Float64=0.01,beta::Float64=0.1,minibatch_size::Int=100,num_epochs::Int=10)
  #rho = sparsity parameter
  #beta = sparsity penalty

  #HOWTODO: for each layer, build a 2-layer NN, use normal feedforward, use AEBackProp
  #  BUT feedforward needs to be a sigm activation function on the end, so do pre/post scaling first
  #just going to do vanilla GD since we would have to compute rho_ for each update

  #pretraining might not be necessary if using relu/softplus units?
  if !(nn.neuron == sigm || nn.neuron == tanh)
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
               alpha::Float64=0.01,mu::Float64=0.9,minibatch_size::Int=100,num_epochs::Int=10,
               update_type::String="momentum",calculate_loss::Bool=true,half_rate::Int=1,loss_fn::String="L1")
  #mu is the "mass" for nesterov/momentum, and it is also the decay rate for rmsprop
  #each column of X is a training example, same with Y--we do this to access things in memory order
  m = size(X,2)
  assert(m == size(Y,2))

  #whiten data
  #it mightttttt be necessary to have a separate preproc data pass if theres too much data for memory
  nn.xu = vec(mean(X,2))
  nn.xs = vec(std(X,2))

  losses = Float64[]
  losses_true = Float64[]

  L = length(nn.biases)

  dW = zero(nn.weights)#Dict{Int,Array{Float64,2}}([i=>zeros(size(nn.weights[i])) for i = 1:L])
  db = zero(nn.biases)#Dict{Int,Array{Float64,2}}([i=>zeros(size(nn.biases[i])) for i = 1:L])
  #momentum update stuff/cache
  vW = zero(nn.weights)
  vb = zero(nn.biases)

  if m < minibatch_size
    minibatch_size = m
    #num_epochs = 1
    #^^ probably not a good idea to use the same data multiple times if you've only got 1 batch--NVM thats just gradient descent-durr
  end

  count = 0
  batch = 1
  s = ""
  for epoch = 1:num_epochs
    println("Epoch $epoch")
    if minibatch_size != m
      p = randperm(m)
    else
      p = [1:m]
    end
    for i_ = 1:m
      i = p[i_]
      x = (X[:,i]-nn.xu)./nn.xs
      y = Y[:,i]#(Y[:,i]-((nn.yl+nn.yu)/2))./((nn.yu-nn.yl)./2)
      y_, a, z = feedforward(x,nn)
      dW_, db_ = backprop(a,z,y,nn)


      dW += dW_
      db += db_
      #add!(dW,dW_)
      #add!(db,db_)

      #increment dW, db
      if mod(count,minibatch_size) == 0
        # fold all of this into a GDupdate function?
        #calculate loss function
        if calculate_loss
          loss = 0.
          for j = 1:m
            x = (X[:,j]-nn.xu)./nn.xs
            y = (Y[:,j])#-((nn.yl+nn.yu)/2))./((nn.yu-nn.yl)./2)
            y_, a, z = feedforward(x,nn)
            loss += 0.5*norm(y-y_,1)#(y-y_)'*(y-y_)#squared error
          end

          loss /= m

          losses = [losses;loss]

          loss += 0.5*nn.c*norm(nn.weights)
          loss += 0.5*nn.c*norm(nn.biases)
          losses_true = [losses_true;loss]
        end

        if nn.verbose
          print(repeat("\b \b",length(s)))
          s = string("Minibatch: ",batch)
          print(s)
        end
        #update weights, biases (maybe include another function to make this cleaner)
        #might be a cleaner way to do this (make a function over weights than nn holds?)

        updateWeights!(nn, dW, db, vW, vb,alpha,mu,m,update_type)

        dW = zero(nn.weights)
        db = zero(nn.biases)

        #reset dW, db
        batch += 1

        if mod(batch,half_rate) == 0
          alpha /= 2
        end
      end

      count += 1
    end #i_
  end #epoch

  return nn, losses, losses_true, alpha

end

function train(X::Array{Float64,1},Y::Array{Float64,1},nn::NeuralNetwork;
               alpha::Float64=0.01,mu::Float64=0.9,minibatch_size::Int=100,num_epochs::Int=10,update_type::String="momentum",calculate_loss::Bool=true,half_rate::Int=1)
  return train(X',Y',nn,alpha=alpha,mu=mu,minibatch_size=minibatch_size,num_epochs=num_epochs,
               update_type=update_type,calculate_loss=calculate_loss,half_rate=half_rate)

end

function updateWeights!(nn::NeuralNetwork, dW::NNWeights, db::NNWeights, vW::NNWeights, vb::NNWeights,
                       alpha::Float64,mu::Float64,m::Int,update_type::String)

  if nn.reg == "L2" || nn.reg == "Ridge"
    reg = deepcopy(nn.weights)

  elseif nn.reg == "L1" || nn.reg == "Lasso"
    reg = deepcopy(nn.weights)
    for i = 1:L
      reg[i] = sign(reg[i])
      #reg[i][find(reg[i])] = 1
    end
  end
  #might be a neater way to do this
  if lowercase(update_type) == "momentum"
    #velocity update
    vW = mu*vW+(-alpha./m)*((dW) + (nn.c*reg))
    vb = mu*vb + (-alpha./m)*db
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

    vW = mu*vW + (-alpha./m)*(dW + nn.c*reg)
    vb = mu*vb + (-alpha./m)*db

    #vW = add!(mult!(vW,mu),mult!(add!(mult!(dW,1./minibatch_size),mult!(reg,nn.c)),-alpha))
    #vb = add!(mult!(vb,mu),mult!(db,-alpha/minibatch_size))

    nn.weights += (-mu)*vW_+(1+mu)*vW
    nn.biases += (-mu)*vb_ + (1+mu)*vb

    #add!(nn.weights,add!(mult!(vW_,-mu),mult!(vW,1+mu)))
    #add!(nn.biases,add!(mult!(vb_,-mu),mult!(vb,1+mu)))

  elseif lowercase(update_type) == "sgd"
    #vanilla SGD
    nn.weights += (-alpha./m)*(dW+nn.c*reg)
    nn.biases += (-alpha./m)*db

    #add!(nn.weights,mult!(add!(mult!(dW,1./minibatch_size),mult!(reg,nn.c)),-alpha))
    #add!(nn.biases,mult!(db,-alpha/minibatch_size))
  elseif lowercase(update_type) == "rmsprop"
    vW = mu*vW + (1-mu)*(dW)^2
    vb = mu*vb + (1-mu)*(db)^2

    nn.weights += (-alpha/m)*dW/sqrt(vW+1e-8)
    nn.biases += (-alpha/m)*db/sqrt(vb+1e-8)

  else
    error(string("No update rule: ",update_type))
  end

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
  a[L][:] = nn.output_neuron(z[L])

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
  #del[L] = -(y-a[L]).*nn.output_gradient(z[L])#nn.gradient(z[L])#ones(size(z[L]))#squared error
  del[L] = -sign(y-a[L]).*nn.output_gradient(z[L]) #L1 error
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
  return backprop(a,z,[y],nn)
end

function predict(nn::NeuralNetwork, x::Float64)
  return predict(nn,[x])
end


function predict(nn::NeuralNetwork, x::Array{Float64,1})
  y, a, z = feedforward((x-nn.xu)./nn.xs,nn)
  return y#.*((nn.yu-nn.yl)/2)+((nn.yl+nn.yu)/2)
end

function predict(nn::NeuralNetwork, X::Array{Float64,2})
  L = length(nn.biases)
  m = size(X,2)
  Y = zeros(length(nn.biases[L]),m)
  for i = 1:m
    y, a, z = predict(X[:,i],nn)
    Y[:,i] = y
  end
  return Y
end

end #module
