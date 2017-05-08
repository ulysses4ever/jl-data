#Experiments Scripts
#This file contains the various batch scripts that we need for the final project. 


include("RandGraph.jl")
export experiment
#In this batch we find the Ms value at different Mu values for a fixed system size. 
#Inputs:
#runtimes: Number of times the experiment will repeat for statistical certainty
#Nu: Number of nodes in the universe
#Mu: Array of different total edges to test
#Ns: The number of nodes in the system
#Outputs:
#out: A matrix whose columns are the results of each run, each index represents a different Mu value
#The rows are the different runs.
function experiment(runtimes::Integer, Nu::Integer, Mu, Ns)
	#if typeof(Mu)==Array{Int64,1}
	#	out=zeros(length(Mu))
	#else
	#	out=zeros(length(Ns))
	#end
	out=Ms(Nu,Mu,Ns)
	for i=2:runtimes
		println(100*i/runtimes)
		out=hcat(out,Ms(Nu,Mu,Ns))
	end
	return out
end

function experiment1Old()
	Ns=[50,100,200,300,500,700,800,900]
	Nu=1000
	Mu=100000
	out=zeros(Integer,Mu,length(Ns))
	println(size(out))
	runtimes=10000
	s=0
	for i=1:runtimes
		println(100*i/runtimes)
		A=Gr(Nu,Mu)
		for n=1:length(Ns)
			#println([1:Ns[n]])
			s=0
			#println(size(A))
			#println(size(getindex(A,[1:Ns[n]],[1:Ns[n]])))
			s=sum(getindex(A,[1:Ns[n]],[1:Ns[n]]))
			#println(s+1)
			s=s/2+1
			out[s,n]=out[s,n]+1
			#println("hello2")
		end
	end
	return out
end

function experiment2Old()
	Nu=1000
	Ns=10
	Mu=[10,50,100,200,240,250,300,400]
	Mu=1000*Mu
	out=zeros(Integer,400000,length(Mu))
	s=0
	runtimes=10000
	for i=1:length(Mu)
		for k=1:runtimes
			println(100*k/runtimes)
			s=0
			A=Gr(Nu,Mu[i])
			s=sum(getindex(A,[1:Ns],[1:Ns]))
			s=s/2+1
			out[s,i]
		end
	end
	return out
end