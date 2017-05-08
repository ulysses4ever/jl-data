######################################################
#
# MSM Plot
#
# Date:   2014-12-02
# Author: Hessel Tuinhof
# 
# Simulate and plot a Markov-Switching Multifractal (MSM)
#
# Required packages: 	PyPlot
# Required functions:	MSM.jl
#
######################################################

# load packages & functions
using PyPlot
require("../src/msm/MSM.jl")

# define colors
rouge = (0.79, 0.0, 0.1)

# configure parameters
num_sim = 1
sim_length = 5000
kbar = 8
m0 = 1.4
sigma = 0.5
gamma_kbar = 0.95
b = 3

# set seed
srand(314159265358979323846)

# plot MSM (returns & log price)
figure()
msm = MSM(num_sim, sim_length, m0, kbar, sigma, gamma_kbar, b)
plot(msm, linewidth = 0.5, color = rouge)
xlim(xmax = sim_length)
figure()
plot(cumsum(msm), linewidth = 1, color = rouge)
xlim(xmax = sim_length)
