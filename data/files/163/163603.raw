rate_upper_bound = 200 #500 #500000 # mM/hr
rate_lower_bound = 0 # mM/hr # essentially zero
CAT_lower_bound = 0 # mM/hr

enz_deg_upper_bound = 1 # fast degradation
enz_deg_lower_bound = 0 # no degradation

sat_upper_bound = 10 # mM
sat_lower_bound = 0.001 # mM

control = [1.17085;2.9565;1.20274;0.0162921;0.00812746;0.0764206;0.00953642;
1.09595;0.0129062;139.75;0.073836;1.64798;4.277;0.382617;1.03476;0.864245;0.0261159;
0.288461;1.0277;7.82276;0.117037;1.17055;0.40326;1.38878;0.0532845;1.31205;0.000181926;
5.89223;0.067948;0.035341;1.85727e-5;0.35985;0.0519835;0.290466]

num_sets = 1000

parameter_bounds = readdlm("parameter_bounds")
parameter_bounds = [parameter_bounds parameter_bounds[:,2]-parameter_bounds[:,1]]

range_width = 1
range_lower_bound = .5*(1-range_width)

Params = zeros(815,num_sets)
for i in 1:num_sets
    Params[[1:154;156:163],i] = rate_upper_bound*rand(162,1) # rate constants go from 0 to 500000
    Params[155,i] = 0.1*rand() # R_CAT is bounded from 0 to 0.1
    Params[164:326,i] = .98*rand(163,1)+.02 # enzyme degradation rates go from 0.02 to 1
    Params[326+1:326+455,i] = 10.^(1-4*rand(455,1)) # satuuration constants go from 0.001 to 10
    Params[326+455+1:326+455+34,i] = control
#    Params[:,i] = parameter_bounds[:,1]+(range_lower_bound+range_width*rand(815,1)).*parameter_bounds[:,3]
end

writedlm("params_rand100",Params)

include("SolveRand100.jl")
include("PlotEnsemble.jl")







