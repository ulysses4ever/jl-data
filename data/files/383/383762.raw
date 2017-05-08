# Estimates model parameters for proof-of-concept biochemical model -
using POETs
include("hcmem_lib.jl")

function test_biochemical_model()

  number_of_subdivisions = 10
  number_of_parameters = 13
  number_of_objectives = 4

  initial_parameter_array = zeros(13)
  ec_array = zeros(number_of_objectives)
  pc_array = zeros(number_of_parameters)
  for index in collect(1:number_of_subdivisions)

    # Grab a starting point -
    initial_parameter_array[1:6]  = ones(6).*(1+0.25*randn(6))
    initial_parameter_array[7:12] = 2*ones(6).*(1+0.25*randn(6))
    initial_parameter_array[13] = (1+0.25*randn())

    # Run JuPOETs -
    (EC,PC,RA) = estimate_ensemble(objective_function,neighbor_function,acceptance_probability_function,cooling_function,initial_parameter_array;rank_cutoff=4,maximum_number_of_iterations=10,show_trace=true)

    # Package -
    ec_array = [ec_array EC]
    pc_array = [pc_array PC]
  end

  return (ec_array,pc_array)
end
