#You give me a sample, I want to generate an exponential epi-spline
#estimator. Note that this is only one dimensional

#We want to maximize \Pi_{x_i \in Sample} e^(-s(x_i)) where s(x) is an 
#epi-spline. We will instead maximize the log likelihood
# \sum -s(x_i)
#I've omitted the negative. I don't really get it.

#S is the sample we fit MLE with, d is the degree of our epi-spline
#Again we return a function, called dens

using Convex
using SCS
using Debug

include("polyfun.jl")

@debug function gendens(S, d, num_part)

#Setting up the optimization problem

bounds=[minimum(S)-.25*(maximum(S)-minimum(S)) maximum(S)+.25*(maximum(S)-minimum(S))] 
	#Bounds on the support. Extend the bounds by a quarter of the observed range on both sides

x=linspace(bounds[1], bounds[2], 100)

gap = (bounds[2]-bounds[1])/num_part
cut_points = bounds[1]*ones(num_part) #the points where the polynomial splits
for i =1:num_part
	cut_points[i]=cut_points[i]+i*gap
end

function piece_poly(a, cut_points, X)
	R=Array(AbstractExpr,size(X,1))
	for i = 1:size(X,1)
		t=false #a trigger. If a point is not bounded by a point in cut_point then send 
			#it to the last polynomial segment
		for j = 1:size(cut_points, 1)
			if X[i] <= cut_points[j]
			R[i]=poly(a[:, j], X[i])
			t=true
			break
			end
		end
		if t==false
		R[i]=poly(a[:, size(cut_points,1)], X[i])
		end
	end
return R
end

a=Variable(d+1, num_part)
problem=maximize(sum(piece_poly(a, cut_points, S)))


#the integrates to one constraint
#Eventually introduce soft constraints
riemsumm = cut_points[1]-bounds[1])*(1/100)*sum(exp(poly(a[:,1],x[find(i->bounds[1] <= x[i] <= cut_points[1])])))
# a for loop summing the rest of the integral

problem.constraints += [(bounds[2]-bounds[1])*(1/100)*sum(exp(piece_poly(a,cut_points,x))) <=1]

solve!(problem, SCSSolver(max_iters=100000))

@bp

function dens(var)
	return exp(piece_poly(a.value, cut_points, var))
	end

return dens
 
end
