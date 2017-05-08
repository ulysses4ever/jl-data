using Helpme
using Base.Test

# A series of tests corresponding with the examples in examples.jl

keybase = Helpme.keybase

macro suggestion_id(ex)
	global keybase
	quote
		z = 0
		try
			$(esc(ex))()
			error("Example did not fail.")
		catch e
			id, msg = Helpme.search(e, $(string(ex)))
			for i in 1:length(keybase)
				k = keybase[i]
				if id == k
					println((e, $(string(ex))))
					println(id)
					z = i
				end
			end

			z
		end
	end
end

function test1()
	a = ["a"=>1]
	b = ["a"=>:a]
	merge(a, b)
end

function test2()
	a = "a"
	b = "b"
	a+b
end

function test3()
	dataset = {1, 2, 3, 4, 5}
	query = "12345"
	for m in eachmatch(r"\d", query)
		dataset[m]
	end
end

function test4()
	dataset = {"a"=>1, "b"=>2}
	query = "ab"
	for m in eachmatch(r"[a-z]", query)
		dataset[m]
	end
end

function test5()
	eval(parse("function alpha(a::Dict{ASCIIString, Number});a;end;alpha([\"test\"=>255])"))
end

function test6()
	eval(parse("for i in 1:12"))
end

function test7()
	eval(parse("for i in 1:12; identity(i); end; end"))
end

function test8()
	eval(parse("function Base.&&(a,b); a&&b; end"))
end

function test9()
	eval(parse("function Base.||(a,b); a||b; end"))
end

tests = [test1, test2, test3, test4, test5, test6, test7, test8, test9]

for i in 1:length(tests)
	j = @suggestion_id() do
		tests[i]()
	end

	info("$i == $j")
	@test i == j
end