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
  LOWER_BOUND = 1E-9
  UPPER_BOUND = 1E9
  lb_arr= LOWER_BOUND*ones(number_of_parameters)
  up_arr =UPPER_BOUND*ones(number_of_parameters)
	#lb_arr[9] = 10.0 #lower bound on k_inhibition_ATIII
	#lb_arr[45]= 3.0 #lower bound on time delay, 3 minutes
	#up_arr[46]= .01 #upper bound on scaling for tau
	#up_arr[3] = 10.0 #upper bound on the k_cat for self activation of thrombin

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
	total_error= vec(total_error)
	for k in collect(1:n)
		min_index = indmin(total_error)
		curr_best_params = pc_array[:,min_index]
		push!(best_params, curr_best_params)
		@show min_index
		@show curr_best_params
		#delete the best ones we've found
		@show size(pc_array)
		@show size(total_error)
		pc_array[1:size(pc_array,1) .!= min_index,: ]
		deleteat!((total_error),min_index)
		@show size(pc_array)
		@show size(total_error)
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

function build_param_dict(problem_vec)
	params = Expr[:(p_1=>$(problem_vec[1])); :(p_2=>$(problem_vec[2])); :(p_3=>$(problem_vec[3])); :(p_4=>$(problem_vec[4])); :(p_5=>$(problem_vec[5])); :(p_6=>$(problem_vec[6])); :(p_7=>$(problem_vec[7])); :(p_8=>$(problem_vec[8])); :(p_9=>$(problem_vec[9])); :(p_10=>$(problem_vec[10])); :(p_11=>$(problem_vec[11])); :(p_12=>$(problem_vec[12])); :(p_13=>$(problem_vec[13])); :(p_14=>$(problem_vec[14])); :(p_15=>$(problem_vec[15])); :(p_16=>$(problem_vec[16])); :(p_17=>$(problem_vec[17])); :(p_18=>$(problem_vec[18])); :(p_19=>$(problem_vec[19])); :(p_20=>$(problem_vec[20])); :(p_21=>$(problem_vec[21])); :(p_22=>$(problem_vec[22])); :(p_23=>$(problem_vec[23])); :(p_24=>$(problem_vec[24])); :(p_25=>$(problem_vec[25])); :(p_26=>$(problem_vec[26])); :(p_27=>$(problem_vec[27])); :(p_28=>$(problem_vec[28])); :(p_29=>$(problem_vec[29])); :(p_30=>$(problem_vec[30])); :(p_31=>$(problem_vec[31])); :(p_32=>$(problem_vec[32])); :(p_33=>$(problem_vec[33])); :(p_34=>$(problem_vec[34])); :(p_35=>$(problem_vec[35])); :(p_36=>$(problem_vec[36])); :(p_37=>$(problem_vec[37])); :(p_38=>$(problem_vec[38])); :(p_39=>$(problem_vec[39])); :(p_40=>$(problem_vec[40])); :(p_41=>$(problem_vec[41])); :(p_42=>$(problem_vec[42])); :(p_43=>$(problem_vec[43])); :(p_44=>$(problem_vec[44])); :(p_45=>$(problem_vec[45])); :(p_46=>$(problem_vec[46])); :(p_47=>$(problem_vec[47])); :(p_48=>$(problem_vec[48])); :(p_49=>$(problem_vec[49])); :(p_50=>$(problem_vec[50])); :(p_51=>$(problem_vec[51])); :(p_52=>$(problem_vec[52])); :(p_53=>$(problem_vec[53]))]
	return params
end

function parsePOETsoutput(filename)
	close("all")
	f = open(filename)
	alltext = readall(f)
	close(f)

	outputname = "textparsing.txt"
	number_of_parameters = 46
  	number_of_objectives = 5
	ec_array = zeros(number_of_objectives)
  	pc_array = zeros(number_of_parameters)
	rank_array = zeros(1)	
	counter =1
	for grouping in matchall(r"\[([^]]+)\]", alltext)
		cleanedgrouping = replace(grouping, "[", "")
		nocommas = replace(cleanedgrouping, ","," ")
		allcleaned = replace(nocommas, "]", "")
		allcleaned = replace(allcleaned, ";", "\n")
		outfile = open(outputname, "w")
		write(outfile, allcleaned)
		close(outfile)
		formatted = readdlm(outputname)
		@show formatted	
		@show size(formatted), counter
		if(counter == 1)
			ec_array = [ec_array formatted]
			counter = counter +1
		elseif(counter == 2)
			pc_array = [pc_array formatted]
			counter = counter +1
		elseif(counter == 3)
			rank_array = [rank_array formatted]
			#@show formatted
			counter =1
		end
		
	end
	return ec_array[:,2:end], pc_array[:,2:end], rank_array[:,2:end]
end

function peturbIC(ICvec,seed)
	#peturbIC by 10% of nominal value
	srand(seed)
	selectedindices = [1,3]
	genrand = randn(1, size(ICvec,1))
	for j in selectedindices
		ICvec[j] = ICvec[j]+ICvec[j]*.05*(.5-genrand[j])*2
	end
	return ICvec
end

function setIC(IC, exp_index)
	if(exp_index==2)
		IC[1]= IC[1]*1.55
		#IC[3] =IC[3]*.95
		#IC[5] = IC[5]*.95
		IC[7] = IC[7]*1.5
		IC[8]= IC[8]*1.5
		IC[11] =.01
	elseif(exp_index== 3)
		IC[1]= IC[1]*1.15
		IC[6] = IC[6]*.75
		IC[7] = IC[7]*1.2
		IC[11] = .001
	elseif(exp_index ==4)
		IC[1] = IC[1]*.75
		IC[7] = IC[7]*.95
	elseif(exp_index ==5)
		IC[1] = IC[1]*.65
		IC[7] = IC[7]*.6
	elseif(exp_index ==6)
		IC[1] = IC[1]*.65
		IC[7] = IC[7]*.55
	end
	return IC
end
