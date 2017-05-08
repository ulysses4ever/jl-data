@everywhere function readParameters(pathToFile)
	params = readdlm(pathToFile)
	return params
end

@everywhere function readParameters(pathToFile, set_number)
	allparams = readdlm(pathToFile, ',')
	params = allparams[set_number,:]
	#println("read")
	return params
end

@everywhere function setParameters(params, data_dictionary)
	data_dictionary["kinetic_parameter_array"] = params[1:29]
	data_dictionary["control_parameter_array"]= params[30:end]
	#data_dictionary=patchParameters(data_dictionary)
	return data_dictionary
end

@everywhere function patchParameters(data_dictionary,set_number)
	#to change the parameters in the protein C pathway to something closer to what they should be
	#@show size(data_dictionary["kinetic_parameter_array"])
	seed =set_number
	srand(seed)
	data_dictionary["kinetic_parameter_array"][5] = .1 +.1/10(.5-rand())
	data_dictionary["kinetic_parameter_array"][6] = 30 + 30/10(.5-rand())
	data_dictionary["kinetic_parameter_array"][13] = 2.0 +abs(2.0/10(.5-rand()))#abs forces positivity
	data_dictionary["kinetic_parameter_array"][15] = .1 + abs(.1/10(.5-rand()))
	
	#prevent negative k
	while(data_dictionary["kinetic_parameter_array"][5]<0)
		if (data_dictionary["kinetic_parameter_array"][5] <0)
			#@show data_dictionary["kinetic_parameter_array"][5] 
		end
		data_dictionary["kinetic_parameter_array"][5] = .1 +.1/10(.5-rand())
		#@show data_dictionary["kinetic_parameter_array"][5]
	end

	while(data_dictionary["kinetic_parameter_array"][6]<0)
		data_dictionary["kinetic_parameter_array"][6] = 30 + 30/10(.5-rand())
	end


	#@show size(data_dictionary["kinetic_parameter_array"])
	#println("patched")
	return data_dictionary
end

