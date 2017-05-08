include("Kinetics.jl");
include("Control.jl");
include("Flow.jl");
include("Dilution.jl");
include("reducedFibrinModel.jl")

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
function MassBalances(t,x,dxdt_vector,data_dictionary)
# ---------------------------------------------------------------------- #
# MassBalances.jl was generated using the Kwatee code generation system.
# Username: rachellecover
# Type: PBPK-JULIA
# Version: 1.0
# Generation timestamp: 05-06-2016 09:57:05
# 
# Arguments: 
# t,- current time 
# x,- state vector 
# dxdt_vector - right hand side vector 
# data_dictionary,- Data dictionary instance (holds model parameters) 
# ---------------------------------------------------------------------- #

# Get data from the data_dictionary - 
S = data_dictionary["STOICHIOMETRIC_MATRIX"];
C = data_dictionary["FLOW_CONNECTIVITY_MATRIX"];
tau_array = data_dictionary["TIME_CONSTANT_ARRAY"];

# Correct nagative x's = throws errors in control even if small - 
idx = find(x->(x<0),x);
x[idx] = 0.0;

# Call the kinetics function - 
(calc_rate_vector) = Kinetics(t,x,data_dictionary);
rate_vector = Float64[]
number_of_compartments = size(C, 1)
number_of_species = 20;
#@show number_of_compartments
#@show size(calc_rate_vector)
#@show size(x)
#to use Adis Model
params = [1.5800000e+07,9.7200000e+07,7.0900000e+06,3.6500000e+07,3.5085476e+05,1.5665729e+02,1.0500000e-04,4.4080665e+00,1.1645505e+01,1.8255242e+02,8.9644462e+04,2.9620688e+02,2.2704573e+04,2.4106120e+06,5.6900000e+01, 1.4200000e+01,7.7488961e+00,7.1642447e+03,2.2965787e-03,2.8714162e+02,4.4674728e+00,2.0400000e+01,3.7422536e+00,2.5726558e-02,1.7422401e+01,1.2830480e-01,7.5522957e+00,9.3800000e+01,2.7700000e+00,3.690000e+01,2.5800000e-01,1.0200000e+00,1.2600000e+00,1.6100000e+01,1.9900000e+00,3.0500000e+01,9.7100000e+01,2.8856018e-02,2.7840367e-02,1.5447597e-02,3.0721908e+00,1.0000000e+00,6.0500000e+00,3.0500000e+00,1.0000000e+00]

#@show length(params)
kV = params[1:27]
qV = [1,.5,20,.7,170,70,73]
cV = params[28:end]

for j = 1:number_of_compartments
	ReducedDict = Dict()
	upper_index = number_of_species*j
	lower_index = upper_index-(number_of_species)+1
	currx = x[lower_index:upper_index]

	#should use some logic to change kV,cV,qV if in wound?
	rate_vector_curr = reducedFibrinModel(t,currx,kV,cV,qV)
	#@show rate_vector_curr[3]
	for item in rate_vector_curr
		push!(rate_vector, item)
	end
end


# Call the control function - 
(rate_vector) = Control(t,x,rate_vector,data_dictionary);

# Call the flow function - 
(flow_terms_vector,q_vector) = Flow(t,x,data_dictionary);

# Call the dilution function - 
tmp_dvdt_vector = C*q_vector;
(dilution_terms_vector) = Dilution(t,x,tmp_dvdt_vector,data_dictionary);

# Encode the biochemical balance equations as a matrix vector product - 
tmp_vector = flow_terms_vector + S*rate_vector - dilution_terms_vector;
number_of_states = length(tmp_vector);
for state_index in collect(1:number_of_states)
	dxdt_vector[state_index] = tau_array[state_index]*tmp_vector[state_index];
end

# Return the volume dvdt terms - 
number_of_compartments = length(tmp_dvdt_vector);
for compartment_index in collect(1:number_of_compartments)
	state_vector_index = (number_of_states)+compartment_index;
	dxdt_vector[state_vector_index] = tmp_dvdt_vector[compartment_index];
end

end
