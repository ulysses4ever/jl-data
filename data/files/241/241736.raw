using Distributions
using Winston

n = 1000;
y = zeros(n, 1);
x = 2*(0:(n-1))/(n-1)-1;

for i in 1:n
    y[i, 1] = 1.0*sin(8*x[i]) + 0.5*sin(32*x[i]) - 0.1*cos(128*x[i])
end

plot(x, y)

subset = sort(unique(rand(1:n, 100)))
plot(x[subset], y[subset,:])

### adjusted mean
ystar = y[2:end,] + y[1]/(n-1)
sum(ystar)/n
mean(y)
