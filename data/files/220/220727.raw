using PyPlot
using Convex
using Debug
using Distributions
include("gendens.jl")

@debug begin
#Here's the sample we work with initially, a column array consisting of
n=20 #Number of elements in our sample
d=4 #degree of our epi-spline (note that means the coefficient vector
        #is of size 4)
num_part=1 #number of elements in our partition

dist=Gamma() #The distribution we sample from
S=rand(dist,n)

dens=gendens(S,d, num_part)

#Now how does it look?
clf()
y=linspace(-4,4,100)
plot(y,dens(y), label="Predicted Dist.")
hold(true)
plot(y, pdf(dist,y), label="Actual Dist.")
scatter(S,zeros(20,1), label="Sample")
legend(loc="upper right", fancybox="true")
hold(false)

end
