#NNTest.jl

#NN.jl testbed
include("NN.jl")
using NN, PyPlot

x = linspace(-0.5,0.5,100)#(rand(1,10000)-0.5)
f = (x)->x
#f = (x)->exp(x)
#f = (x)->x.*x.*x
#f = (x)->sin(x)
#f = (x)->x.*x+1
#f = (x)->sin(exp(x.*x.*x-x+12)).^2
y = f(x)

alpha_final = 0.1
nn = buildNN([1;2;1],0.00001,minimum(y),maximum(y),neuron_type="relu",reg_type="L2",verbose=false,init_type="rand",output_neuron_type="none")
nn,losses, losses_true,alpha_final = train(x,y,nn,alpha=alpha_final,num_epochs=3,minibatch_size=1,update_type="rmsprop",half_rate=1000)
x_ = linspace(-0.5,0.5,100)
y_ = [predict(nn,[x_[i]]) for i = 1:length(x_)]
#plotting stuff
#plot(x_,f(x_),x_,y_)