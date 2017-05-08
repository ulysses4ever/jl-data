@example("Keywords like using, import, and export can only appear at "*
"global-level scopes. They can't even show up in a quote block in a macro "*
"definition. An ugly workaround, if you absolutely cannot avoid it, is to use "*
"expressions like eval(parse(\"import ...\") instead.") do
	function ex()
		import Base
	end

	ex()
end

@example("Julia attempts to choose the proper type for Dicts when [brackets] "*
"are used, and merge can be fussy when types don't match up. To force Julia to "*
"assign the type Dict{Any,Any}, use {braces} in your variable definitions for "*
"Dicts.") do
	merge(["key"=>"value"], ["key"=>12345])
end

@example("Strings are concatenated with the * operator, not the + operator.") do
	"foo" + "bar"
end