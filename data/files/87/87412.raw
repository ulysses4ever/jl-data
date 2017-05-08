function rand_input(data, batch_size)
	#returns random mini batch
	
	run_input = Array(Float64, data.input_size, batch_size)
	run_output = Array(Float64, data.output_size, batch_size)
	#rand generator	
	for n = 1:batch_size
			#k = 2
			k = mod(rand(Int),size(data.input,2))+1
			run_input[:,n] = data.input[:,k]
			run_output[:,n] = data.output[:,k]
	end
	return run_input, run_output
end

function run_neural_network_layer(hidden_matrix, node_state)
	node_state_probability = logistic_calc(hidden_matrix * node_state)
	node_state_after = rand_vector_from_probabilities(node_state_probability)
	return node_state_after, node_state_probability
end

function squared_error(first, second)
	return sum((first-second).^2)
end

function run_neural_network(network,data)
	#run the network on the data once with batch size given by the network
	#returns error of based on probability to last node
	
	# make input to network
	if (network.full_batch)
		run_input = data.input	   #this should just copy a pointer
		run_output = data.output   #so it should be very fast 
	else
		run_input, run_output = rand_input(data, network.batch_size);
	end
	# set node probability on input
	network.node_state_probability[1] = run_input
	# determine node state of input   (needless step in some cases)
	network.node_state[1] = rand_vector_from_probabilities(run_input)
	# determin state of rest of nodes
	for n = 1:length(network.hidden_matrix)
		network.node_state[n+1], network.node_state_probability[n+1] = run_neural_network_layer(network.hidden_matrix[n],network.node_state[n])
	end

	# find squared error and return that as well as output - data_output
	return squared_error(network.node_state_probability[length(network.node_state_probability)], run_output) / network.batch_size, (run_output - network.node_state_probability[length(network.node_state_probability)])


end

