
function create_weight_matrix(row,columbe)
	return .1*(rand(row,columbe)-.5)

end


function create_neural_network(data, hidden_layers, batch_size=data.data_size)
	# we need the weight matrixes and allocate space for node states

	#------------------creates the array of weight matrixes---------------
	#input to hidden layer
	store = Array[create_weight_matrix(hidden_layers[1],data.input_size)];
	#hidden to hidden layers
	for n = 1:length(hidden_layers)-1
		push!(store,create_weight_matrix(hidden_layers[n+1],hidden_layers[n]));
	end
	#hidden to output layer
	push!(store,create_weight_matrix(data.output_size,hidden_layers[length(hidden_layers)]));
	

	#-----------------creates the array of node states and probability node states
	#input states
	store_node = Array[fill(0.0,data.input_size,batch_size)];	
	store_node_probability = Array[fill(0.0,data.input_size,batch_size)];
	#hidden states
	for n = 1:length(hidden_layers)
		push!(store_node,fill(0.0,hidden_layers[n],batch_size));
		push!(store_node_probability,fill(0.0,hidden_layers[n],batch_size));
	end
	#output states	
	push!(store_node,fill(0.0,data.output_size,batch_size));	
	push!(store_node_probability,fill(0.0,data.output_size,batch_size));	

	# make and return the neural network with true if your useing the entire batch
	if (batch_size == data.data_size)
		return Nn(store,store_node,store_node_probability,batch_size,true)
	else 
		return Nn(store,store_node,store_node_probability,batch_size,false)
	end
end




