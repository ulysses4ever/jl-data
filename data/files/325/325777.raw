using DataFrames

function createCentroid(startPoint, r)

	modifiers=createSimpleDot(length(startPoint))

	[ (r*abs(modifiers[i]))+startPoint[i] for i=1:length(startPoint) ]

end


function createDots(startPoints::DataFrame, amount;	 max_r=2)

	dimnames= keys(startPoints)

	for i=1:amount
		r = rand()*max_r
		dot = DataFrame()
		modifiers=createSimpleDot(length(dimnames))
		for j=1:length(dimnames)
			dot[dimnames[j]] = (r*modifiers[j])+startPoints[1, dimnames[j]]
		end
		startPoints=vcat(startPoints,dot)
	end
	startPoints
end

function createSimpleDot(dims::Int64)
	splits=Float64[0,1]
	for i=1:dims-1
		push!(splits,rand())
	end

	sort!(splits)

	[ sign(sqrt(splits[i+1]-splits[i])) for i=1:length(splits)-1 ]
end

function sign(value)
	x = rand()
	if x>= 0.5
		-value
	else
		value
	end
end
