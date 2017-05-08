#This function generates a least squares regression surface.
#x is a k x l matrix of input data
#n is the highest degree in t (the first variable)
#m is the highest degree in the other variables


@debug function genreg(x,y, n, m)

#This first part generates the matrix X which is the data x 
#in the polynomial fit |X*beta-y| (beta is a vector of poly coefficients)

k=size(x,1)
l=size(x,2)
local X
w=l-1 #number of explanatory, non-time variables

for i=0:n, j= 0:m^w-1
		if i==0 && j==0
			X=ones(k,1)
		else
			A=digits(j,m,w) #integer i in base m with zero padding w
			t=ones(k)
			for p=1:w
				t=t.*(x[:,p+1].^A[p])
			end	
			X=hcat(X,x[:,1].^i.*t)
		end
end

#Now we set up the optimization problem via Convex
b=Variable(size(X,2))
problem=minimize(norm((X*b-y),1))

#Enforce Curvature Bounds
#problem.constraints += [-50 <= b, b <= 50]

#perhaps eventually use Gurobi
solve!(problem, GLPKSolverLP())


return b.value

end


