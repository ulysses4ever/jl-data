######################################################
#
# Markov-Switching Multifractal (MSM)
#
# Date:   2014-11-19
# Author: Hessel Tuinhof
# 
# Function to simulate a MSM process.
#
# Reference: 
# - Stein, William: https://raw.githubusercontent.com/sagemath/sagelib/master/sage/finance/markov_multifractal_cython.pyx
#
# Required packages: 	Distributions
#
# Input:	
#   num_sim ... number of simulatons, positive integer
#   sim_length ... length of simulation, positive integer
#   m0 ... multiplier, float in [0,2]
#   kbar ... number of frequencies, positive integer
#   sigma ... standard deviation of returns, positve float
#   gamma_kbar ... transition probability, float in [0,1)
#   b ... geometric rate, float in (1,inf)
#
# Output:
#   msm ... simulated log returns
#
# Examples: 
#   # Simulation of log returns (1 simulation)
#   plot(MSM(1, 4000, 1.4, 8, 0.55, 0.92, 3)) 
#
#   # Simulation of log price (10 simulations)
#   plot(cumsum(MSM(10, 4000, 1.4, 8, 0.55, 0.92, 3)))
#
######################################################

#####################   Warning   #####################
# For large simulation purposes the use of the array type
# is not recommendable. Instead one should save the sim-
# ulated returns in an DataFrame or TimeSeries type for
# improved performance.
#####################   Warning   #####################

using Distributions

function MSM(num_sim, sim_length, m0, kbar, sigma, gamma_kbar, b)
	m1 = 2-m0
    gammaone = 1 - exp(log(1-gamma_kbar)/(b^(kbar-1)))
    gamma  = zeros(kbar)
    for i = 1:kbar
		gamma[i] = 1-(1-gammaone)^(b^(i-1))
	end
	markovstatevector = zeros(kbar)
	msm = zeros(sim_length, num_sim)
	for i = 1:num_sim
		for j = 1:kbar
			convert(Bool, rand(Int64) & 1) ? markovstatevector[j] = m0 : markovstatevector[j] = m1
		end
		err = randn(sim_length)
		for j = 1:sim_length
			msm[j,i] = sigma * err[j] * sqrt(prod(markovstatevector))
			for k = 1:kbar
				if rand() <= gamma[k]
					convert(Bool, rand(Int64) & 1) ? markovstatevector[k] = m0 : markovstatevector[k] = m1
				end
			end
		end			
	end
	return msm
end
