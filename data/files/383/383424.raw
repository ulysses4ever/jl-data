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
	#@show size(predictedThrobin), size(interpolatedExperimentalData)
	sum = 0.0
	for j in collect(1:size(predictedThrobin,1))
		sum = sum +(predictedThrobin[j]-interpolatedExperimentalData[j])^2
	end
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
	kinetic_parameter_vector = vector[1:16]
	control_parameter_vector=vector[17:36]
	platelet_parameter_vector=vector[37:42]
	timing = vector[43:44]
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
  UPPER_BOUND = 3.0

  # return the corrected parameter arrays -
  return parameter_bounds_function(new_parameter_array,LOWER_BOUND*ones(number_of_parameters),UPPER_BOUND*ones(number_of_parameters))
end

function acceptance_probability_function(rank_array,temperature)
  return (exp(-rank_array[end]/temperature))
end

function cooling_function(temperature)

  # define my new temperature -
  alpha = 0.9
	#@show temperature
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
