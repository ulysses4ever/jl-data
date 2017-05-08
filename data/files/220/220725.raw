using PyPlot
using Convex

include("gendens.jl")

#Here's the sample we work with initially, a column array consisting of
#20 samples from a N(0,1) distribution
n=20 #Number of elements in our sample
d=3 #degree of our epi-spline (note that means the coefficient vector
        #is of size 4)
num_part=2 #number of elements in our partition

S = randn(n,1)

dens=gendens(S,d, num_part)

#Now how does it look?
clf()
y=linspace(-5,5,100)
plot(y,dens(y), label="Predicted Dist.")
hold(true)
plot(y, 1/sqrt(2*pi)*exp((-1/2)*y.^2), label="Actual Dist.")
scatter(S,zeros(20,1), label="Sample")
legend(loc="upper right", fancybox="true")
hold(false)

