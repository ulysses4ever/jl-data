


function back_propagate(neural_network, out, learning_rate)
	# refference at http://halfbakedmaker.org/?p=2411
	# 	first   : calc delta at output nodes
	#   Second  : calc delta at all other nodes
	#   Third   : calc weight changes

	# initalize delta store
	delta_store = Array(Array{Float64,2},length(neural_network.node_state))

	# first step
	delta_store[length(neural_network.node_state)] = -out .* (1 .- neural_network.node_state_probability[length(neural_network.node_state_probability)]) .* neural_network.node_state_probability[length(neural_network.node_state_probability)]
	
	# Second step
	for n = -length(neural_network.node_state)+1:-1
		delta_store[-n] = (1-neural_network.node_state_probability[-n]) .* neural_network.node_state_probability[-n] .* (neural_network.hidden_matrix[-n]' * delta_store[-n+1])
	end

	# Third step
	for n = 1:length(neural_network.hidden_matrix)
		neural_network.hidden_matrix[n] += (-1 * learning_rate * (neural_network.node_state_probability[n] * delta_store[n+1]' )') ./ neural_network.batch_size
	end

	

end
