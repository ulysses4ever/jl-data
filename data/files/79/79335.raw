@example :DICT_MERGE begin
	merge(["l"=>"l"],["l"=>6])
end

@example :STR_CONCAT begin
	"l"+"l"
end

@example :REGEX_ITER begin
	l = [6:6]
	for i in eachmatch(r"\d","6")
		l[i]
	end
end

@example :REGEX_ITER begin
	l = {"l"=>"l"}
	for i in eachmatch(r"[a-z]", "l")
		l[i]
	end
end

@example :INVARIANTS begin
	function l(::Array{Number,1});end
	l([6])
end

@example :NOT_PYTHON begin
	eval(parse("if true"))
end

@example :NOT_PYTHON begin
	eval(parse("end"))
end

@example :BASE_ANDOR begin
	eval(parse("Base.&&"))
end

@example :BASE_ANDOR begin
	eval(parse("Base.||"))
end

@example :ARRAY_SIZE begin
	function l(::Array{Number,6});end
	l(Number[6])
end

@example :FUNC_COLON begin
	eval(parse("function f11(): a = 6;end;f11()"))
end

@example :FUNC_COLON begin
	eval(parse("function f12(): print();end;f12()"))
end

@example :FUNC_COLON begin
	eval(parse("function f13(): Base.print();end;f13()"))
end

@example :DICTS_ITER begin
	for l in {"l"=>6}
		l+6
	end
end

@example :IMPORT_LVL begin
	function l();import Base;end
	l()
end

@example :IS_DEFINED begin
	isdefined(isdefined)
end

@example :IS_DEFINED begin
	isdefined("l")
end

@example :IS_DEFINED begin
	isdefined(l)
end

@example :IF_BOOLEAN begin
	if 6?6:6
	end
end

@example :IF_BOOLEAN begin
	if ""?"":""
	end
end

@example :IF_BOOLEAN begin
	if []?[]:[]
	end
end

@example :IF_BOOLEAN begin
	if 1 & 2 | 3
	end
end

@example :IF_BOOLEAN begin
	if length([])
	end
end

@example :PUSHAPPEND begin
	l = Int[]
	push!(l,[6])
end

@example :PUSHAPPEND begin
	l = Int[]
	append!(l,6)
end

@example :INDEX_BASE begin
	[][0]
end

@example :STRCONVERT begin
	"l"*6
end

@example :RANGEARRAY begin
	function l(::Array);end
	l(6:6)
end

@example :KEYWORDARG begin
	function l(q,w=6;e=6);end
	l(6,w=6)
end

@example :TYPEASSERT begin
	6::String
end

@example :ISOPERATOR begin
	6<:String
end

@example :SYMBOLEXPR begin
	function l(::Expr);end
	l(:(6))
end

@example :SYMBOLEXPR begin
	function l(::Symbol);end
	l(:(6+6))
end

@example :DOT_EQUALS begin
	eval(parse("[].===6"))
end

@example :TYPE_PARAM begin
	eval(parse("function f33{::Any}();end"))
end

@example :INDIRECTFN begin
	function l(::Any);end
	function li(a::Any)
		l() = l(a)
		l()
	end
	li(6)
end

@example :COLLECTSUM begin
	sum(values(Dict()))
end

@example :DIMS_MATCH begin
	ones((4,5)) * ones((4,5))
end

@example :BOOLASSIGN begin
	eval(parse("if a=0;end"))
end

@example :MAKESTRING begin
	String()
end

@example :MAKESYMBOL begin
	Symbol()
end