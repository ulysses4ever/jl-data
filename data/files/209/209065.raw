module Jester

using Dates

export test
export assert

testcounter = 0
failedcounter = 0

type TestException <: Exception 
	message::ASCIIString
end

function test(testSubject::Function)
	test(testSubject, "test " * string(testcounter + 1))
end

function assert(result::Bool)
	if !result
		throw(TestException("assert was false"))
	end
end

function assert(result::Bool, message::ASCIIString)
	if !result
		throw(TestException(message))
	end
end

function test(testSubject::Function, description::ASCIIString)
	print(description * " ")

	passed = true
	errorMessage = ""

	x1 = now()
	try
		testSubject()
	catch error
		passed = false
		global failedcounter += 1

		if isa(error, TestException)
			errorMessage = error.message
		else
			errorMessage = string(error);
		end

	end
	x2 = now()

	if passed
		println(" [\033[32mPASS\033[39m] ($(x2 - x1))")
	else
		println(" [\033[31mFAIL\033[39m]")
		println("\033[31m" * errorMessage * "\033[39m")
	end

	global testcounter += 1
end


atexit() do 
	println("$(testcounter - failedcounter) / $(testcounter) tests pass")
end

end #module