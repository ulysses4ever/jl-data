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
						push!(z, i)
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
	mydict1 = ["asdfasdf"=>1]
	mydict2 = ["asdfasdf"=>:asdfasdf]
	merge(mydict1, mydict2)
end
push!(indices, findfirst(results, 1))

results = @suggestion_id begin
	asdfasdf = "asdfasdf"
	qwerty = "qwerty"
	asdfasdf + qwerty
end
push!(indices, findfirst(results, 2))

results = @suggestion_id begin
	dataset = {1, 2, 3, 4, 5}
	query = "12345"
	for m in eachmatch(r"\d", query)
		dataset[m]
	end
end
push!(indices, findfirst(results, 3))

results = @suggestion_id begin
	dataset = {"a"=>1, "b"=>2}
	query = "ab"
	for m in eachmatch(r"[a-z]", query)
		dataset[m]
	end
end
push!(indices, findfirst(results, 4))

results = @suggestion_id begin
	function alpha(asdfwef::Dict{ASCIIString, Number})
		asdfwef
	end

	alpha(["test"=>255])
end
push!(indices, findfirst(results, 5))

results = @suggestion_id begin
	eval(parse("for i in 1:12"))
end
push!(indices, findfirst(results, 6))

results = @suggestion_id begin
	eval(parse("for i in 1:12; identity(i); end; end"))
end
push!(indices, findfirst(results, 7))

results = @suggestion_id begin
	eval(parse("function Base.&&(a,b); a&&b; end"))
end
push!(indices, findfirst(results, 8))

results = @suggestion_id begin
	eval(parse("function Base.||(a,b); a||b; end"))
end
push!(indices, findfirst(results, 9))

results = @suggestion_id begin
	function jwngwoijenfoer(asdfwef::Array{Float32,8})
		asdfwef
	end
	
	jwngwoijenfoer(Float32[1:8])
end
push!(indices, findfirst(results, 10))

results = @suggestion_id begin
	eval(parse("function ooewjdbwoedjfvobwe(): nkjsndf=[1:8];end; ooewjdbwoedjfvobwe()"))
end
push!(indices, findfirst(results, 11))

results = @suggestion_id begin
	eval(parse("function ooewjdbwoedjfvobwe(): identity(9);end; ooewjdbwoedjfvobwe()"))
end
push!(indices, findfirst(results, 12))

results = @suggestion_id begin
	eval(parse("function ooewjdbwoedjfvobwe(): Base.identity(9);end; ooewjdbwoedjfvobwe()"))
end
push!(indices, findfirst(results, 13))

results = @suggestion_id begin
	oqwjej = {"sdfre"=>3, "jkndivnf"=>"grewerg", "sdfwerf"=>{}}
	for i in oqwjej
		"Hello, " * oqwjej
	end
end
push!(indices, findfirst(results, 14))

results = @suggestion_id begin
	function nuinkjnbk()
		import Base
	end

	nuinkjnbk()
end
push!(indices, findfirst(results, 15))

results = @suggestion_id begin
	function nuinkjnbk()
		info("Hello World!")
	end

	isdefined(nuinkjnbk)
end
push!(indices, findfirst(results, 16))

results = @suggestion_id begin
	function nuinkjnbk()
		info("Hello World!")
	end

	isdefined("nuinkjnbk")
end
push!(indices, findfirst(results, 17))

results = @suggestion_id begin
	isdefined(nuinkjnbk)
end
push!(indices, findfirst(results, 18))

results = @suggestion_id begin
	myarray = {}
	if length(myarray)
		print(myarray)
	end
end
push!(indices, findfirst(results, 19))

results = @suggestion_id begin
	mystring = "Hello World!"
	if mystring[1:0]
		print(mystring)
	end
end
push!(indices, findfirst(results, 20))

results = @suggestion_id begin
	myarray = Number[]
	if myarray
		print(myarray)
	end
end
push!(indices, findfirst(results, 21))

results = @suggestion_id begin
	asdfgsdg = Float32[]
	push!(asdfgsdg, [3.14])
end
push!(indices, findfirst(results, 22))

results = @suggestion_id begin
	asdfgsdg = {}
	append!(asdfgsdg, 1)
end
push!(indices, findfirst(results, 23))

results = @suggestion_id begin
	myarray = Float32[1:1000]
	for i in 0:1000
		println(myarray[i])
	end
end
dump(results)
push!(indices, findfirst(results, 24))

results = @suggestion_id begin
	mystring = "Hello, I'm test #"
	mynumber = 25
	println(mystring * mynumber)
end
push!(indices, findfirst(results, 25))

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
info("Using weights: "*repr(Helpme.weights))
@test 0==length(filter(x->x==0, indices))