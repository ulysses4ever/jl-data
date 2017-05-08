
function run_back_propagate(neural_network,data, number_of_times, learning_rate = 1.0)
	# run back_prop to get lower error

	for n=1:number_of_times
		error, out = run_neural_network(neural_network,data)
		back_propagate(neural_network, out, learning_rate)
		#println(error);
	end


end

