suggbase[:DEFAULTMSG] = "Helpme not helping? Report an issue at <https://github.com/snotskie/Helpme.jl/issues>."

suggbase[:DICT_MERGE] = "Julia attempts to choose the proper type for Dicts when brackets[] "*
"are used, and functions like merge can be fussy when types don't match up. To force Julia to "*
"assign the type Dict{Any,Any}, use braces{}. More info at <http://bit.ly/1nUDhyc>."

suggbase[:STR_CONCAT] = "Strings are concatenated with the * operator, not the + operator. "*
"More info at <http://bit.ly/1rF5fBE>."

suggbase[:REGEX_ITER] = "When iterating over regex matches with functions like eachmatch, "*
"especially when using the matches as indices or keys, you might mean m.match "*
"where you have just m or m.captures. More info at <http://bit.ly/1nUDx0a>."

suggbase[:INVARIANTS] = "Type parameters in Julia are invariant, meaning although Int <: Number is true, "*
"Array{Int} <: Array{Number} is false. This can be annoying when defining functions. "*
"Instead of \"f(Array{Number})=...\" try \"f{T<:Number}(Array{T})=...\" More info at <http://bit.ly/1k2C3iY>."

suggbase[:NOT_PYTHON] = "Julia is not Python. All if, for, begin, function, etc. blocks must be "*
"completed with an end statement. Similarly, all end statements must have been \"opened\" "*
"with an if, for, etc. statement. Count your open and closes and make sure they match. More info at <http://bit.ly/1x0ENFE>."

suggbase[:BASE_ANDOR] = "Because && and || are logical operators with short-circuit behavior, "*
"it is not possible to override or access Base.&& and Base.||."

suggbase[:ARRAY_SIZE] = "The i in the expression \"Array{Int,i}\" is not the length of the array "*
"but instead the number of dimensions."

suggbase[:FUNC_COLON] = "Putting a colon in a function declaration, such as in \"function f():\", "*
"is grammatically correct, but it confuses the parser. Do not use colons in Julia like "*
"you do in Python to start blocks."

suggbase[:DICTS_ITER] = "Iteration over dictionaries in Julia is iteration over (key, value), "*
"not just over key or over value like in other languages. Use expressions like "*
"\"for (k,v) in mydict\" where possible to avoid confusion."

suggbase[:IMPORT_LVL] = "Keywords like using, import, and export can only appear at "*
"global-level scopes. They can't even show up in a quote block in a macro "*
"definition. An ugly workaround, if you absolutely cannot avoid it, is to use "*
"expressions like eval(parse(\"import ...\") instead."

suggbase[:IS_DEFINED] = "Methods like isdefined take Symbols as parameters, not strings or "*
"functions. To check if x is defined, use \"isdefined(:x),\" where :x is the Symbol "*
"for x."

suggbase[:IF_BOOLEAN] = "If blocks and ternary operations in Julia require Boolean types, like Java, "*
"not JavaScript."

suggbase[:PUSHAPPEND] = "The append! function appends arrays together, so the second argument needs "*
"to be iterable, whereas the push! function pushes a single value into an array, so the "*
"second argument can be any type supported by the array."

suggbase[:INDEX_BASE] = "Julia has 1-based indexing, so the first element is at index 1, not index 0. "*
"Also, index -1 throws an error; use the end keyword as an index to get the last element."

suggbase[:STRCONVERT] = "Values are not automatically converted to strings during string concatenation. "*
"Convert them first using the \"string\" function. More info at <http://bit.ly/1rF5fBE>."

suggbase[:RANGEARRAY] = "The a:b syntax creates a Range object. Surround in brackets like [a:b] to "*
"create an Array. More info at <http://bit.ly/1lTfcdT>."

suggbase[:KEYWORDARG] = "Julia distinguishes between keyword and optional arguments. For a function "*
"f(x, y=1; z=2), x is required, y is optional, and z is a keyword. Invoking f(1, z=3) "*
"is legal, but not f(1, y=2, z=3). Note the position of the semi-colon. More info at <http://bit.ly/UNNRQr>."

suggbase[:TYPEASSERT] = "The value::Type syntax is Julia has multiple meanings. It is used in argument lists "*
"and variable definitions to declare type. It is used everywhere else as a type assertion. "*
"Perhaps you mean to use the \"isa\" function, the \"convert\" function, or a constructor. "*
"If not, it's best to write your code so it operates on a wider range of types. More info at <http://bit.ly/1jSlkz0>."

suggbase[:ISOPERATOR] = "The <: operator operates on two types, not a value and a type. The \"isa\" function "*
"takes a value and a type. More info at <http://bit.ly/1po1fsf>."

suggbase[:SYMBOLEXPR] = "The simpler :(x) syntax returns a Symbol, whereas the more complex :(x+y), "*
"etc. syntax returns an Expr. More info at <http://bit.ly/1pFoycM>."

suggbase[:DOT_EQUALS] = "The .=== operator does not exist. Use .== or a comprehension instead. "*
"More info at <http://bit.ly/TCB3vk>."

suggbase[:TYPE_PARAM] = "The X in \"function myfunction{X}()\" does not declare the return type "*
"of the function. This syntax is used to declare parametric types. More info at <http://bit.ly/1mAsPPT>."

suggbase[:INDIRECTFN] = "To extend a generic function within another function, you must "*
"either declare it global or use the fully qualified name. More info at <http://bit.ly/1yZOHJE>."