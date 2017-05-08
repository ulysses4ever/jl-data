function calculateMSE(t,predictedThrobin, experimentalData)
	num_points = size(t,1)
	interpolatedExperimentalData = Float64[]
	for j in collect(1:num_points)
		currt = t[j]
		upperindex = searchsortedfirst(experimentalData[:,1], currt, by=abs)
		if(upperindex ==1)
			lowerindex = 1
		else
			lowerindex = upperindex -1
		end

		if(upperindex >= size(experimentalData,1)&& upperindex !=1)
		upperindex = size(experimentalData,1)
		lowerindex = upperindex-1
	end
		val = linearInterp(experimentalData[lowerindex,2], experimentalData[upperindex,2],experimentalData[lowerindex,1], experimentalData[upperindex,1], currt)
		push!(interpolatedExperimentalData,val)
	end
	sum = 0.0
	for j in collect(1:size(predictedThrobin,1))
		sum = sum +(predictedThrobin[j]-interpolatedExperimentalData[j])^2
	end
	#figure()
	#plot(t, interpolatedExperimentalData)
	#@show sum, size(predictedThrobin,1)
	return sum/size(predictedThrobin,1), interpolatedExperimentalData#MSE
end

function linearInterp(lowerVal, upperVal, tstart, tend,tdesired)
	
	val = lowerVal + (upperVal-lowerVal)/(tend-tstart)*(tdesired-tstart)
	if(isnan(val))
		val = 0.0
	end
	return val
end

function calculateAUC(t,y)
	   local n = length(t)
    if (length(y) != n)
        error("Vectors 't', 'y' must be of same length")
    end

	sum = 0.0
	for j in collect(2:n)
		curr_rect = (t[j]-t[j-1])*(y[j]+y[j-1])/2
		sum = sum+curr_rect
	end
	return sum
end

function buildDictFromOneVector(vector)
	kinetic_parameter_vector = vector[1:18]
	control_parameter_vector=vector[19:38]
	platelet_parameter_vector=vector[39:44]
	timing = vector[45:46]
	dict = buildCoagulationModelDictionary(kinetic_parameter_vector, control_parameter_vector, platelet_parameter_vector, timing)
	return dict
end

# Generates new parameter array, given current array -
function neighbor_function(parameter_array)

  SIGMA = 0.05
  number_of_parameters = length(parameter_array)

  # calculate new parameters -
  new_parameter_array = parameter_array.*(1+SIGMA*randn(number_of_parameters))

  # Check the bound constraints -
  LOWER_BOUND = SMALL
  UPPER_BOUND = 1E9
  lb_arr= LOWER_BOUND*ones(number_of_parameters)
  up_arr =UPPER_BOUND*ones(number_of_parameters)
	lb_arr[9] = 10.0 #lower bound on k_inhibition_ATIII
	lb_arr[45]= 3.0 #lower bound on time delay, 3 minutes
	#up_arr[46]= .01 #upper bound on scaling for tau
	up_arr[3] = 10.0 #upper bound on the k_cat for self activation of thrombin

  # return the corrected parameter arrays -
  return parameter_bounds_function(new_parameter_array,lb_arr, up_arr)
end

function acceptance_probability_function(rank_array,temperature)
  return (exp(-rank_array[end]/temperature))
end

function cooling_function(temperature)

  # define my new temperature -
  alpha = 0.9
	@show temperature
  return alpha*temperature
end


# Helper functions -
function parameter_bounds_function(parameter_array,lower_bound_array,upper_bound_array)

  # reflection_factor -
  epsilon = 0.01

  # iterate through and fix the parameters -
  new_parameter_array = copy(parameter_array)
  for (index,value) in enumerate(parameter_array)

    lower_bound = lower_bound_array[index]
    upper_bound = upper_bound_array[index]

    if (value<lower_bound)
      new_parameter_array[index] = lower_bound
    elseif (value>upper_bound)
      new_parameter_array[index] = upper_bound
    end
  end

  return new_parameter_array
end

function createCorrectDict(basic_dict, exp_index)
	if(exp_index==1)
		
	elseif(exp_index==2)
		basic_dict["FACTOR_LEVEL_VECTOR"][3] =basic_dict["FACTOR_LEVEL_VECTOR"][3]*1.06 
	elseif(exp_index==3)
		basic_dict["FACTOR_LEVEL_VECTOR"][3] =basic_dict["FACTOR_LEVEL_VECTOR"][3]*.39
	elseif(exp_index==4)
		basic_dict["FACTOR_LEVEL_VECTOR"][3] =basic_dict["FACTOR_LEVEL_VECTOR"][3]*.07  
	elseif(exp_index==5)
		basic_dict["FACTOR_LEVEL_VECTOR"][3] =basic_dict["FACTOR_LEVEL_VECTOR"][3]*.01
	elseif(exp_index==6)
		basic_dict["FACTOR_LEVEL_VECTOR"][3] =basic_dict["FACTOR_LEVEL_VECTOR"][3]*.00
	end
	return basic_dict
end

function generateBestNparameters(n, ec_array, pc_array)
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
	return best_params

end

function generateNbestPerObjective(n,ec_array, pc_array)
	best_params=Array[]
	num_objectives =size(ec_array,1)
	for k in collect(1:n)
		for j in collect(1:num_objectives)
			curr_error=ec_array[j,:]
			min_index = indmin(curr_error)
			curr_best_params = pc_array[:,min_index]
			push!(best_params, curr_best_params)
			pc_array[1:size(pc_array,1) .!= min_index,: ]
			deleteat!(vec(curr_error),min_index)
		end
	end
	return best_params
end

function analyzeParams()
	allparams = zeros(1,46)
	for j in collect(1:6)
		currparams = readdlm(string("parameterEstimation/LOOCVSavingAllParams_2016_12_23_Take2/bestParamSetsFromLOOCV",j,"excluded.txt"), ',')
		meancurrparams = mean(currparams,1)
		allparams = vcat(allparams, meancurrparams)
	end
	return allparams[2:end,:]
end

function dict_to_vec(d)
    v = Array(Float64, 0)
	selectedkeys = ["FACTOR_LEVEL_VECTOR","CONTROL_PARAMETER_VECTOR","PLATELET_PARAMS", "TIME_DELAY","KINETIC_PARAMETER_VECTOR", "ALEPH"] 
    for k in selectedkeys
	for j in collect(1:length(d[k]))
        	push!(v, d[k][j])
	end
    end
    return v
end

function extractValueFromDual(input)
	# to get the value of a dual as Float64 that can be used by min/max
	if(contains(string(typeof(input)), "Dual"))
		return input.value
	else
		return input
	end
end
