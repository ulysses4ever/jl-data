#generate a least-squares regression surface. Independent data is time,
#temperature, and dew point

using PyPlot
using Convex
using SCS
using MathProgBase
using GLPKMathProgInterface
using GLPK
using Debug

include("epi_trend.jl")
include("polyfun.jl")
include("genreg.jl")
include("evalreg.jl")

#load Data file first
Data=readcsv("data/refinement.csv",skipstart=1)

t_exp = 3
naughty_exp=2

num_part = 2 #The number of subintervals for non-time explanatory variables

reg=epi_trend(Data, t_exp, naughty_exp, num_part)

#plot the real data
scatter(Data[:,1], Data[:,4], alpha=.5, label="observed")
hold(true)

#predicted data
@bp
pdat=reg(Data[:,1:size(Data,2)-1])

#plot the predicted data via the regression
scatter(Data[:,1], pdat, alpha=.5, c="r",label="predicted")
xlabel("time (hour)")
ylabel("load")
title("Observed vs. Predicted Load")
legend(loc="upper left", fancybox="true")

#that curve that Roger wants. We will construct regressions for temp 
#and dew in time, and then plug those in for our weather predictions

q=linspace(0,24,100)
temp=multipolyval(genreg(Data[:,1], Data[:,2],3,2),q,3,2) #This last two
#doesn't do anything
dew=multipolyval(genreg(Data[:,1], Data[:,3],3,2),q,3,2) 
#these need work


X=hcat(q,temp,dew)
plot(q,evalreg(reg, X, cut, t_exp, naughty_exp), c="g", label= "Typical Day's Load") 
legend(loc="upper left", fancybox="true")

hold(false)

