include("derivative.jl")

function quadratic(f)
	f1 = derivative(f)

	c = f(0.0)
	b = f1(0.0)
	a = f(1.0) - b - c

	return (-b + sqrt(b^2 - 4*a*c + 0im)) / (2*a), (-b - sqrt(b^2 - 4*a*c + 0im)) / (2*a)
end