######################################################
#
# Multifractal Model of Asset Returns (MMAR)
#
# (in the special case of H=1/2)
#
# Date:   2014-11-13
# Author: Hessel Tuinhof
# 
# Function to simulate a MMAR process using a canonical
# binomomial cascade.
#
# Reference: 
# - Riedi, Rudolf H.: Multifractal Processes 
#   (http://www.stat.rice.edu/~riedi/Publ/PDF/MP.pdf)
#
# Required packages: 	Distributions
# Required functions: 	BinomialCanonical.jl
#
# Input:	
#   m0 ... multiplier, float in (0,1)
#   k ... number of cascades, positive integer
# 
# Output: 	
#   mmar ... simulated log returns
#
# Examples: 
#   # Simulation of log returns
#   plot(MMAR(0.6, 10)) 
#
#   # Simulation of log price
#   plot(cumsum(MMAR(0.6, 10)))        
#
######################################################

using Distributions
require("/home/htuinhof/documents/Uni/Masterthesis/src/cascades/BinomialCanonical.jl")

function MMAR(m0, k)
	T = 2^k
	N = linspace(0, 1, T)
	mmar = zeros(T)
	mu = BinomialCanonical(m0, k)
	mu_normalized = cumsum(mu) / cumsum(mu)[end]
	mmar[1] = rand(Normal(0, mu_normalized[1]))
	for i = 0:T-2
		mu_normalized[T-i] = mu_normalized[T-i] - mu_normalized[T-i-1]
		mmar[T-i] = rand(Normal(0, mu_normalized[T-i]))
	end
	return mmar
end
