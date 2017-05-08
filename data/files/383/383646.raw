function generateBestNparameters(n)
	ECPath = "/home/rachel/Documents/Fibrinolysis_model_julia/src/ec_array.dat.G3"
	PCPath = "/home/rachel/Documents/Fibrinolysis_model_julia/src/pc_array.dat.G3"

	ec_array = readdlm(ECPath)
	pc_array =readdlm(PCPath)

	#calculate error
	best_params = Array[]
	total_error = sum(ec_array[:,2:end],1)
	for k in collect(1:n)
		min_index = indmin(total_error)
		curr_best_params = pc_array[:,min_index]
		push!(best_params, curr_best_params)
		@show min_index
		@show curr_best_params
		#delete the best ones we've found
		pc_array[1:size(pc_array,1) .!= min_index,: ]
		deleteat!(vec(total_error),min_index)
	end
	writedlm(string("Best", n, "ParameterSets.txt"), best_params)

end
