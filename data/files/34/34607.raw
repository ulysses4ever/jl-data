######################################################
#
# Trading Time Plot
#
# Date:   2014-10-02
# Author: Hessel Tuinhof
# 
# Plot trading time against physical time. Trading time 
# is the cumulative sum of a multiplicative cascade.
# Here we use a canonical binomial cascade.
#
# Required packages: 	PyPlot
# Required functions:	BinomialCanonical.jl
#
######################################################

# load packages & functions
using PyPlot
require("../src/cascades/BinomialCanonical.jl")

# define colors
rouge = (0.79, 0.0, 0.1)
turquoise = (0, 0.41, 0.41)

# configure parameters
m0 = [0.5, 0.6, 0.65, 0.75]
num_cascades = 10

# set seed
srand(314159265358979323846)

# plot trading time 
for i = 1:4
	figure()
	mu = BinomialCanonical(m0[i], num_cascades)
	x_coordinates = linspace(0, 1, 2^num_cascades)
	y_coordinates = cumsum(mu)/cumsum(mu)[end]
	plot(x_coordinates, y_coordinates, linewidth = 1, color = rouge)
	plot([0, 1], [0, 1], linewidth = 1, linestyle = "--", color = turquoise)
end

