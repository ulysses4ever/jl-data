type NestedDataBAL <: NestedData
	Mu::Vector{Float64}
	NFac::Int64
	Nlvl::Vector{Int64}
	VC::Vector{Float64}
  re::Array{Any,1}
  n::Int64 
  dat::DataFrame  
end


function NestedDataBAL(Mu::Vector{Float64}, NFac::Int64, Nlvl::Vector{Int64}, VC::Vector{Float64})
	nf=NFac; nl=Nlvl; nll=length(nl)
	nf+1 == length(nl) ? n=prod(Nlvl) : error("number of elements in level vector is length of factors vector + 1")
    if length(Mu) == 1 
      # dat[:y]+= repeat(Mu,inner=[n]) 
      y=repeat(Mu,inner=[n]) + rand(Normal(0.0,VC[end]),n)
      dat=DataFrame(y=y) 
    else 
      y=Mu + rand(Normal(0.0,VC[end]),n)
      dat=DataFrame(y=y) 
    end 

    re={ zeros(prod(nl[1:i])) for i in 1:(nll-1)}  
    
    for i in 1:(nll-1)
        Z=kron(speye(prod(nl[1:i])),sparse(ones(prod(nl[i+1:end]))))
    	if VC[i] > 0.0
    		re[i]=rand(Normal(0.0,VC[i]),prod(nl[1:i]))
        dat[:y]+= Z * re[i]
    	end
    	
        dat[symbol("x$i")]=pool( convert(Array{Int64,1},Z* [1:prod(nl[1:i])]) )
    end
    dat[symbol("id")]=pool([1:n] )
    NestedDataBAL(Mu,NFac,Nlvl,VC,re,n,dat);
 end

 

