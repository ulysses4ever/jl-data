using PyPlot
using Convex
using Debug
using MathProgBase
using GLPK
using GLPKMathProgInterface
using SCS
@debug begin

N=2 #number of players
n=10 #number of actions for player 1
m=10 #number of actions for player 2

U=Array(Array{Int32,2}, N)

for i=1:N
	U[i] = rand(1:10, n,m) #declare some utilities
end

#a toy example
#U[1]=[1 0; 0 2]
#U[2]=[2 0; 0 1]

#Getting into the optimization
P=Variable(n,m, Positive())

problem = maximize(sum(P.*U[1]+P.*U[2]))
problem.constraints += [sum(P)==1]

#Adding the constraints for player 1
for i = 1:n, q =1:n
		problem.constraints += [sum((U[1][i,:]-U[1][q,:]).*P[i,:]) >=0]
end

#Now for player 2
for j = 1:m, q =1:m
		problem.constraints += [sum((U[2][:,j]-U[2][:,q]).*P[:,j]) >=0]
end


solve!(problem, GLPKSolverLP()) #Should use GLPK for this step

CE=deepcopy(P.value)

print(CE)

#Initialize the problem

W=zeros(size(P))
X=P.value
r=5 #This is just a guess

D=zeros(20,1)
g=zeros(20,1) #error stuff

for k=1:20

#Find the Marginals
M=Array(Array{Float64,2}, N)
for i=1:N
	M[i]=sum(X,N+1-i)
end

Xhat=prod(M)
Xhat=Xhat/sum(Xhat) #normalize
W=W+r*(X-Xhat)
D[k]=norm(X-Xhat)
g[k]=k

if k==1
	W=0
end

problem = minimize(-1*sum(P.*U[1]+P*U[2])+sum(P.*W)+(1/2)*r*norm(P-Xhat)^2)
problem.constraints += [sum(P)==1]

#Adding the constraints for player 1
for i = 1:n, q =1:n
		problem.constraints += [sum((U[1][i,:]-U[1][q,:]).*P[i,:]) >=0]
end

#Now for player 2
for j = 1:m, q =1:m
		problem.constraints += [sum((U[2][:,j]-U[2][:,q]).*P[:,j]) >=0]
end

solve!(problem, SCSSolver(max_iters=100000))

X=P.value

end
	
end #for debug

NE=P.value

if norm(NE-CE)>.01
println("Max utility NE is not Max Utility CE")
end

clf()
scatter(g,D)
