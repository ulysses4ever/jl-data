module Quadrature
using RandomNumbers

# Functions we will integrate
f1(x) = (1.0 / sqrt(2 * pi)) * exp((-x^2.0) / 2.0)
f1lim = (0.0, 1.0)

f2(x) = ((sin(2.0 * x))^2.0)/(x^2.0)
f2lim = (pi, 2 * pi)

f3(x) = x^(-.5)
f3lim = (0.0, 2.0)

# Change of variable for f1 -> Inf
f4(x) = f1(-log(x)) / x
f4lim = (0.0, e^-f1lim[1])

# Infinite limits of integration for printing
f1inflim = (0.0, Inf)

# PDF of the normal distribution
function normpdf(x, mu=0, sigma=1)
	return (sigma * sqrt(2 * pi))^-1.0 * e^(-(x - mu)^2 / (2 * sigma^2))
end

# Limits to integrate normpdf over
normlim = (-50.0, 50.0)

# PDF of the Cauchy distribution
cauchypdf(x) = (pi * (1.0 + x^2.0))^-1.0

# PDF of the t-distribution
function tpdf(x, dof)
	term1 = gamma(.5 * (dof + 1.0)) / (sqrt(dof * pi) * gamma(dof / 2.0))
	term2 = (1.0 + (x^2.0)/dof)^(-.5*(dof+1.0))
	return term1 * term2
end

# Generate a single random t variable
function rn_t(dof)
	z = rn_standard_normal()
	v = rn_chi_sq(dof)
	return z / sqrt(v / dof)
end

# Utility function to print each entry in an array on its own line
mapln(x) = map(println, x)

# Utility function to truncate
function truncate(x::Float64, minvalue::Float64, maxvalue::Float64)
	if x > maxvalue
		return maxvalue
	elseif x < minvalue
		return minvalue
	else
		return x
	end
end

# Truncated Cauchy
rn_trunc_cauchy(a, b) = truncate(rn_standard_cauchy(), a, b)
rn_trunc_cauchy(a, b, n) = [rn_trunc_cauchy(a, b) for x in 1:n]

# Truncated t
rn_trunc_t(dof, a, b) = truncate(rn_t(dof), a, b)
rn_trunc_t(dof, a, b, n) = [rn_trunc_t(dof, a, b) for x in 1:n]

# Extended trapezoidal rule
function exttrap(f, a, b; nmax=20, epsilon=1e-6)
	# Initialize I
	n = 2
	I = [(b - a) * .5 * ( f(a) + f(b))]

	while n < nmax
		# Determine new points to evaluate at
		irange = 1:2^(n-2)
		evalpoints = map(x -> (a + (2*x - 1) * (b - a) / (2^(n -1))), irange)

		# Sum function evals at new points
		sumterm = sum(map(f, evalpoints))

		# Add new I onto results vector
		push!(I, .5 * I[n-1] + (sumterm * (b - a) / (2^(n-1))))

		# Check for convergence
		if abs(I[n] - I[n-1]) <= epsilon * abs(I[n-1])
			return I
		end

		n += 1
	end

	return I
end

# Romberg integration
function romberg(f, a, b; nmax=20, epsilon=1e-6)
	# Get the results of the trapezoidal rule
	traps = exttrap(f, a, b, nmax=nmax, epsilon=epsilon)

	# Find a size for our results
	resultsize = min(nmax, length(traps))

	# Create a zero matrix and assign traps to the first column
	r = zeros(Float64, (resultsize, resultsize))
	r[:, 1] = traps[1:resultsize]

	# For each row past the first
	for i in 2:resultsize
		# For each column past the first
		for j in 2:i
			r[i,j] = (1 / (4^(j - 1) - 1)) * (4^(j-1) * r[i,j-1] - r[i-1,j-1])
		end

		# Check stopping criteria
		if abs(r[i,i] - r[i,i-1]) <= epsilon * abs(r[i,i-1])
			return r[1:i,1:i]
		end
	end
end

# Extended midpoint rule
function midpoint(f, a, b; nmax=20, epsilon=1e-6)
	# Initialize I
	n = 2
	I = [f(.5 * (a + b))]

	while n < nmax
		# Determine new points to evaluate at:
		# Keep odd numbers from 1:2*3^(n-1) that aren't divisible by 3
		newodds = filter(x -> x % 3 != 0, [1:2:2*3^(n-1)])

		# Divide by (2*3^(n-1)) and scale to (a,b)
		newpoints = a + (b - a) * newodds / (2*3^(n - 1))

		# Sum function evals at this point
		sumterm = sum(map(f, newpoints))
		
		# Add new I onto results vector
		push!(I, I[n-1] / 3.0 + sumterm * (b - a) / 3.0^(n-1))

		# Check for convergence
		if abs(I[n] - I[n-1]) <= epsilon * abs(I[n-1])
			return I
		end

		n += 1
	end

	return I
end

# Monte Carlo Integration with antithetic variables
function mci(f, a, b; nmax=1e4, epsilon=1e-6)

	# Store our random variables in a vector
	x = [rn_unif(a, b)]

	# Calculate our initial result
	I = [(b - a) * .5 * (f(x[1]) + f(a + b - x[1]))]

	# Initialize n
	n = 2
	while n < nmax
		# Generate a new random variable and add it to the vector
		push!(x, rn_unif(a, b))

		# Calculate new result and push it onto the results vector
		push!(I, (b - a) * .5 * mean(map(f, x) + map(f, a + b - x)))

		# Check for convergence
		if abs(I[n] - I[n-1]) <= epsilon * abs(I[n-1])
			return I
		end

		n += 1
	end

	return I
end

# Monte Carlo Integration with Importance Sampling (Uniform)
function mciunif(f, a, b; n=1000)
	# Store our random variables in a vector
	x = rn_unif(a, b, n)

	# Calculate our estimate
	I = (b - a) * mean(map(f, x))

	return I
end

# Monte Carlo Integration with Importance Sampling (Truncated Standard Cauchy)
function mcicauchy(f, a, b; n=1000)
	# Store our random variables in a vector
	x = rn_trunc_cauchy(a, b, n)

	# Calculate our estimate
	I = mean(map(f, x) ./ map(cauchypdf, x))

	return I
end

# Monte Carlo Integration with Importance Sampling (Truncated t-distribution)
function mcit(f, a, b; n=1000)
	# Use 30 degrees of freedom - in the future this might be worth parameterizing
	dof = 30

	# Store our random variables in a vector
	x = rn_trunc_t(dof, a, b, n)

	# Calculate our estimate
	I = mean(map(f, x) ./ map(x -> tpdf(x, dof), x))

	return I
end

# Run integration function f n times and write final results to a csv file
function mcincsv(f, n, filename)
	println("Writing $n runs to $filename")
	results = [f(x) for x in 1:n]
	writecsv(filename, results)
end

end