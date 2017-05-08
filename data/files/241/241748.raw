using Distributions

n = 50

### generate from a normal with a covariate
y = zeros(n)
x = [ones(n) sort(rand(n))]
beta = [1.0, 0.5]
xbeta = x * beta
sigma = 0.10 # standard deviation

for i in 1:n
    y[i,:] = rand(Normal(xbeta[i], sigma), 1)
end
# some plotting (ugly julia plotting...)
# using Winston
# plot(x[:,2], y)

### generate with constant mean and variance
z = rand(Normal(([1 0.5]*beta)[1], sigma), n)
# plot(z)

### fit glm's with the two models
