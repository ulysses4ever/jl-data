using Helpme
using Base.Test

# A series of tests corresponding with the examples in examples.jl

macro suggestion_id(ex)
	quote
		z = Int[]
		try
			$(esc(ex))()
			error("Example did not fail.")
		catch e
			for (d, id, msg) in Helpme.search(e, $(string(ex)))
				for i in 1:length(Helpme.keybase)
					k = Helpme.keybase[i]
					if id == k
						append!(z, [i])
						break
					end
				end
			end

			z
		end
	end
end

indices = Int[]

### BEGIN TESTS ###

results = @suggestion_id begin
	a = ["a"=>1]
	b = ["a"=>:a]
	merge(a, b)
end
append!(indices, [findfirst(results, 1)])

results = @suggestion_id begin
	a = "a"
	b = "b"
	a+b
end
append!(indices, [findfirst(results, 2)])

results = @suggestion_id begin
	dataset = {1, 2, 3, 4, 5}
	query = "12345"
	for m in eachmatch(r"\d", query)
		dataset[m]
	end
end
append!(indices, [findfirst(results, 3)])

results = @suggestion_id begin
	dataset = {"a"=>1, "b"=>2}
	query = "ab"
	for m in eachmatch(r"[a-z]", query)
		dataset[m]
	end
end
append!(indices, [findfirst(results, 4)])

results = @suggestion_id begin
	function alpha(a::Dict{ASCIIString, Number})
		a
	end

	alpha(["test"=>255])
end
append!(indices, [findfirst(results, 5)])

results = @suggestion_id begin
	eval(parse("for i in 1:12"))
end
append!(indices, [findfirst(results, 6)])

results = @suggestion_id begin
	eval(parse("for i in 1:12; identity(i); end; end"))
end
append!(indices, [findfirst(results, 7)])

results = @suggestion_id begin
	eval(parse("function Base.&&(a,b); a&&b; end"))
end
append!(indices, [findfirst(results, 8)])

results = @suggestion_id begin
	eval(parse("function Base.||(a,b); a||b; end"))
end
append!(indices, [findfirst(results, 9)])

results = @suggestion_id begin
	function jwngwoijenfoer(a::Array{Float32,8})
		a
	end
	
	jwngwoijenfoer(Float32[1:8])
end
append!(indices, [findfirst(results, 10)])

results = @suggestion_id begin
	eval(parse("function ooewjdbwoedjfvobwe(): nkjsndf=[1:8];end; ooewjdbwoedjfvobwe()"))
end
append!(indices, [findfirst(results, 11)])

results = @suggestion_id begin
	eval(parse("function ooewjdbwoedjfvobwe(): identity(9);end; ooewjdbwoedjfvobwe()"))
end
append!(indices, [findfirst(results, 12)])

results = @suggestion_id begin
	eval(parse("function ooewjdbwoedjfvobwe(): Base.identity(9);end; ooewjdbwoedjfvobwe()"))
end
append!(indices, [findfirst(results, 13)])

results = @suggestion_id begin
	oqwjej = {"sdfre"=>3, "jkndivnf"=>"grewerg", "sdfwerf"=>{}}
	for i in oqwjej
		"Hello, " * oqwjej
	end
end
append!(indices, [findfirst(results, 14)])

results = @suggestion_id begin
	function nuinkjnbk()
		import Base
	end

	nuinkjnbk()
end
append!(indices, [findfirst(results, 15)])

### END TESTS ###

dist = 0
for i in 1:length(indices)
	if indices[i] > 0
		info("Test #"*string(i)*": "*string(indices[i]))
		dist += (indices[i]-1)^2
	else
		info("Test #"*string(i)*": FAILED")
	end
end

dist = sqrt(dist)
info("Distance from ideal: "*string(dist))
@test 0==length(filter(x->x==0, indices))