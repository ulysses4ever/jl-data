using Helpme
using Base.Test
using Lint

# A series of tests corresponding with the examples in examples.jl

const indices = Int[]
macro test_suggestion(num, ex)
	global indices
	quote
		results = Int[]
		try
			$(esc(ex))()
			warn("Test #"*$(string(num))*" did not raise exception.")
		catch e
			search = Helpme.search(e, $(string(ex)))
			for example in search
				for i in 1:length(Helpme.database)
					if example == Helpme.database[i]
						push!(results, i)
						break
					end
				end
			end

			index = findfirst(results, $num)
			if index == 0
				warn("Test #"*$(string(num))*" FAILED: suggested $results instead.")
			end

			push!(indices, index)
		end
	end
end

info("Using weights: "*repr(Helpme.weights))

### BEGIN TESTS ###

@test_suggestion 1 begin
	mydict1 = ["asdfasdf"=>1]
	mydict2 = ["asdfasdf"=>:asdfasdf]
	merge(mydict1, mydict2)
end

@test_suggestion 2 begin
	asdfasdf = "asdfasdf"
	qwerty = "qwerty"
	asdfasdf + qwerty
end

@test_suggestion 3 begin
	dataset = {1, 2, 3, 4, 5}
	query = "12345"
	for m in eachmatch(r"\d", query)
		dataset[m]
	end
end

@test_suggestion 4 begin
	dataset = {"a"=>1, "b"=>2}
	query = "ab"
	for m in eachmatch(r"[a-z]", query)
		dataset[m]
	end
end

@test_suggestion 5 begin
	function alpha(asdfwef::Dict{ASCIIString, Number})
		asdfwef
	end

	alpha(["test"=>255])
end

@test_suggestion 6 begin
	eval(parse("for i in 1:12"))
end

@test_suggestion 7 begin
	eval(parse("for i in 1:12; identity(i); end; end"))
end

@test_suggestion 8 begin
	eval(parse("function Base.&&(a,b); a&&b; end"))
end

@test_suggestion 9 begin
	eval(parse("function Base.||(a,b); a||b; end"))
end

@test_suggestion 10 begin
	function jwngwoijenfoer(asdfwef::Array{Float32,8})
		asdfwef
	end
	
	jwngwoijenfoer(Float32[1:8])
end

@test_suggestion 11 begin
	eval(parse("function ooewjdbwoedjfvobwe(): nkjsndf=[1:8];end; ooewjdbwoedjfvobwe()"))
end

@test_suggestion 12 begin
	eval(parse("function ooewjdbwoedjfvobwe(): identity(9);end; ooewjdbwoedjfvobwe()"))
end

@test_suggestion 13 begin
	eval(parse("function ooewjdbwoedjfvobwe(): Base.identity(9);end; ooewjdbwoedjfvobwe()"))
end

@test_suggestion 14 begin
	oqwjej = {"sdfre"=>3, "jkndivnf"=>"grewerg", "sdfwerf"=>{}}
	for i in oqwjej
		"Hello, " * oqwjej
	end
end

@test_suggestion 15 begin
	function nuinkjnbk()
		import Base
	end

	nuinkjnbk()
end

@test_suggestion 16 begin
	function nuinkjnbk()
		info("Hello World!")
	end

	isdefined(nuinkjnbk)
end

@test_suggestion 17 begin
	function nuinkjnbk()
		info("Hello World!")
	end

	isdefined("nuinkjnbk")
end

@test_suggestion 18 begin
	isdefined(nuinkjnbk)
end

@test_suggestion 19 begin
	myarray = {}
	if length(myarray)
		print(myarray)
	end
end

@test_suggestion 20 begin
	mystring = "Hello World!"
	if mystring[1:0]
		print(mystring)
	end
end

@test_suggestion 21 begin
	myarray = Number[]
	if myarray
		print(myarray)
	end
end

@test_suggestion 22 begin
	asdfgsdg = Float32[]
	push!(asdfgsdg, [3.14])
end

@test_suggestion 23 begin
	asdfgsdg = {}
	append!(asdfgsdg, 1)
end

@test_suggestion 24 begin
	myarray = Float32[1:1000]
	for i in 0:1000
		println(myarray[i])
	end
end

@test_suggestion 25 begin
	mystring = "Hello, I'm test #"
	mynumber = 25
	println(mystring * mynumber)
end

@test_suggestion 26 begin
	function jansdifnqwiljebf(asdfqwef::Array{Int})
		return asdfqwef
	end

	print(jansdifnqwiljebf(1:1000))
end

@test_suggestion 27 begin
	function asdgergawerg(dfqefqwfqwr, qfregqwregr=Dict())
		print(dfqefqwfqwr)
		dump(qfregqwregr)
	end

	asdgergawerg("Hello!", qfregqwregr=Dict())
end

@test_suggestion 28 begin
	aaefwregqre = 6.0
	egqrevqwefq = aaefwregqre::Int16
end

@test_suggestion 29 begin
	if string(:Hello) <: Symbol
		print("World!")
	end
end

@test_suggestion 30 begin
	ijansdvjiowneoijfnew(asdfwqe::Expr) = eval(asdfwqe)
	ijansdvjiowneoijfnew(:x)
end

@test_suggestion 31 begin
	ijansdvjiowneoijfnew(asdfwqe::Symbol) = Expr(asdfwqe)
	ijansdvjiowneoijfnew(:(-x))
end

### END TESTS ###

function idealdist()
	dist = 0.0
	for i in 1:length(indices)
		if indices[i] > 0
			info("Test #"*string(i)*": "*string(indices[i]))
			dist += (indices[i]-1)^2
		else
			info("Test #"*string(i)*": FAILED")
		end
	end

	return sqrt(dist)
end

const dist = idealdist()
info("Distance from ideal: "*string(dist))

const numfailed = length(filter(x->x==0, indices))
info("Failed $numfailed tests.")
@test numfailed == 0
# @testlint "Helpme.jl"
pwd()