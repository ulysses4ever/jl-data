using GLM
using DataFrames
using Distributions
# GLM might automatically load DataFrames and Distributions


n = 50;

### generate from a normal with a covariate
srand(1)    # seed

y = zeros(n);
x = [ones(n) sort(rand(n))];
beta = [1.5, 0.75];
xbeta = x * beta;
sigma = 0.10; # standard deviation

for i in 1:n
    y[i,:] = rand(Normal(xbeta[i], sigma), 1)
end
# some plotting (ugly julia plotting...)
# using Winston
# plot(x[:,2], y)
data1 = DataFrame(y=y, x=x[:,2])

### generate with constant mean and variance
z = rand(Normal(([1 0.5]*beta)[1], sigma), n)
# the mean for this normal is the overall mean of the previous normal
# plot(z)
data2 = DataFrame(y=z, x=x[:,2])

### fit glm's with the two models
mod11 = glm(y ~ 1, data1, Normal(), IdentityLink())
mod12 = glm(y ~ x, data1, Normal(), IdentityLink())
# need to fix the vim highlighter on "data1" (notice that dumb red number)

mod21 = glm(y ~ 1, data2, Normal(), IdentityLink())
mod22 = glm(y ~ x, data2, Normal(), IdentityLink())

### calculate deviance (for normal regression)
function calc_deviance(model)
    b = coef(model)
    y = model.mf.df[1]  # go into model frame (mf), then into data frame (df), then 
                        # grab the first column ([1]). this assumes univariate data
    x = model.mm.m # model matrix
    n = length(y)
    s2 = (y-x*b)' * (y-x*b) / (n - length(b))
    (1 ./ s2 * sum((y-x*b).^2))[1]
end
deviance(mod11)
deviance(mod12)
deviance(mod21)
deviance(mod22)
calc_deviance(mod11)
calc_deviance(mod12)
calc_deviance(mod21)
calc_deviance(mod22)





### vim syntax highlighting problem examples
asdf1(asdf1)    # something is messed up when inside a function
asdf1[:, asdf1] # and within brackets
(asdf1)         # doesn't have to be a function
[asdf1]
