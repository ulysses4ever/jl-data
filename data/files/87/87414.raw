
function percent_error(node_state, output)
	output_store = rand_vector_from_probabilities(output)
	error = 0.0
	for n = 1:size(output,2)
		if (~(node_state[:,n] == output[:,n]))
			error += 1.0
		end
	end
	return error / size(output,2)
end

function test_neural_network(network,data)
	#run the network on the data once with binary output
	
	# set node probability on input
	network.node_state_probability[1] = data.input
	
	# determine node state of input   (needless step in some cases)
	network.node_state[1] = rand_vector_from_probabilities(data.input)
	# determin state of rest of nodes
	for n = 1:length(network.hidden_matrix)
		network.node_state[n+1], network.node_state_probability[n+1] = run_neural_network_layer(network.hidden_matrix[n],network.node_state[n])
	end

	# find squared error and return that as well as output - data_output
	return percent_error(network.node_state[length(network.node_state)], data.output)


end
