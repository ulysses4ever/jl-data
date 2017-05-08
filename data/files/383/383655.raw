include("Kinetics.jl");
include("Control.jl");
include("Flow.jl");
include("Dilution.jl");
#to run Fibrinolysis model
include("Balances.jl")
include("DataFileReactions.jl")
include("readParameters.jl")

# ----------------------------------------------------------------------------------- #
# Copyright (c) 2016 Varnerlab
# School of Chemical Engineering Purdue University
# W. Lafayette IN 46907 USA

# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights 
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell 
# copies of the Software, and to permit persons to whom the Software is 
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
# ----------------------------------------------------------------------------------- #
#function MassBalances(t,x,dxdt_vector,data_dictionary)
function MassBalances(t,x,data_dictionary,set_number)
# ---------------------------------------------------------------------- #
# MassBalances.jl was generated using the Kwatee code generation system.
# Username: rachellecover
# Type: PBPK-JULIA
# Version: 1.0
# Generation timestamp: 07-26-2016 09:08:18
# 
# Arguments: 
# t  - current time 
# x  - state vector 
# dxdt_vector - right hand side vector 
# data_dictionary  - Data dictionary instance (holds model parameters) 
# ---------------------------------------------------------------------- #

#@show t
# Get data from the data_dictionary - 
S = data_dictionary["STOICHIOMETRIC_MATRIX"];
C = data_dictionary["FLOW_CONNECTIVITY_MATRIX"];
tau_array = data_dictionary["TIME_CONSTANT_ARRAY"];

# Correct nagative x's = throws errors in control even if small - 
idx = find(x->(x<0),x);
x[idx] = 0.0;

# Call the kinetics function - 
# Call the kinetics function - 
(calc_rate_vector) = Kinetics(t,x,data_dictionary);
rate_vector = Float64[]
number_of_compartments = size(C, 1)
number_of_species = 18;
#@show number_of_compartments
#@show size(calc_rate_vector)
#to use reduced order fibrinolysis model
#@show data_dictionary["INITIAL_CONDITION_ARRAY"]
	#read in best parameters
	 pathToFile = "/home/rachel/Documents/Fibrinolysis_model_julia/src/Best100ParameterSets.txt"
	 currparams = readParameters(pathToFile,set_number)

for j = 1:number_of_compartments
	ReducedDict = Dict()
	upper_index = number_of_species*j
	lower_index = upper_index-17
	currx = x[lower_index:upper_index]
	ic_arr= data_dictionary["INITIAL_CONDITION_ARRAY"][lower_index:upper_index]
	#@show ic_arr
	ReducedDict= DataFileReactions(ic_arr)
	 ReducedDict= setParameters(currparams,ReducedDict)
	ReducedDict = patchParameters(ReducedDict,set_number)
	#@show (ReducedDict)
	#if(j == 8)
		rate_vector_curr = Balances(t,currx,ReducedDict)
	#else
		#rate_vector_curr = zeros(1,18)
	#end
	#@show rate_vector_curr
	for item in rate_vector_curr
		push!(rate_vector, item)
	end
end
#@show size(rate_vector)
# Call the control function - 
(rate_vector) = Control(t,x,rate_vector,data_dictionary);

# Call the flow function - 
(flow_terms_vector,q_vector) = Flow(t,x,data_dictionary);

# Call the dilution function - 
tmp_dvdt_vector = C*q_vector;
(dilution_terms_vector) = Dilution(t,x,tmp_dvdt_vector,data_dictionary);

#for ODE
dxdt_vector = similar(x)

# Encode the biochemical balance equations as a matrix vector product - 
tmp_vector = flow_terms_vector + S*rate_vector - dilution_terms_vector;
number_of_states = length(tmp_vector);
for state_index in collect(1:number_of_states)
	dxdt_vector[state_index] = tau_array[state_index]*tmp_vector[state_index];
end

# Correct nagative x's = throws errors in control even if small - 
idx = find(x->(x<0),x);
x[idx] = 0.0;

# Return the volume dvdt terms - 
number_of_compartments = length(tmp_dvdt_vector);
for compartment_index in collect(1:number_of_compartments)
	state_vector_index = (number_of_states)+compartment_index;
	dxdt_vector[state_vector_index] = tmp_dvdt_vector[compartment_index];
end
	return dxdt_vector
end
