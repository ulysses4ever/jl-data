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
			info(repr(e))
			info($(string(ex)))
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

@test in(1, @suggestion_id begin
	a = ["a"=>1]
	b = ["a"=>:a]
	merge(a, b)
end)

@test in(2, @suggestion_id begin
	a = "a"
	b = "b"
	a+b
end)

@test in(3, @suggestion_id begin
	dataset = {1, 2, 3, 4, 5}
	query = "12345"
	for m in eachmatch(r"\d", query)
		dataset[m]
	end
end)

@test in(4, @suggestion_id begin
	dataset = {"a"=>1, "b"=>2}
	query = "ab"
	for m in eachmatch(r"[a-z]", query)
		dataset[m]
	end
end)

@test in(5, @suggestion_id begin
	function alpha(a::Dict{ASCIIString, Number})
		a
	end

	alpha(["test"=>255])
end)

@test in(6, @suggestion_id begin
	eval(parse("for i in 1:12"))
end)

@test in(7, @suggestion_id begin
	eval(parse("for i in 1:12; identity(i); end; end"))
end)

@test in(8, @suggestion_id begin
	eval(parse("function Base.&&(a,b); a&&b; end"))
end)

@test in(9, @suggestion_id begin
	eval(parse("function Base.||(a,b); a||b; end"))
end)

@test in(10, @suggestion_id begin
	function jwngwoijenfoer(a::Array{Float32,8})
		a
	end
	
	jwngwoijenfoer(Float32[1:8])
end)

@test in(11, @suggestion_id begin
	eval(parse("function ooewjdbwoedjfvobwe(): nkjsndf=[1:8];end; ooewjdbwoedjfvobwe()"))
end)

@test in(12, @suggestion_id begin
	eval(parse("function ooewjdbwoedjfvobwe(): identity(9);end; ooewjdbwoedjfvobwe()"))
end)

@test in(13, @suggestion_id begin
	eval(parse("function ooewjdbwoedjfvobwe(): Base.identity(9);end; ooewjdbwoedjfvobwe()"))
end)

@test in(14, @suggestion_id begin
	oqwjej = {"sdfre"=>3, "jkndivnf"=>"grewerg", "sdfwerf"=>{}}
	for i in oqwjej
		"Hello, " * oqwjej
	end
end)

@test in(15, @suggestion_id begin
	function nuinkjnbk()
		import Base
	end

	nuinkjnbk()
end)