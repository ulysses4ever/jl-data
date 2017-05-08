# xorELM.jl

# two input neurons
X = [[-1 -1], [-1 +1], [+1 -1], [+1 +1]]'
# one output neuron
Y = [+1 -1 -1 +1]

nTrainData = size(X, 2)
nInputNeurons = size(X, 1)
nHiddenNeurons = 2500

# regularization parameter
C = 100.

# generate random input weight matrix and bias
inW = rand(nHiddenNeurons, nInputNeurons) * 2 - 1
bias = rand(nHiddenNeurons, 1)

# feed forward training data through hidden layer
H = zeros(nHiddenNeurons, nTrainData)
for i=1:nTrainData
   H[:,i] = 1 ./ (1 + exp(-inW*X[:,i]-bias))
end

# regularized output weights matrix
outW = (eye(nHiddenNeurons)/C + H * H') \ H * Y'

# output for the training data
scores = sign(H' * outW)

using PyPlot

function meshgrid{T}(vx::AbstractVector{T}, vy::AbstractVector{T})
   m, n = length(vy), length(vx)
   vx = reshape(vx, 1, n)
   vy = reshape(vy, m, 1)
   (repmat(vx, m, 1), repmat(vy, 1, n))
end

# generate a grid
span = linspace(-1.5, 1.5, 100)
P1, P2 = meshgrid(span, span)
pp = [P1[:] P2[:]]'

nInputPatterns = size(pp, 2)

# simulate neural network on a grid
#
# feed forward training data through hidden layer
H = zeros(nHiddenNeurons, nInputPatterns)
for i=1:nInputPatterns
   H[:,i] = 1 ./ (1 + exp(-inW*pp[:,i]-bias))
end
# output layer
aa = H' * outW
aa = reshape(aa, length(span), length(span))

# plot classification regions
figure(1)
clf()
pcolormesh(P1, P2, aa, cmap="cool")

figure(2)
clf()
pcolormesh(P1, P2, sign(aa), cmap="cool")
