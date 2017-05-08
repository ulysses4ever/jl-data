#Random Graph Generator G(n,m)
#The purpose of this file is to demonstrate to Joaquin how much more baller Julia is than Matlab.

export Gr, Ms
#This function generates an undirected graph with N nodes and M edges. The M edges are uniformly distributed between the N nodes.
#Inputs:
#N: Number of nodes in the graph
#M: Number of edges in the graph
#Output:
#Integer Adjacency matrix
function Gr(N,M)
	G=zeros(Integer,N,N)#Generate empty graph of zeros
	VL=[0,0]#The node pair between which an edge is generated
	test=true#Gate Variable that checks for repetition
	for i=1:M#Loops to generate M edges
		while test#Test assumes there is a duplicate edge or a self edge
			VL=ifloor((N-1)*rand(2))#Generates random pairing of vertices
			if G[VL[1]+1,VL[2]+1]==0 && (VL[1]+1)!=(VL[2]+1)#If there is no edge present or self edge
				test=false#Set gate variable that edge is valid
			end
		end
		test=true#Reset Gate variable
		G[VL[1]+1,VL[2]+1]=1#Sets randomly chosen edge to 1 
		G[VL[2]+1,VL[1]+1]=1#Sets transpose value since our graph is simple graph
	end
	return G#Returns the graph generated
end

#Generates the number of edges that are present in a sub system Ns given a graph with Nu nodes and Mu edges
#Inputs:
#Nu, number of nodes present in the graph
#Mu, number of edges present in the graph
#Ns, number of nodes in our system
#Output:
#Total Number of edges present in our subgraph.
function Ms(Nu::Integer,Mu::Integer,Ns::Integer)
	U=Gr(Nu,Mu)#Generate Matrix
	return (.5)*sum(getindex(U,[1:Ns],[1:Ns]))#Get the number of edges present in the subsystem
end

#This function returns the array of results for different Mu
function Ms(Nu::Integer,Mu::Array{Int64,1},Ns::Integer)
	out=zeros(length(Mu))
	s=0
	for i=1:length(Mu)
		out[i]=Ms(Nu,Mu[i],Ns)
	end
	return out
end

#This function returns teh array fo results for different Ns
function Ms(Nu::Integer, Mu::Integer, Ns::Array{Int64,1})
	out=zeros(length(Ns))
	s=0
	U=Gr(Nu,Mu)
	for i=1:length(Ns)
		out[i]=(.5)*sum(getindex(U,[1:Ns[i]],[1:Ns[i]]))
	end
	return out
end

