@testcase :DICT_MERGE begin
	mydict1 = ["asdfasdf"=>1]
	mydict2 = ["asdfasdf"=>:asdfasdf]
	merge(mydict1, mydict2)
end

@testcase :STR_CONCAT begin
	asdfasdf = "asdfasdf"
	qwerty = "qwerty"
	asdfasdf + qwerty
end

@testcase :REGEX_ITER begin
	dataset = {1, 2, 3, 4, 5}
	query = "12345"
	for m in eachmatch(r"\d", query)
		dataset[m]
	end
end

@testcase :REGEX_ITER begin
	dataset = {"a"=>1, "b"=>2}
	query = "ab"
	for m in eachmatch(r"[a-z]", query)
		dataset[m]
	end
end

@testcase :INVARIANTS begin
	function alpha(asdfwef::Dict{ASCIIString, Number})
		asdfwef
	end

	alpha(["test"=>255])
end

@testcase :NOT_PYTHON begin
	eval(parse("for i in 1:12"))
end

@testcase :NOT_PYTHON begin
	eval(parse("for i in 1:12; identity(i); end; end"))
end

@testcase :BASE_ANDOR begin
	eval(parse("function Base.&&(a,b); a&&b; end"))
end

@testcase :BASE_ANDOR begin
	eval(parse("function Base.||(a,b); a||b; end"))
end

@testcase :ARRAY_SIZE begin
	function jwngwoijenfoer(asdfwef::Array{Float32,8})
		asdfwef
	end
	
	jwngwoijenfoer(Float32[1:8])
end

@testcase :FUNC_COLON begin
	eval(parse("function ooewjdbwoedjfvobwe11(): nkjsndf=[1:8];end; ooewjdbwoedjfvobwe11()"))
end

@testcase :FUNC_COLON begin
	eval(parse("function ooewjdbwoedjfvobwe12(): identity(9);end; ooewjdbwoedjfvobwe12()"))
end

@testcase :FUNC_COLON begin
	eval(parse("function ooewjdbwoedjfvobwe13(): Base.identity(9);end; ooewjdbwoedjfvobwe13()"))
end

@testcase :DICTS_ITER begin
	oqwjej = {"sdfre"=>3, "jkndivnf"=>"grewerg", "sdfwerf"=>{}}
	for i in oqwjej
		"Hello, " * oqwjej
	end
end

@testcase :IMPORT_LVL begin
	function nuinkjnbk()
		import Base
	end

	nuinkjnbk()
end

@testcase :IS_DEFINED begin
	function nuinkjnbk()
		info("Hello World!")
	end

	isdefined(nuinkjnbk)
end

@testcase :IS_DEFINED begin
	function nuinkjnbk()
		info("Hello World!")
	end

	isdefined("nuinkjnbk")
end

@testcase :IS_DEFINED begin
	isdefined(nuinkjnbk)
end

@testcase :IF_BOOLEAN begin
	myarray = {}
	if length(myarray)
		print(myarray)
	end
end

@testcase :IF_BOOLEAN begin
	mystring = "Hello World!"
	if mystring[1:0]
		print(mystring)
	end
end

@testcase :IF_BOOLEAN begin
	myarray = Number[]
	if myarray
		print(myarray)
	end
end

@example :IF_BOOLEAN begin
	argaegfawerg = 4313
	nvijenvierng = 12342
	if argaegfawerg & nvijenvierng
	elseif argaegfawerg | nvijenvierng
	end
end

@example :IF_BOOLEAN begin
	myarrray = rand(-10:10, (4, 5, 6))
	if length(myarrray)
	end
end

@testcase :PUSHAPPEND begin
	asdfgsdg = Float32[]
	push!(asdfgsdg, [3.14])
end

@testcase :PUSHAPPEND begin
	asdfgsdg = {}
	append!(asdfgsdg, 1)
end

@testcase :INDEX_BASE begin
	myarray = Float32[1:1000]
	for i in 0:1000
		println(myarray[i])
	end
end

@testcase :STRCONVERT begin
	mystring = "Hello, I'm test #"
	mynumber = 25
	println(mystring * mynumber)
end

@testcase :RANGEARRAY begin
	function jansdifnqwiljebf(asdfqwef::Array{Int})
		return asdfqwef
	end

	print(jansdifnqwiljebf(1:1000))
end

@testcase :KEYWORDARG begin
	function asdgergawerg(dfqefqwfqwr, qfregqwregr=Dict())
		print(dfqefqwfqwr)
		dump(qfregqwregr)
	end

	asdgergawerg("Hello!", qfregqwregr=Dict())
end

@testcase :TYPEASSERT begin
	aaefwregqre = 6.0
	egqrevqwefq = aaefwregqre::Int16
end

@testcase :ISOPERATOR begin
	if string(:Hello) <: Symbol
		print("World!")
	end
end

@testcase :SYMBOLEXPR begin
	ijansdvjiowneoijfnew(asdfwqe::Expr) = eval(asdfwqe)
	ijansdvjiowneoijfnew(:x)
end

@testcase :SYMBOLEXPR begin
	ijansdvjiowneoijfnew(asdfwqe::Symbol) = Expr(asdfwqe)
	ijansdvjiowneoijfnew(:(-x))
end

@testcase :DOT_EQUALS begin
	eval(parse("myarray=Int[];mymatches.===234"))
end

@testcase :TYPE_PARAM begin
	eval(parse("function asdasdfqwef{T::Any}(x::T, y::T)x+y;end"))
end

@testcase :INDIRECTFN begin
	function sdfgerfqefwerg(i::Int, f::Number)
		print() = print(i, f)
		print()
	end
	sdfgerfqefwerg(5, 12.3)
end

@testcase :COLLECTSUM begin
	mydict = Dict{Int32,Int32}()
	v = values(mydict)
	sum(v)
end

@testcase :DIMS_MATCH begin
	myarrray = rand(-10:10, (4, 5, 6))
	myarrray[:,:,1] * (myarrray[:,:,1] * 0.5)
end

@example :BOOLASSIGN begin
	eval(parse("while myexamplefoobarvariable='this is a string';end"))
end

@example :MAKESTRING begin
	mystrrrrring = String("Hello, World!")
end

@example :MAKESYMBOL begin
	mysyyyyyymbol = Symbol(:FOOBAR)
end