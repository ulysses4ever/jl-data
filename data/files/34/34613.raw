######################################################
#
# MMAR Plot
#
# Date:   2014-11-13
# Author: Hessel Tuinhof
# 
# Simulate and plot a Brownian Motion in multifractal
# trading time (also called MMAR).
#
# Required packages: 	PyPlot
# Required functions:	MMAR.jl
#
######################################################

# load packages & functions
using PyPlot
require("../src/mmar/MMAR.jl")

# define colors
rouge = (0.79, 0.0, 0.1)

# configure parameters
m0 = 0.6
num_cascades = 10

# set seed
srand(314159265358979323846)

# plot MMAR (returns & log price)
figure()
mmar = MMAR(m0, num_cascades)
plot(mmar, linewidth = 0.7, color = rouge)
xlim(xmax = 2^num_cascades)
figure()
plot(cumsum(mmar), linewidth = 1, color = rouge)
xlim(xmax = 2^num_cascades)


