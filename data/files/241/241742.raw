using Distributions
using Winston

# n = 1000;
# y = zeros(n, 1);
# x = 2*(0:(n-1))/(n-1)-1;
# 
# for i in 1:n
#     y[i, 1] = 1.0*sin(8*x[i]) + 0.5*sin(32*x[i]) - 0.1*cos(128*x[i])
# end
# 
# plot(x, y)
# 
# subset = sort(unique(rand(1:n, 100)))
# plot(x[subset], y[subset,:], "r")
# oplot(x, y, "b--")
# 
# ### adjusted mean
# ystar = y[2:end,] + y[1]/(n-1)
# sum(ystar)/n
# mean(y)


####
srand(1)

n = 100;
x = [rand(Uniform(-2, 4), n) rand(Uniform(0, 4), n)];
x = [x x[:,1].*x[:,2] x[:,1].^2];
y = zeros(n);
for i in 1:n
    y[i] = 1.5 - 4*x[i,1] + 2*x[i,2] - 0.5*x[i,3] + 1.0*x[i,4] + rand(Normal(0, 1), 1)[1]
#   y[i] = rand(Normal(1.5 - 4*x[i,1] + 2*x[i,2] - 0.5*x[i,3] + 1.0*x[i,4], 1), 1)[1]
end

X = [ones(n,1) x];
ycent = (y - mean(y)) ./ 1

# TODO vim syntax highlighting on the word in
b1 = inv(X' * X) * X' * y
b2 = inv(X' * X) * X' * ycent

# the difference between the parameters is only in the intercept, (all very significant)
# not sure why b2[1] is not zero
