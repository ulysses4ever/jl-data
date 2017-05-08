######################################################
#
# Canonical Binomial Cascade Function
#
# Date:   2014-09-29
# Author: Hessel Tuinhof
# 
# Function to construct a canonical binomial cascade.
# The canonical measure only preserves mass on average.
#
# Reference:
# - Riedi, Rudolf H.: Multifractal Processes
#   (http://www.stat.rice.edu/~riedi/Publ/PDF/MP.pdf)
# - Calvet, L. E.; Fisher, A. J.: Multifractal Volatility
#
# Required packages: Distributions
#
# Input:
#   m0 ... submass, float in (0,1)
#   k ... number of cascades, positive integer
#   startmass ... total mass, default: 1
#
# Output:
#   mu ... vector contains all measures
#
######################################################

using Distributions

function BinomialCanonical(m0, k, startmass = 1)
	mu = zeros(2)
	M = zeros(2)
	for i = 1:2
		rand(Bernoulli()) == 1 ? M[i] = m0 : M[i] = 1-m0
		mu[i] = M[i]*startmass
	end
	if k > 1
		tmp = Float64[]
		mu = append!(tmp, [BinomialCanonical(m0, k-1, mu[1]), BinomialCanonical(m0, k-1, mu[2])])
	end
	return mu
end
