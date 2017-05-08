#You give me a sample, I want to generate an exponential epi-spline
#estimator. Note that this is only one dimensional

#We want to maximize \Pi_{x_i \in Sample} e^(-s(x_i)) where s(x) is an 
#epi-spline. We will instead maximize the log likelihood
# \sum -s(x_i)
#I've omitted the negative. I don't really get it.

#S is the sample we fit MLE with, d is the degree of our epi-spline
#Again we return a function, called dens

using PyPlot

function gendens(S, d)

#Setting up the optimization problem

a=Variable(d+1)
problem=maximize(sum(poly(a,S)))

#the integrates to one constraint
bounds=[minimum(S)-10 maximum(S)+10] #Bounds on the support
x=linspace(bounds[1], bounds[2], 100)
problem.constraints += [(bounds[2]-bounds[1])*(1/100)*sum(exp(poly(a,x))) <=1]

solve!(problem, SCSSolver(max_iters=100000))

function dens(var)
	return exp(poly(a.value,var))
	end

return dens
 
end
