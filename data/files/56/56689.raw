module RandomNumbers
# Note:
# Unless mentioned otherwise, the single variable continuous functions return
# Float64 and the multiple variable continuous functions return Array{Float64, 1}.
# Similarly, the single variable discrete functions return Int64 and the multiple
# variable discrete functions return Array{Int64, 1}.
export rn_unif, rn_exp, rn_standard_cauchy, rn_standard_normal, rn_normal,
	   rn_chi_sq, rn_bernoulli, rn_binom, rn_geo, rn_gamma, rn_beta

# Generate a single uniform random variable between a and b.
function rn_unif(a, b)
	return a + rand() * (b - a)
end

# Generate n random uniform variables between a and b.
function rn_unif(a, b, n::Int64)
	return [rn_unif(a,b) for x in 1:n]
end

# Generate a single exponential random variable with rate parameter theta.
function rn_exp(theta)
	# Don't allow negative theta values.
	if theta <= 0.0
		throw(ArgumentError("Theta cannot be less than zero."))
	end

	return -log(rn_unif(0, 1)) / theta
end

# Generate n exponential random variables with rate parameter theta.
function rn_exp(theta, n::Int64)
	return [rn_exp(theta) for x in 1:n]
end

# Generate a single standard Cauchy random variable.
function rn_standard_cauchy()
	return tan(pi * (rn_unif(0, 1) - .5))
end

# Generate n standard Cauchy random variables.
function rn_standard_cauchy(n::Int64)
	return [rn_standard_cauchy() for x in 1:n]
end

# Generate a single standard normal random variable.
function rn_standard_normal()
	u1 = rand()
	u2 = rand()

	return sqrt(-2 * log(u1)) * cos(2 * pi * u2)
end

# Generate n standard normal random variables.
function rn_standard_normal(n::Int64)
	return [rn_standard_normal() for x in 1:n]
end

# Generate a single normal random variable with mean mu and
# standard deviation sigma.
function rn_normal(mu, sigma)
	# Don't allow negative sigma.
	if sigma <= 0.0
		throw(ArgumentError("Standard deviation cannot be negative."))
	end

	return (sigma * rn_standard_normal()) + mu
end

# Generate n normal random variables with mean mu and standard deviation sigma.
function rn_normal(mu, sigma, n::Int64)
	return [rn_normal(mu, sigma) for x in 1:n]
end

# Generate a single chi-square random normal variable with k degrees of freedom.
# Is specifying Integer in argument necessary?
function rn_chi_sq(k::Integer)
	# Only accept positive natural numbers as input.
	if k < 1
		throw(ArgumentError("Degrees of freedom must be at least 1."))
	end

	# Generate k squared random normal variables.
	normals = rn_standard_normal(k).^2

	# Return the sum of the squared random normal variables.
	return sum(normals)
end

# Generate n chi-square random normal variables with k degrees of freedom.
function rn_chi_sq(k::Integer, n::Int64)
	return [rn_chi_sq(k) for x in 1:n]
end

# Generate a single Bernoulli random variable with success probability
# p as an Int64.
function rn_bernoulli(p)
	# Only allow success probabilities in between 0 and 1.
	if !(0 < p < 1)
		throw(ArgumentError("Success probability must be between 0 and 1."))
	end

	# Generate a single uniform random variable.
	unif = rn_unif(0, 1)

	# Return whether the random variable is below p.
	return unif < p ? 1 : 0
end

# Generate n Bernoulli random variables with success probability p as
# an Array{Int64, 1}.
function rn_bernoulli(p, n::Int64)
	return [rn_bernoulli(p) for x in 1:n]
end

# Generate a single binomial random variable with success probability p.
# Returns Int64.
function rn_binom(trials::Int64, p)
	# Only allow success probabilities in between 0 and 1.
	if !(0 < p < 1)
		throw(ArgumentError("Success probability must be between 0 and 1."))
	end

	# Only allow positive numbers of trials.
	if trials < 1
		throw(ArgumentError("Number of trials must be at least 1."))
	end

	# Generate Bernoulli random variable for each trial.
	berns = rn_bernoulli(p, trials)

	# Return the sum of successful trials.
	return sum(berns)
end

# Generate n binomial random variables with success probability p as an
# Array{Int64, 1}.
function rn_binom(trials, p, n::Int64)
	return [rn_binom(trials, p) for x in 1:n]
end

# Generate a single geometric random variable with success probability p.
function rn_geo(p)
	# Only allow success probabilities in between 0 and 1.
	if !(0 < p < 1)
		throw(ArgumentError("Success probability must be between 0 and 1."))
	end

	lambda = -log(1 - p)

	exp = rn_exp(lambda)

	return ifloor(exp) + 1
end

# Generate n geometric random variables with success probability p.
function rn_geo(p, n::Int64)
	return [rn_geo(p) for x in 1:n]
end

# Generate a single gamma random variable with shape parameter alpha and rate
# parameter beta. This function implements Marsaglia and Tsang's method for 
# generating gamma random variables.
function rn_gamma(alpha, beta)
	if alpha <= 0 || beta <= 0
		throw(ArgumentError("Alpha and beta must be greater than zero."))
	end

	if (alpha >= 1)
		# Set two constants used in the algorithm.
		d = alpha - (1.0 / 3.0)
		c = 1.0 / sqrt(9.0 * d)

		# We need to loop until we generate appropriate random numbers
		while true
			# Generate Z~N(0,1).
			z = rn_standard_normal()

			# We need a z that will never result in a negative v.
			if z > -1.0 / c
				v = (1.0 + c * z)^3

				# Generate U~U(0,1).
				u = rn_unif(0, 1)

				# Compute the upper bound for log(u).
				u_bound = (.5 * z^2) + d - (d * v) + (d * log(v))

				# If this condition holds we've found a suitable result.
				if log(u) < u_bound
					return (d * v) / beta
				end
			end
		end
	else
		# When 0 < alpha < 1 we can return a transformed answer.
		x = rn_gamma(alpha + 1, beta)
		u = rn_unif(0, 1)
		return x * u ^ (1 / alpha)
	end
end

# Generate n gamma random variables with shape parameter alpha and rate
# parameter beta.
function rn_gamma(alpha, beta, n::Int64)
	return [rn_gamma(alpha, beta) for x in 1:n]
end

# Generate a beta random variable with shape parameters alpha and beta.
# Note that this does not use the rejection method.
function rn_beta(alpha, beta)
	if alpha <= 0 || beta <= 0
		throw(ArgumentError("Alpha and beta must be greater than zero."))
	end

	# Generate two independent gamma variables
	x = rn_gamma(alpha, 1)
	y = rn_gamma(beta, 1)

	return x / (x + y)
end

function rn_beta(alpha, beta, n::Int64)
	return [rn_beta(alpha, beta) for x in 1:n]
end

end