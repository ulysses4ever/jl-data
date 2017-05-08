function readParameters(pathToFile)
	params = readdlm(pathToFile)
	return params
end

function readParameters(pathToFile, set_number)
	allparams = readdlm(pathToFile)
	params = allparams[:,set_number]
end

function setParameters(params, data_dictionary)
	data_dictionary["kinetic_parameter_array"] = params[1:29]
	data_dictionary["control_parameter_array"]= params[30:end]
	return data_dictionary
end

function patchParameters(data_dictionary)
	#to change the parameters in the protein C pathway to something closer to what they should be
	data_dictionary["kinetic_parameter_array"][5] = .1 +.1/10(.5-rand())
	data_dictionary["kinetic_parameter_array"][6] = 30 + 30/10(.5-rand())
	#println("patched")
	return data_dictionary
end

