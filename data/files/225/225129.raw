# VERSION >= v"0.4.0-dev+6521" && __precompile__(true)
module Script

export _nullFunction
export _debug
export compile
export invoke

global const _nullFunction = function() end
global _debug = true

function compile(file::String)
	result = nothing
	try
		result = evalfile(file)
		if _debug == true
			println("file compiled.")
		end
	catch err
		println("Cannot compile file. There was an error: ", err)
	end
	return result
end

function invoke(f::Function, args...)
	result = nothing
	try
		if f == _nullFunction
			error("function is null")
		end
		result = f(args...)
		if _debug == true
			println("function invoked. result: ", result)
		end
	catch err
		println("Cannot invoke function. There was an error: ", err)
	end
	return result
end

end # module
