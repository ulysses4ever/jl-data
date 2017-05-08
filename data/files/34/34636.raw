######################################################
#
# Conservative Binomial Cascade Function
#
# Date:   2014-09-28
# Author: Hessel Tuinhof
# 
# Function to construct a conservative binomial cascade.
# The conservative measure preserves mass exactly.
#
# Reference: 
# - Riedi, Rudolf H.: Multifractal Processes
# (http://www.stat.rice.edu/~riedi/Publ/PDF/MP.pdf)
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

function BinomialConservative(m0, k, startmass = 1)
	rand(Bernoulli()) == 1 ? M = m0 : M = 1-m0
	mu = [M*startmass, (1-M)*startmass]
	if k > 1
		tmp = Float64[]
		mu = append!(tmp, [BinomialConservative(m0, k-1, mu[1]), BinomialConservative(m0, k-1, mu[2])])
	end
	return mu
end
