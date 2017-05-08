#julia by example
println("hello world")
# if I were to call this from the command line
# julia hello_world.jl
# include("helloworld.jl") will evaluate and return last output

# functions
# calculate volume of sphere
function sphere_vol(r)
	#allowed unicode names
	return 4/3*pi*r^3
end

# or a more compact function definition
quadratic(a, sqr_term, b) = (-b + sqr_term) / 2a

function quadratic2(a::Float64, b::Float64, c::Float64)
	# 2a is the same as 2*a
	sqr_term = sqrt(b^2-4a*c)
	r1 = quadratic(a, sqr_term, b)
	r2 = quadratic(a, -sqr_term, b)
	# a tuple of values can be returned
	# if return is ommitted, the last term is required
	r1, r2
end

#printing
vol = sphere_vol(3)
@printf "volume = %0.3f\n" vol

quad1, quad2 = quadratic2(2.0, -2.0, -12.0)
println("result 1: ", quad1)
println("result 2: ", quad2)

#strings
#define with double quotes
s1 = "The quick brown fox jumps over the lazy dog"
println(s1) #adds new line
print(s1) # does not add new line

#chars in single quotes
c1 = 'a'
println(c1)

# ascii value of a char with int()
println(c1, " ascii value = ", int(c1))
#therefore be aware!!!!!
println(int('2') == 2) #returns false!

#strings converted to upper case
s1_caps = uppercase(s1)
s2_lower = lowercase(s1)

#sub strings are indexed like arrays
show(s1[11])
show(s1[1:10]) 

# use the end for the end of the array or string
show(s1[end-10:end])

# string interpolation
a = "welcome"
b = "to Julia"
println("$a to $b")

# you can use this to evaluate statements:
println("1 + 2 = $(1 + 2)")

#concatenate strings with the * operator
# NOT USING THE + operator
s2 = "this" * " and" * " that" 
println(s2)

# use the string function
s3 = string("this", " and", " that")


