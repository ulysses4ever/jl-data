# Set up dictionaries to store parameters, etc.

# ---------------------- Basic parameters ---------------------------------
param = Dict()
param["D"] = 100
param["T"] = 15
param["I"] = 30
param["max_b"] = 500
param["w_max"] = 10000

param["gamma"] = 100/110
param["controls"] = collect(-8:0.5:2)
param["numControls"] = length(param["controls"])
param["o_vec"] = collect(-8:2).'

# -------------------------------------------------------------------------
dist = Dict()
# hard-code distribution
dist["Prob_o"] = [param["o_vec"]; repmat([1/11], 1, 11)]


# ---------------------- Storage of data ----------------------------------
data = Dict()
data["signals"] = repmat([-4.0], param["I"], 1)
