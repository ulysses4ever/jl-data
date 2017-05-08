#!/usr/bin/julia

println("Time duration with macros")
println("-------------------------")
print("Enter expression <default sin(1.57)>:")

t = readline(STDIN)

if length(rstrip(t))==0
	ex = :( sin(1.57) )
else 
	ex = parse(t)
end

function f(ex) 
	time = @elapsed ex
	println("duration: ",time,"sec for ",ex," with result ",eval(ex))
	println()	
	println(macroexpand(:(@elapsed ex)))
end

f(ex)

##Example macros, note the different "quoting" styles
# macro assert(ex)
#    :($ex ? nothing : error("Assertion failed: ", $(string(ex))))
# end
#
# macro elapsed(ex)
#    quote
#        local t0 = time_ns()
#        local val = $(esc(ex))
#        (time_ns()-t0)/1e9
#    end
# end


# f(x)=2x+3x^3; f(4)



