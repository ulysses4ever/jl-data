######################################################
#
# Binomial Cascade Plot
#
# Date:   2014-09-29
# Author: Hessel Tuinhof
# 
# Plot several conservative and canonical binomial
# cascades.
#
# Required packages: 	PyPlot
# Required functions: 	BinomialConservative.jl
#					  	BinomialCanonical.jl
#
######################################################

# load packages & functions
using PyPlot
require("../src/cascades/BinomialConservative.jl")
require("../src/cascades/BinomialCanonical.jl")

# define colors 
rouge = (0.79, 0.0, 0.1)
turquoise = (0, 0.41, 0.41)

# set seed
srand(314159265358979323846)

###
### Plot conservative binomial cascade (k = 5)
###

# configure parameters
m0 = 0.6
num_cascades = 5

# plot cascade 
figure()
mu = BinomialConservative(m0, num_cascades)
y_coordinates = 2 * push!(mu, mu[end]) 
x_coordinates = linspace(0, 1, 2^num_cascades + 1)
step(x_coordinates, y_coordinates, where = "post", linewidth = 1, color = rouge)
ylim(ymin = 0, ymax = maximum(y_coordinates) + (maximum(y_coordinates)/100)*5) # add 5% to the maximum of the y-values

###
### Plot conservative binomial cascade (k = 10)
###

# configure parameters
m0 = 0.6
num_cascades = 10

# plot cascade 
figure()
mu = BinomialConservative(m0, num_cascades)
y_coordinates = 2 * push!(mu, mu[end])
x_coordinates = linspace(0, 1, 2^num_cascades + 1)
step(x_coordinates, y_coordinates, where = "post", linewidth = 0.6, color = rouge)
ylim(ymin = 0, ymax = maximum(y_coordinates) + (maximum(y_coordinates)/100)*5) # add 5% to the maximum of the y-values

###
### Plot canonical binomial cascade (k = 5)
###

# configure parameters
m0 = 0.6
num_cascades = 5

# plot cascade 
figure()
mu = BinomialCanonical(m0, num_cascades)
y_coordinates = 2 * push!(mu, mu[end])
x_coordinates = linspace(0, 1, 2^num_cascades + 1)
step(x_coordinates, y_coordinates, where = "post", linewidth = 1, color = turquoise)
ylim(ymin = 0, ymax = maximum(y_coordinates) + (maximum(y_coordinates)/100)*5) # add 5% to the maximum of the y-values

###
### Plot canonical binomial cascade (k = 10)
###

# configure parameters
m0 = 0.6
num_cascades = 10

# plot cascade 
figure()
mu = BinomialCanonical(m0, num_cascades)
y_coordinates = 2 * push!(mu, mu[end])
x_coordinates = linspace(0, 1, 2^num_cascades + 1)
step(x_coordinates, y_coordinates, where = "post", linewidth = 0.6, color = turquoise)
ylim(ymin = 0, ymax = maximum(y_coordinates) + (maximum(y_coordinates)/100)*5) # add 5% to the maximum of the y-values



	
