# 1
@example(:DICT_MERGE) do
	merge(["l"=>"l"],["l"=>6])
end

# 2
@example(:STR_CONCAT) do
	"l"+"l"
end

# 3
@example(:REGEX_ITER) do
	l = [6:6]
	for i in eachmatch(r"\d","6")
		l[i]
	end
end

# 4
@example(:REGEX_ITER) do
	l = {"l"=>"l"}
	for i in eachmatch(r"[a-z]", "l")
		l[i]
	end
end

# 5
@example(:INVARIANTS) do
	function l(::Array{Number,1})
	end
	l([6])
end

# 6
@example(:NOT_PYTHON) do
	eval(parse("if true"))
end

# 7
@example(:NOT_PYTHON) do
	eval(parse("end"))
end

# 8
@example(:BASE_ANDOR) do
	eval(parse("Base.&&"))
end

# 9
@example(:BASE_ANDOR) do
	eval(parse("Base.||"))
end

# 10
@example(:ARRAY_SIZE) do
	function l(::Array{Number,6})
	end
	l(Number[6])
end

# 11
@example(:FUNC_COLON) do
	eval(parse("function l(): a = 6;end;l()"))
end

# 12
@example(:FUNC_COLON) do
	eval(parse("function l(): print();end;l()"))
end

# 13
@example(:FUNC_COLON) do
	eval(parse("function l(): Base.print();end;l()"))
end

# 14
@example(:DICTS_ITER) do
	for l in {"l"=>6}
		l+6
	end
end

# 15
@example(:IMPORT_LVL) do
	function l()
		import Base
	end
	l()
end

# 16
@example(:IS_DEFINED) do
	isdefined(isdefined)
end

# 17
@example(:IS_DEFINED) do
	isdefined("l")
end

# 18
@example(:IS_DEFINED) do
	isdefined(ll) # turns out just isdefined(l) was seeing the previous definition of function l above
end

# 19
@example(:IF_BOOLEAN) do
	if 6?6:6
	end
end

# 20
@example(:IF_BOOLEAN) do
	if ""?"":""
	end
end

# 21
@example(:IF_BOOLEAN) do
	if []?[]:[]
	end
end

# 22
@example(:PUSHAPPEND) do
	l = Int[]
	push!(l,[6])
end

# 23
@example(:PUSHAPPEND) do
	l = Int[]
	append!(l,6)
end

# 24
@example(:INDEX_BASE) do
	[][0]
end

# 25
@example(:STRCONVERT) do
	"l"*6
end

# 26
@example(:RANGEARRAY) do
	function l(::Array)
	end
	l(6:6)
end

# 27
@example(:KEYWORDARG) do
	function l(q,w=6;e=6)
	end
	l(6,w=6)
end

# 28
@example(:TYPEASSERT) do
	6::String
end

# 29
@example(:ISOPERATOR) do
	6<:String
end

# 30
@example(:SYMBOLEXPR) do
	function l(::Expr)
	end
	l(:(6))
end

# 31
@example(:SYMBOLEXPR) do
	function l(::Symbol)
	end
	l(:(6+6))
end

# 32
@example(:DOT_EQUALS) do
	eval(parse("[].===6"))
end