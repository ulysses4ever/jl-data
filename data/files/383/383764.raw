 using PyCall
@pyimport numpy as np

 @everywhere using Debug

# some global parameters -
BIG = 1e10
SMALL = 1e-9
outputfile = "outputMay31parallel/parameter_array.txt"

# Globally load data so we don't have load on each iteration -
#MEASURED_ARRAY = readdlm("./data/CORRUPTED_MEASUREMENT_SET.dat")

# Evaluates the objective function values -
#@debug function objective_function(parameter_array)


#  # Calculate the objective function array -
#  obj_array = BIG*ones(4,1)

#  # Solve the model with the update parameters -
#  tStart = 0.0;
#  tStop = 100.0;
#  tStep = 0.1;
#  (t,x) = SolveBalances(tStart,tStop,tStep,parameter_array)

#  # Need to interpolate the simulation onto the experimental time scale -
#  number_of_measurements = 10
#  time_experimental = linspace(tStart,tStop,number_of_measurements)
#  AI = np.interp(time_experimental[:],t,x[:,7])
#  BI = np.interp(time_experimental[:],t,x[:,8])
#  CI = np.interp(time_experimental[:],t,x[:,9])
#  XI = np.interp(time_experimental[:],t,x[:,10])

#  # interpolate the e data onto the same timescale -
#  AMI = np.interp(time_experimental[:],MEASURED_ARRAY[:,1],MEASURED_ARRAY[:,2])
#  BMI = np.interp(time_experimental[:],MEASURED_ARRAY[:,1],MEASURED_ARRAY[:,3])
#  CMI = np.interp(time_experimental[:],MEASURED_ARRAY[:,1],MEASURED_ARRAY[:,4])
#  XMI = np.interp(time_experimental[:],MEASURED_ARRAY[:,1],MEASURED_ARRAY[:,5])

#  # Compute the error values -
#  error_A = (AMI - AI)
#  error_B = (BMI - BI)
#  error_C = (CMI - CI)
#  error_X = (XMI - XI)

#  # Compute the objective array -
#  obj_array[1,1] = (transpose(error_A)*error_A)[1]
#  obj_array[2,1] = (transpose(error_B)*error_B)[1]
#  obj_array[3,1] = (transpose(error_C)*error_C)[1]
#  obj_array[4,1] = (transpose(error_X)*error_X)[1]

#  # return -
#  return obj_array
#end

# Generates new parameter array, given current array -
function neighbor_function(parameter_array)
	@show parameter_array
	f = open(outputfile, "a")
	write(f,string(parameter_array, "\n"))
	close(f)
	

  SIGMA = 0.05
  number_of_parameters = length(parameter_array)

  # calculate new parameters -
  new_parameter_array = parameter_array.*(1+SIGMA*randn(number_of_parameters))

  # Check the bound constraints -
  LOWER_BOUND = SMALL
  UPPER_BOUND = 500

  # return the corrected parameter arrays -
  return parameter_bounds_function(new_parameter_array,LOWER_BOUND*ones(number_of_parameters),UPPER_BOUND*ones(number_of_parameters))
end

function acceptance_probability_function(rank_array,temperature)
  return (exp(-rank_array[end]/temperature))
end

function cooling_function(temperature)

  # define my new temperature -
  alpha = 0.9
  return alpha*temperature
end

function faster_cooling_function(temperature)
	alpha = .5
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
