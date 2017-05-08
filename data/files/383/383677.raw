function readParameters(pathToFile)
	params = readdlm(pathToFile)
	return params
end

function setParameters(params, data_dictionary)
	data_dictionary["kinetic_parameter_array"] = params[1:29]
	data_dictionary["control_parameter_array"]= params[30:end]
	return data_dictionary
end
pathToFile = "/home/rachel/Documents/Fibrinolysis_model_julia/src/tmp/global_best_parameter_set.dat"
