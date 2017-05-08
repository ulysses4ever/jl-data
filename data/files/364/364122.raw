#-------------------------Structures for holding opt and data---------------------------------

immutable Options
	iters::Int64
	spcrd::Int64
	space
	inittr::Float64
	tolred::Float64
	toltr::Float64
	maxiter::Int64	
	
	minstep::Float64
	maxstep::Float64
	steptol::Float64
	abstol::Vector{Float64}
end

immutable ErrorData
	obsv::Vector{Int64}
	tsample::Vector{Float64}	
	tmax::Int64
	expdat::Matrix{Float64}
	initp::Vector{}
end

immutable PlotData
	obsv::Vector{Int64}	
	tsample::Vector{Float64}	
	tmax::Int64
	expdat::Matrix{Float64}
	initp::Vector{}
	
	steptol::Float64
	abstol::Vector{Float64}
	minstep::Float64
	maxstep::Float64
end

