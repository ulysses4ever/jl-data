function sock_simulation(num_simulations, num_pairs, num_draws)
	socks = vcat(1:num_pairs, 1:num_pairs)
	num_unique = 0.0
	for i=1:num_simulations
		shuffle!(socks)
		if length(unique(socks[1:num_draws]))==num_draws
			num_unique = num_unique + 1.0
		end
	end
	num_unique / num_simulations
end

for pairs=6:50
	res = sock_simulation(10000, pairs, 11)
	println(@sprintf("%2d pairs: %0.1f%% unique", pairs, res*100))
end
