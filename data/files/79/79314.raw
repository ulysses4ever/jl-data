# 1
@example :DICT_MERGE begin
	merge(["l"=>"l"],["l"=>6])
end

# 2
@example :STR_CONCAT begin
	"l"+"l"
end

# 3
@example :REGEX_ITER begin
	l = [6:6]
	for i in eachmatch(r"\d","6")
		l[i]
	end
end

# 4
@example :REGEX_ITER begin
	l = {"l"=>"l"}
	for i in eachmatch(r"[a-z]", "l")
		l[i]
	end
end

# 5
@example :INVARIANTS begin
	function l(::Array{Number,1});end
	l([6])
end

# 6
@example :NOT_PYTHON begin
	eval(parse("if true"))

end

# 7
@example :NOT_PYTHON begin
	eval(parse("end"))
end

# 8
@example :BASE_ANDOR begin
	eval(parse("Base.&&"))
end

# 9
@example :BASE_ANDOR begin
	eval(parse("Base.||"))
end

# 10
@example :ARRAY_SIZE begin
	function l(::Array{Number,6});end
	l(Number[6])
end

# 11
@example :FUNC_COLON begin
	eval(parse("function f11(): a = 6;end;f11()"))
end

# 12
@example :FUNC_COLON begin
	eval(parse("function f12(): print();end;f12()"))
end

# 13
@example :FUNC_COLON begin
	eval(parse("function f13(): Base.print();end;f13()"))
end

# 14
@example :DICTS_ITER begin
	for l in {"l"=>6}
		l+6
	end
end

# 15
@example :IMPORT_LVL begin
	function l();import Base;end
	l()
end

# 16
@example :IS_DEFINED begin
	isdefined(isdefined)
end

# 17
@example :IS_DEFINED begin
	isdefined("l")
end

# 18
@example :IS_DEFINED begin
	isdefined(l)
end

# 19
@example :IF_BOOLEAN begin
	if 6?6:6
	end
end

# 20
@example :IF_BOOLEAN begin
	if ""?"":""
	end
end

# 21
@example :IF_BOOLEAN begin
	if []?[]:[]
	end
end

# 22
@example :PUSHAPPEND begin
	l = Int[]
	push!(l,[6])
end

# 23
@example :PUSHAPPEND begin
	l = Int[]
	append!(l,6)
end

# 24
@example :INDEX_BASE begin
	[][0]
end

# 25
@example :STRCONVERT begin
	"l"*6
end

# 26
@example :RANGEARRAY begin
	function l(::Array);end
	l(6:6)
end

# 27
@example :KEYWORDARG begin
	function l(q,w=6;e=6);end
	l(6,w=6)
end

# 28
@example :TYPEASSERT begin
	6::String
end

# 29
@example :ISOPERATOR begin
	6<:String
end

# 30
@example :SYMBOLEXPR begin
	function l(::Expr);end
	l(:(6))
end

# 31
@example :SYMBOLEXPR begin
	function l(::Symbol);end
	l(:(6+6))
end

# 32
@example :DOT_EQUALS begin
	eval(parse("[].===6"))
end