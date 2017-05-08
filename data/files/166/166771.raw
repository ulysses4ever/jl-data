function pretty_print_chromosome(chromosome, tree_depth, data_class_map)
	chromosome_string = ""
	max_width = 2^(tree_depth - 1)
	parents = null
	for i in 1:tree_depth
		if i == 1
			parents = Array(Integer, 1)
			parents[1] = 1
		end
		children = Array(Integer, 2^i)
		node_string = "\t"
		splitter_string = "\t"
		first_seps = ((i == 1) ? "" : "\t")
		second_seps = ((i == 1) ? "" : "\t")
		for j in 1:2^(i - 1)
			tab_sum = 0
			for k in 1:(tree_depth - i + 1)
				tab_sum = (tab_sum + 2^(k - 1))
			end
			tab_sum = ((tab_sum == 1) ? 0 : ((tab_sum - 1) / 2))
			for k in 1:tab_sum
				node_string = string(node_string, "\t")
				splitter_string = string(splitter_string, "\t")
				first_seps = string(first_seps, (((j == 1) || (mod(j, 2) == 1)) ? "\t" : "____"))
				second_seps = string(second_seps, "\t")
			end
			number_string = ((i == tree_depth) ? string(" ", data_class_map[integer(chromosome[parents[j]])]) : integer(chromosome[parents[j]]))
			splitter_value = round(chromosome[parents[j] + 1] * 100)
			if ((i == tree_depth) || (number_string < 1000))
				number_string = string(number_string, "\t")
			end
			node_string = string(node_string, number_string)
			splitter_string = string(splitter_string, (splitter_value / 100), ((mod(splitter_value, 10) == 0) ? "\t" : ""))
			first_seps = string(first_seps, ((mod(j, 2) == 1) ? "   _" : "_   "))
			second_seps = string(second_seps, ((mod(j, 2) == 1) ? "  / " : " \\  "))
			for k in 1:(tab_sum)
				node_string = string(node_string, "\t")
				splitter_string = string(splitter_string, "\t")
				first_seps = string(first_seps, (((j == 2^(i - 1)) || (mod(j, 2) == 0)) ? "\t" : "____"))
				second_seps = string(second_seps, "\t")
			end
			node_string = string(node_string, "\t")
			splitter_string = string(splitter_string, "\t")
			first_seps = string(first_seps, ((mod(j, 2) == 1) ? "_/\\_" : "\t"))
			second_seps = string(second_seps, "\t")
			children[2 * j - 1] = (parents[j] + 2)
			extra_children = 2
			for k in 1:(tree_depth - i)
				extra_children += (2 * (2 ^ (k - 1)))
			end
			children[2 * j] = (parents[j] + extra_children)
		end
		chromosome_string = string(chromosome_string, ((i == 1) ? "" : first_seps), "\n", ((i == 1) ? "" : second_seps), "\n", node_string, "\n", ((i == tree_depth) ? "" : splitter_string), "\n")
		parents = children
	end
	return chromosome_string
end

function build_tree(node, current_depth, tree_depth)
	if current_depth < tree_depth
		node[1] = Array(Any, 2)
		node[2] = Array(Any, 2)	
		build_tree(node[1], current_depth + 1, tree_depth)
		build_tree(node[2], current_depth + 1, tree_depth)
	else
		node[1] = Array(Any, 0)
		node[2] = Array(Any, 0)
	end
end

function traverse_tree(node, chromo_space, number_of_classes, number_of_attrs)
	index = 0
	for i in 1:(length(chromo_space) * 2)
		if chromo_space[i] == 0
			index = i
			break
		end
	end
	if length(node[1]) != 0
		chromo_space[index] = float64(mod(rand(Int), number_of_attrs) + 1)
		chromo_space[index + 1] = rand(Float64)
		traverse_tree(node[1], chromo_space, number_of_classes, number_of_attrs)
		traverse_tree(node[2], chromo_space, number_of_classes, number_of_attrs)
	else
		chromo_space[index] = float64(mod(rand(Int), number_of_classes) + 1)
		chromo_space[index + 1] = rand(Float64)
	end
end

function craft_population(number_of_classes, number_of_attrs, tree_depth, population_size)
	chromosome_size = 0
	for i in 1:tree_depth
		chromosome_size += (2 * (2 ^ (i - 1)))
	end
	population = Array(Any, population_size)
	if tree_depth > 1
		tree_mold = Array(Any, 2)
		build_tree(tree_mold, 1, tree_depth)
	else
		tree_mold = Array(Any, 0)
	end
	for i in 1:population_size
		population[i] = zeros(Float64, chromosome_size)
		traverse_tree(tree_mold, population[i], number_of_classes, number_of_attrs)
	end
	return population
end 

function traverse_mock_tree(node, chromo_space)
	index = 0
	for i in 1:(length(chromo_space) * 2)
		if chromo_space[i] == "0"
			index = i
			break
		end
	end
	if length(node[1]) != 0
		chromo_space[index] = "n"
		chromo_space[index + 1] = "v"
		traverse_mock_tree(node[1], chromo_space)
		traverse_mock_tree(node[2], chromo_space)
	else
		chromo_space[index] = "l"
		chromo_space[index + 1] = "v"
	end
end

function craft_mock_chromo(tree_depth)
	chromosome_size = 0
	for i in 1:tree_depth
		chromosome_size += (2 * (2 ^ (i - 1)))
	end
	mock_tree = Array(String, chromosome_size)
	if tree_depth > 1
		tree_mold = Array(Any, 2)
		build_tree(tree_mold, 1, tree_depth)
	else
		tree_mold = Array(Any, 0)
	end
	mock_tree = Array(String, chromosome_size)
	fill!(mock_tree, "0")
	traverse_mock_tree(tree_mold, mock_tree)
	return mock_tree
end

function evaluate_fitnesses(data_class_map, training_data_attrs, training_data_class, population, population_size, tree_depth)
	fitnesses = Array(Float64, population_size)
	for i in 1:population_size
		correctly_classified = 0
		for k in 1:length(training_data_class)
			current_index = 1
			for j in 1:(tree_depth - 1)
				if training_data_attrs[k,integer(population[i][current_index])] < population[i][current_index + 1]
					current_index += 2
				else
					current_index += (2 * (2 ^ (tree_depth - j)))
				end
			end
			if data_class_map[integer(population[i][current_index])] == training_data_class[k]
				correctly_classified += 1
			end
		end
		fitnesses[i] = (correctly_classified / length(training_data_class))
	end
	return fitnesses
end

function crossover(population, aggregated_fitnesses, fitnesses, population_size, size_of_elite)
	chromosome_size = 0
	for i in 1:tree_depth
		chromosome_size += 2 ^ (i - 1)
	end
	new_pop = Array(Any, population_size)
	fill!(new_pop, Array(Float64, 0))
	elite_fitnesses = zeros(Float64, size_of_elite)
	for i in 1:population_size
		for j in 1:size_of_elite
			if fitnesses[i] >= elite_fitnesses[j]
				if j < size_of_elite
					elite_fitnesses[j + 1] = elite_fitnesses[j]
					new_pop[j + 1] = new_pop[j]
				end
				elite_fitnesses[j] = fitnesses[i]
				new_pop[j] = population[i]
				break
			end
		end
	end
	for i in 1:div((population_size - size_of_elite), 2)
		roll = rand()
		first_one = null
		second_one = null
		for j in 1:population_size
			if roll <= aggregated_fitnesses[j] || j == population_size
				first_one = population[j]
				break
			end
		end
		roll = rand()
		for j in 1:population_size
			if roll <= aggregated_fitnesses[j] || j == population_size
				second_one = population[j]
				break
			end
		end
		roll = mod(rand(Int), (length(first_one) - 1)) + 1
		tmp_one = Array(Float64, length(first_one))
		tmp_two = Array(Float64, length(first_one))
		for j in 1:length(first_one)
			if j <= roll
				tmp_one[j] = first_one[j]
				tmp_two[j] = second_one[j]
			else
				tmp_one[j] = second_one[j]
				tmp_two[j] = first_one[j]
			end
		end
		new_pop[size_of_elite + (i * 2) - 1] = tmp_one
		new_pop[size_of_elite + (i * 2)] = tmp_two
	end
	if (mod((population_size - size_of_elite), 2) == 1)
		roll = rand()
		first_one = null
		second_one = null
		for j in 1:population_size
			if roll <= aggregated_fitnesses[j] || j == population_size
				first_one = population[j]
				break
			end
		end
		roll = rand()
		for j in 1:population_size
			if roll <= aggregated_fitnesses[j] || j == population_size
				second_one = population[j]
				break
			end
		end
		roll = mod(rand(Int), (length(first_one) - 1)) + 1
		tmp_one = Array(Float64, length(first_one))
		for j in 1:length(first_one)
			if j <= roll
				tmp_one[j] = first_one[j]
			else
				tmp_one[j] = second_one[j]
			end
		end
		new_pop[population_size] = tmp_one
	end
	return new_pop
end

function mutate!(population, mut_odds, number_of_classes, number_of_attrs, mock_chromo)
	for i in 1:length(population), j in 1:length(population[i])
		if rand() > mut_odds
			if mock_chromo[j] == "n"
				population[i][j] = mod(rand(Int), number_of_attrs) + 1
			elseif mock_chromo[j] == "l"
				population[i][j] = mod(rand(Int), number_of_classes) + 1
			else 
				population[i][j] = rand(Float64)
			end
		end
	end
end

function aggregate_fitnesses(fitnesses)
	tmp_fitnesses = Array(Float64, length(fitnesses))
	sum = 0
	for i in 1:length(fitnesses)
		sum += fitnesses[i]
		tmp_fitnesses[i] = sum
	end
	for i in 1:length(fitnesses)
		tmp_fitnesses[i] = (tmp_fitnesses[i] / sum)
	end
	return tmp_fitnesses
end

function do_vote(data_class_map, test_data_attrs, test_data_class, ensemble, ensemble_size, tree_depth, generation_counter)
	classified_as = zeros(Integer, length(data_class_map), length(data_class_map))
	correctly_classified = 0
	for k in 1:length(test_data_class)
		votes = zeros(Integer, length(data_class_map))	
		for i in 1:ensemble_size
			current_index = 1
			for j in 1:(tree_depth - 1)
				if test_data_attrs[k,integer(ensemble[i][current_index])] < ensemble[i][current_index + 1]
					current_index += 2
				else
					current_index += (2 * (2 ^ (tree_depth - j)))
				end
			end
			votes[integer(ensemble[i][current_index])] += 1
		end
		chosen_index = 0
		max_votes = 0
		for m in 1:length(data_class_map)
			if votes[m] > max_votes
				chosen_index = m
				max_votes = votes[m]
			end
		end
		real_index = 0
		for m in 1:length(data_class_map)
			if data_class_map[m] == test_data_class[k]
				real_index = m
				break
			end
		end
		classified_as[chosen_index,real_index] = classified_as[chosen_index,real_index] + 1
		if data_class_map[chosen_index] == test_data_class[k]
			correctly_classified += 1
		end
	end
	return {
		"ensemble" => ensemble,
		"classified_as" => classified_as,
		"percentage" => (correctly_classified / length(test_data_class)),
		"iters" => generation_counter
	}
end

function make_ensemble(population, fitnesses, ensemble_size, population_size)
	ensemble = Array(Any, ensemble_size)
	fill!(ensemble, Array(Float64, 0))
	ensemble_fitnesses = zeros(Float64, ensemble_size)
	for i in 1:population_size
		for j in 1:ensemble_size
			if fitnesses[i] > ensemble_fitnesses[j]
				if j != ensemble_size
					ensemble_fitnesses[j + 1] = ensemble_fitnesses[j]
					ensemble[j + 1] = ensemble[j]
				end
				ensemble_fitnesses[j] = fitnesses[i]
				ensemble[j] = population[i]
				break
			end
		end
	end
	return ensemble
end

function run(data_class_map, training_data_attrs, training_data_class, test_data_attrs, test_data_class, mut_odds, ensemble_size, population_size, tree_depth, min_growth, min_growth_iters, size_of_elite)
	tic()
	counter = 0
	generation_counter = 0
	max_fitness = 0
	population = craft_population(size(data_class_map)[1], size(training_data_attrs)[2], tree_depth, population_size)
	fitnesses = evaluate_fitnesses(data_class_map, training_data_attrs, training_data_class, population, population_size, tree_depth)
	mock_chromo = craft_mock_chromo(tree_depth)
	while counter < min_growth_iters
		generation_counter += 1
		aggregated_fitnesses = aggregate_fitnesses(fitnesses)
		population = crossover(population, aggregated_fitnesses, fitnesses, population_size, size_of_elite)
		mutate!(population, mut_odds, size(data_class_map)[1], size(training_data_attrs)[2], mock_chromo)
		fitnesses = evaluate_fitnesses(data_class_map, training_data_attrs, training_data_class, population, population_size, tree_depth)
		if ((maximum(fitnesses) / max_fitness) > min_growth)
			counter = 0
			max_fitness = maximum(fitnesses)
		else
			counter += 1
		end
	end
	ensemble = make_ensemble(population, fitnesses, ensemble_size, population_size)
	return do_vote(data_class_map, test_data_attrs, test_data_class, ensemble, ensemble_size, tree_depth, generation_counter)
end