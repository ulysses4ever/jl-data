#neurons.jl
#for use with NN.jl and NNaux.jl
#really just here to keep things neat

#put into neurons.jl?
########Activation Functions and Gradients ######################
#################################################################
#activation functions and gradients--might put in a different file to keep things neat
function sigm(x)
  return 1./(1+exp(-x))
end

function reLu(x)
  return max(0.,x)
end

function leakyReLu(x,alpha::Float64=0.01)
  return max(alpha*x,x)
end

function softplus(x)
  return log(1+exp(x))
end

#gradients/derivatives of activation functions--elementwise
function Gsigm(x)
  return sigm(x).*(1-sigm(x))
end

function GreLu(x)
  return x > 0.? 1.: 0.
end

function GleakyReLu(x,alpha::Float64=0.01)
  return x > 0.? 1.: alpha
end

function Gtanh(x)
  return 1 - tan(x).*tan(x)
end

#=
function Gsoftplus(x::real)
  return sigm(x)
end

@vectorize_1arg Real GSoftplus
=#

@vectorize_1arg Real sigm
@vectorize_1arg Real reLu
@vectorize_1arg Real softplus
@vectorize_1arg Real Gsigm
@vectorize_1arg Real Gtanh
@vectorize_1arg Real GreLu
@vectorize_1arg Real GleakyReLu



#############################################################
