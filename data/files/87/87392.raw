

module NeuNet


include("logistic_calc.jl")
include("randomize_vector.jl")
include("probabilities_calc.jl")
include("create_neural_network.jl")
include("read_data_MSB.jl")
include("read_data.jl")
include("run_neural_network.jl")
include("back_propagate.jl")
include("run_back_propagate.jl")
include("test_neural_network.jl")	



export #Types
	Nn,	
	Data,
	# functions
	test_neural_network,
	run_back_propagate,
	create_neural_network,
	read_data	

type Nn
	hidden_matrix::Array{Array{Float64,2},1}
	node_state::Array{Array{Float64,2},1}
	node_state_probability::Array{Array{Float64,2},1}
	batch_size::Int
	full_batch::Bool
	Nn(hidden_matrix,node_state,node_state_probability,batch_size,full_batch) = new(hidden_matrix,node_state,node_state_probability,batch_size,full_batch)	
end


type Data
	input_size::Int
	output_size::Int
	data_size::Int
	input::Array{Float64,2}
	output::Array{Float64,2}
end


end # module
