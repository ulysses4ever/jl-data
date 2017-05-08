include("Utility.jl")
include("BalanceEquations.jl")
include("CoagulationModelFactory.jl")
include("runModel.jl")

function CreateSensitivityMatrix()
	# Setup the timescale of the simulation -
	time_start = 0.0
	time_stop = 60.0
	time_step_size = 0.01
	number_of_timesteps = length(time_start:time_step_size:time_stop)
	params = readdlm("parameterEstimation/AfterCalculatingF8FunctionPostNM.txt", ',')
	data_dictionary=buildDictFromOneVector(params)
	number_of_states = 11
	param_names = readdlm("sensitivity/boundsplusorminus50percent.txt", ',')[:,1]
	for (parameter_index, parameter_value) in enumerate(param_names)
		local_data_dictionary = deepcopy(data_dictionary)
		tic()
		println(string("On parameter index ", parameter_index, " and value ", parameter_value))
		(T,X) = solveAdjBalances(time_start,time_stop,time_step_size,parameter_index,local_data_dictionary)
		toc()
		data_array = [T X]
		file_path = "./sensitivity/AdjSimulation03012017/-P"*string(parameter_index)*".dat"
		writedlm(file_path,data_array)
	end
end
