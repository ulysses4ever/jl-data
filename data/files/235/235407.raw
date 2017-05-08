#Random Graph Generator G(n,m)
#The purpose of this file is to demonstrate to Joaquin how much more baller Julia is than Matlab.


function Gr(N,M)
	G=zeros(Integer,N,N)
	VL=[0,0]
	test=true
	x=0
	y=0
	for i=1:M
		#print("Generating Edge #")
		#println(i)
		while test
			VL=ifloor((N-1)*rand(2))
			if G[VL[1]+1,VL[2]+1]==0 && (VL[1]+1)!=(VL[2]+1)
				test=false
			end
		end
		test=true
		#print("Between the Following Vertices:")
		#print(VL[1])
		#print(",")
		#println(VL[2])
		G[VL[1]+1,VL[2]+1]=1
		G[VL[2]+1,VL[1]+1]=1

	end
	return G
end

function experiment1()
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

function experiment2()
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
