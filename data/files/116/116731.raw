

function random_search(func, size, num_trys)

	best = fill(0.0, num_trys)
	test = randbool(size)
	store = 0.0
	best[1] = func(test);
	for n=2:num_trys
		test = randbool(size)
		store = func(test);
		best[n] = best[n-1];
		if (store > best[n-1])
			best[n] = store;
		end
	end
	return best
end

function average_random_search(func, size, num_trys, trials)

	total = fill(0.0, num_trys)
	for n = 1:trials
		total = total + random_search(func, size, num_trys);
	end
	return total/trials
end



