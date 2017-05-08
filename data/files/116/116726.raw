using Cd

function RBM_search(func, size_x, size_y, num_trys, learning_rate)

	# rbm stuff
	weight_matrix = .1 * (rand(Float64, size_y, size_x)) - .05; 
	momentum_speed = fill(0.0, size(weight_matrix));
	
	# search variables
	best = fill(0.0, num_trys)
	test_y = randbool(size_y,1);
	test_x = hidden_to_visible_state(test_y, weight_matrix);
#	print(size(test_x), "\n");
	store = 0.0
	best[1] = func(test_x);

	# runs on hope and a prayer
	for n=2:num_trys
		test_y = randbool(size_y, 1)
		test_x = hidden_to_visible_state(test_y, weight_matrix);
#		print(maximum(weight_matrix), "\n");
#		print(minimum(weight_matrix), "\n");
		store = func(test_x);
		best[n] = best[n-1];
		if (store >= best[n-1])
			best[n] = store;
			gradient = cd_gradient(test_x, weight_matrix);
			momentum_speed = .9 * momentum_speed + gradient;
			weight_matrix += momentum_speed * learning_rate;
		end
	end

	return best
end




function RBM_search_adv(func, size_x, size_y, num_trys, learning_rate)

	# rbm stuff
	weight_matrix = .1 * (rand(Float64, size_y, size_x)) - .05; 
	momentum_speed = fill(0.0, size(weight_matrix));
	
	# search variables
	best = fill(0.0, num_trys)
	test_y = randbool(size_y,1);
	test_x = hidden_to_visible_state(test_y, weight_matrix);
#	print(size(test_x), "\n");
	store = 0.0
	best[1] = func(test_x);
	average = best[1];

	# runs on hope and a prayer
	for n=2:num_trys
		test_y = randbool(size_y, 1)
		test_x = hidden_to_visible_state(test_y, weight_matrix);
#		print(maximum(weight_matrix), "\n");
#		print(minimum(weight_matrix), "\n");
		store = func(test_x);
		average = (average + store)/2
		best[n] = best[n-1];
		if (store >= best[n-1])
			best[n] = store;
		end
		if (store/average > 1.5)
			gradient = cd_gradient(test_x, weight_matrix);
			momentum_speed = .9 * momentum_speed + gradient;
			weight_matrix += momentum_speed * learning_rate;
		end
	end

	return best
end

# Next try 
function RBM_search_hope(func, size_x, size_y, num_trys, learning_rate)

	# rbm stuff
	weight_matrix = .1 * (rand(Float64, size_x, size_y)) - .05; 
	momentum_speed = fill(0.0, size(weight_matrix));
	
	# search variables
	best = fill(0.0, num_trys)
	test_y = randbool(size_y,1);
	test_x = visible_to_hidden_state(test_y, weight_matrix);
#	print(size(test_x), "\n");
	store = 0.0
	best[1] = func(test_x);
	average = best[1];

	# runs on hope and a prayer
	for n=2:num_trys
		test_y = randbool(size_y, 1)
		test_x = visible_to_hidden_state(test_y, weight_matrix);
#		print(maximum(weight_matrix), "\n");
#		print(minimum(weight_matrix), "\n");
		store = func(test_x);
		best[n] = best[n-1];
		if (store >= best[n-1])
			best[n] = store;
			# now for the learning
			gradient = gradient_special(test_y, test_x, weight_matrix);
#			print(size(gradient), "\n");
			momentum_speed = .9 * momentum_speed + gradient;
			weight_matrix += momentum_speed * learning_rate;
		end
	end

	return best
end

function gradient_special(test_y, test_x, weight_matrix)
	# calc visible state from hidden state
	visible_batch_2 = hidden_to_visible_state(test_x, weight_matrix);
	# calc hidden probability from visible state
	hidden_probability_2 = visible_to_hidden_probability(visible_batch_2, weight_matrix);
	
	# gradien calc
	gradient = (goodness_gradient(test_y, test_x) - goodness_gradient(visible_batch_2, hidden_probability_2));

	return gradient'
end


function average_RBM_search(func, size_x, size_y, num_trys, learning_rate, trials)

	total = fill(0.0, num_trys)
	for n = 1:trials
		total = total + RBM_search(func, size_x, size_y, num_trys, learning_rate);
	end
	return total/trials
end

function average_RBM_search_adv(func, size_x, size_y, num_trys, learning_rate, trials)

	total = fill(0.0, num_trys)
	for n = 1:trials
		total = total + RBM_search_adv(func, size_x, size_y, num_trys, learning_rate);
	end
	return total/trials
end

function average_RBM_search_hope(func, size_x, size_y, num_trys, learning_rate, trials)

	total = fill(0.0, num_trys)
	for n = 1:trials
		total = total + RBM_search_hope(func, size_x, size_y, num_trys, learning_rate);
	end
	return total/trials
end





