using POETs
include("hcmem_lib.jl")
include("multidimensionalMSE.jl")

function test_model()
	outputfile = "outputMay26/poetsinfo.txt"
	touch(outputfile)
	number_of_subdivisions = 10
  	number_of_parameters = 9
  	number_of_objectives = 2
	params0 = [75,1.5,.5,250, .5, .5, 1.67,.96, .7]
	ec_array = zeros(number_of_objectives)
  	pc_array = zeros(number_of_parameters)
	for index in collect(1:number_of_subdivisions)
		initial_parameter_array = Float64[]
		#create new starting conditions by peturbing given initial parameter values
		for j in collect(1:number_of_parameters)
			push!(initial_parameter_array, params0[j]+(.5-rand()))
		end

		#run JuPOETS
		(EC,PC,RA) = estimate_ensemble(multidimensionalMSE,neighbor_function,acceptance_probability_function,cooling_function,initial_parameter_array;rank_cutoff=4,maximum_number_of_iterations=10,show_trace=true)
		  # Package -
    		ec_array = [ec_array EC]
    		pc_array = [pc_array PC]

		#write outputs to file
		@show (EC, PC, RA)
		f = open(outputfile, "a")
		write(f, string(EC, ",", PC, ",", RA, "\n"))
		close(f)
	end

	return (ec_array, pc_array)
end
test_model()
