#-----------------------------
# Defining common variables used for
# unit testing, and including the functions
# used
#-----------------------------
using Base.Test
srand(42);
Nobs = 1024;
y = randn(Nobs);
include("var.jl")
#----------------------------


#------------------------------
# TEST 1.1: Test if NaNs, and Infs are found
# - Reading and writing a Nobs element vector
#   which has some bad data in it
#------------------------------
y[2] = NaN
y[3] = Inf
y[5] = -Inf
y[isfinite(y)]
a = var_dynamic(y)
print("Variance: ")
println(a)

println("var_dynamic() passed test")
#------------------------------
