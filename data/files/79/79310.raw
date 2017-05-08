# 1
@example("Julia attempts to choose the proper type for Dicts when [brackets] "*
"are used, and merge can be fussy when types don't match up. To force Julia to "*
"assign the type Dict{Any,Any}, use {braces} in your variable definitions for "*
"Dicts.") do
	merge(["l"=>"l"],["l"=>6])
end

# 2
@example("Strings are concatenated with the * operator, not the + operator.") do
	"l"+"l"
end

# 3
@example("When iterating over regex matches with functions like eachmatch, "*
"especially when using the matches as indices or keys, you might mean m.match "*
"where you have just m or m.captures.") do
	l = [6:6]
	for i in eachmatch(r"\d","6")
		l[i]
	end
end

# 4
@example("When iterating over regex matches with functions like eachmatch, "*
"especially when using the matches as indices or keys, you might mean m.match "*
"where you have just m or m.captures.") do
	l = {"l"=>"l"}
	for i in eachmatch(r"[a-z]", "l")
		l[i]
	end
end

# 5
@example("Type parameters in Julia are invariant, meaning although Int <: Number is true, "*
"Array{Int} <: Array{Number} is false. This can be annoying when defining functions. "*
"Instead of \"f(Array{Number})=...\" try \"f{T<:Number}(Array{T})=...\"") do
	function l(::Array{Number,1})
	end
	l([6])
end

# 6
@example("Julia is not Python. All if, for, begin, function, etc. blocks must be "*
"completed with an end statement. Similarly, all end statements must have been \"opened\" "*
"with an if, for, etc. statement. Count your open and closes and make sure they match.") do
	eval(parse("if true"))
end

# 7
@example("Julia is not Python. All if, for, begin, function, etc. blocks must be "*
"completed with an end statement. Similarly, all end statements must have been \"opened\" "*
"with an if, for, etc. statement. Count your open and closes and make sure they match.") do
	eval(parse("end"))
end

# 8
@example("Because && and || are logical operators with short-circuit behavior, "*
"it is not possible to override or access Base.&& and Base.||.") do
	eval(parse("Base.&&"))
end

# 9
@example("Because && and || are logical operators with short-circuit behavior, "*
"it is not possible to override or access Base.&& and Base.||.") do
	eval(parse("Base.||"))
end

# 10
@example("The i in the expression \"Array{Int,i}\" is not the length of the array "*
"but instead the number of dimensions.") do
	function l(::Array{Number,6})
	end
	l(Number[6])
end

# 11
@example("Putting a colon in a function declaration, such as in \"function f():\", "*
"is grammatically correct, but it confuses the parser. Do not use colons in Julia like "*
"you do in Python to start blocks.") do
	eval(parse("function l(): a = 6;end;l()"))
end

# 12
@example("Putting a colon in a function declaration, such as in \"function f():\", "*
"is grammatically correct, but it confuses the parser. Do not use colons in Julia like "*
"you do in Python to start blocks.") do
	eval(parse("function l(): print();end;l()"))
end

# 13
@example("Putting a colon in a function declaration, such as in \"function f():\", "*
"is grammatically correct, but it confuses the parser. Do not use colons in Julia like "*
"you do in Python to start blocks.") do
	eval(parse("function l(): Base.print();end;l()"))
end

# 14
@example("Iteration over dictionaries in Julia is iteration over (key, value), "*
"not just over key or over value like in other languages. Use expressions like "*
"\"for (k,v) in mydict\" where possible to avoid confusion.") do
	for l in {"l"=>6}
		l+6
	end
end

# 15
@example("Keywords like using, import, and export can only appear at "*
"global-level scopes. They can't even show up in a quote block in a macro "*
"definition. An ugly workaround, if you absolutely cannot avoid it, is to use "*
"expressions like eval(parse(\"import ...\") instead.") do
	function l()
		import Base
	end
	l()
end

# 16
@example("Methods like isdefined take Symbols as parameters, not strings or "*
"functions. To check if x is defined, use \"isdefined(:x),\" where :x is the Symbol "*
"for x.") do
	isdefined(isdefined)
end

# 17
@example("Methods like isdefined take Symbols as parameters, not strings or "*
"functions. To check if x is defined, use \"isdefined(:x),\" where :x is the Symbol "*
"for x.") do
	isdefined("l")
end

# 18
@example("Methods like isdefined take Symbols as parameters, not strings or "*
"functions. To check if x is defined, use \"isdefined(:x),\" where :x is the Symbol "*
"for x.") do
	isdefined(l)
end

# 19
@example("If blocks and ternary operations in Julia require Boolean types, like Java, "*
"not JavaScript.") do
	if 6?6:6
	end
end

# 20
@example("If blocks and ternary operations in Julia require Boolean types, like Java, "*
"not JavaScript.") do
	if ""?"":""
	end
end

# 21
@example("If blocks and ternary operations in Julia require Boolean types, like Java, "*
"not JavaScript.") do
	if []?[]:[]
	end
end

# 22
@example("The append! function appends arrays together, so the second argument needs "*
"to be iterable, whereas the push! function pushes a single value into an array, so the "*
"second argument can be any type supported by the array.") do
	l = Int[]
	push!(l,[6])
end

# 23
@example("The append! function appends arrays together, so the second argument needs "*
"to be iterable, whereas the push! function pushes a single value into an array, so the "*
"second argument can be any type supported by the array.") do
	l = Int[]
	append!(l,6)
end

# 24
@example("Julia has 1-based indexing, so the first element is at index 1, not index 0. "*
"Also, index -1 throws an error; use the end keyword as an index to get the last element.") do
	[][0]
end

# 25
@example("Values are not automatically converted to strings during string concatenation. "*
"Convert them first using the \"string\" function.") do
	"l"*6
end

# 26
@example("The a:b syntax creates a Range object. Surround in brackets like [a:b] to "*
"create an Array.") do
	function l(::Array)
	end
	l(6:6)
end

# 27
@example("Julia distinguishes between keyword and optional arguments. For a function "*
"f(x, y=1; z=2), x is required, y is optional, and z is a keyword. Invoking f(1, z=3) "*
"is legal, but f(1, y=2, z=3) is not. Note the position of the semi-colon in the function "*
"definition.") do
	function l(q,w=6;e=6)
	end
	l(6,w=6)
end

# 28
@example("The value::Type syntax is Julia has multiple meanings. It is used in argument lists "*
"and variable definitions to declare type. It is used everywhere else as a type assertion. "*
"Perhaps you mean to use the \"isa\" function, the \"convert\" function, or a constructor. "*
"If not, it's best to write your code so it operates on a wider range of types.") do
	6::String
end

# 29
@example("The <: operator operates on two types, not a value and a type. The \"isa\" function "*
"takes a value and a type.") do
	6<:String
end

# 30
@example("The simpler :(x) syntax returns a Symbol, whereas the more complex :(x+y), "*
"etc. syntax returns an Expr.") do
	function l(::Expr)
	end
	l(:(6))
end

# 31
@example("The simpler :(x) syntax returns a Symbol, whereas the more complex :(x+y), "*
"etc. syntax returns an Expr.") do
	function l(::Symbol)
	end
	l(:(6+6))
end