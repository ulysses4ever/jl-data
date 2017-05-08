include("Utility.jl")
include("utilities.jl")
include("CoagulationModelFactory.jl")
using PyPlot

function calculateSensitivityArr()
	pathToSensitivityFiles = "sensitivity/AdjSimulation03012017/"
	pattern = "-P"
	timeSkip = 1.0
	time_start = 0.0
	time_stop = 60.0
	time_step_size=.01
	params = readdlm("parameterEstimation/AfterCalculatingF8FunctionPostNM.txt", ',')
	data_dictionary = buildDictFromOneVector(params)
	num_species =11
	eps = 1E-2
	parameter_name_mapping_array = data_dictionary["parameter_name_mapping_array"]
	time_arr,sensitivity_arr = calculate_sensitivity_array(pathToSensitivityFiles, pattern, timeSkip, data_dictionary)
	@show size(sensitivity_arr)
	@show size(time_arr)
	avg_sensitivity_arr = calculate_average_scaled_sensitivity_array(pathToSensitivityFiles, pattern, data_dictionary)
	@show size(avg_sensitivity_arr)
	avg_state_arr = time_average_model_outputs(pathToSensitivityFiles, pattern, timeSkip, data_dictionary)
	useful_state_vec = mean(avg_state_arr,1)
	@show useful_state_vec
	@show size(avg_state_arr)
	estable_params = estimate_identifiable_parameters(avg_sensitivity_arr, eps)
	@show estable_params
	W = createW(num_species,useful_state_vec, eps)
	#FIM = calculate_fisher_information_matrix(avg_sensitivity_arr, eye(num_species)*eps,estable_params)
	FIM = calculate_fisher_information_matrix(avg_sensitivity_arr, W,estable_params)
	@show FIM
	@show size(FIM)
	d = abs(diag(inv(FIM)))
	@show d
	var = (d.^(.5))
	@show var
	CI_top = params[estable_params]+1.96*var
	CI_bottom = params[estable_params]-1.96*var
	#plotParamEsts(params[estable_params], var, CI_top, CI_bottom,parameter_name_mapping_array[estable_params])
	return (parameter_name_mapping_array[estable_params], params[estable_params], CI_top, CI_bottom)
end

function createW(num_species, time_avg_data, eps)
	W = eye(num_species)*eps
	for(j in collect(1:num_species))
		for(i in collect(1:num_species))
			#if(i!=j)
				W[i,j]=time_avg_data[i]*time_avg_data[j]*.1^2
			#end
		end
	end
	@show(W==transpose(W))
	return W
	
end

function plotParamEsts(params,var, CI_top, CI_bottom, labels)
	close("all")
	figure(figsize=[15,15])
	data = Array(Any,size(params,1)) 
	@show params
	@show var
	for i in collect(1:size(params,1))
		data[i] = [var[i], (params[i]), CI_top[i], CI_bottom[i];]
	end
	@show size(data)
	boxplot(data) # Symbol color and shape (rs = red square)
	x = collect(1:size(labels,1))
	ax = gca()
	ax[:xaxis][:set_ticks](x)
	ax[:xaxis][:set_ticklabels](labels, rotation = 60, fontsize = 8)

end

function makeHeatMap(data, timestr)
	figure(figsize=[15,15])
	timeSkip = 1.0
	time_start = 0.0
	time_stop = 120.0
	time_step_size=0.01
	data_dictionary = DataDictionary(time_start,time_stop,time_step_size)
	labels=["gene 1", "gene 2", "gene 3", "mRNA 1", "mRNA2", "mRNA3", "protein 1", "protein 2", "protein 3" ]
	if(size(data,1)==9 && size(data,2)==9)
		x = collect(0:size(labels,1)-1)
		y= collect(0:size(labels,1)-1)
		pcolormesh(x,y,abs(data),cmap="Reds")
		colorbar()
		ax = gca()
		ax[:xaxis][:set_ticks](x-.5)
		ax[:xaxis][:set_ticklabels](labels, rotation = 60, fontsize = 8)
		ax[:yaxis][:set_ticks](y+.5)
		ax[:yaxis][:set_ticklabels](labels, rotation = 0, fontsize = 8)
		savefig(string("figures/ProteinInteractions",timestr, ".pdf"))
	elseif(size(data,1)==24 && size(data,2)==24)
		x = collect(0:size(data,1))
		y= collect(0:size(data,1))
		pcolormesh(x,y,abs(data), cmap="Reds")
		colorbar()
		ax = gca()
		labels = data_dictionary["parameter_name_mapping_array"]
		ax[:xaxis][:set_ticks](x-.5)
		ax[:xaxis][:set_ticklabels](labels, rotation = 60, fontsize = 8)
		ax[:yaxis][:set_ticks](y+.5)
		ax[:yaxis][:set_ticklabels](labels, rotation = 0, fontsize = 8)
		savefig(string("figures/ParameterInteractions",timestr, ".pdf"))
	elseif(size(data,1)==9 && size(data,2)==24)
		x = collect(0:size(data,2))
		y= collect(0:size(data,1))
		pcolormesh(x,y,abs(data), cmap="Reds")
		colorbar()
		ax = gca()
		xlabels = data_dictionary["parameter_name_mapping_array"]
		ax[:xaxis][:set_ticks](x-.5)
		ax[:xaxis][:set_ticklabels](xlabels, rotation = 60, fontsize = 8)
		ax[:yaxis][:set_ticks](y+.5)
		ax[:yaxis][:set_ticklabels](labels, rotation = 0, fontsize = 8)
		savefig(string("figures/ParameterSpeciesInteractions",timestr, ".pdf"))

	end
end
