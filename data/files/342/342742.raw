module TrainTravelers

	using PyPlot

	const N = 20
	const stations = [1:N]

	function plot_analytical()
		s = stations
		plot(s, s/N .* (1 .- s/N))  # see PDF
	end

	function plot_simulated(people::Int)
		plot(stations, simulate(people))
	end

	function plot_simulated_two_popular_stations(people::Int)
		station_weights = ones(Int, N)
		station_weights[int(1/4*N)] = 10
		station_weights[int(3/5*N)] = 7
		plot(stations, simulate(people, station_weights))
	end

	function simulate(people::Int)
		simulate(people, ones(Int, N))
	end

	function simulate(people::Int, station_weights::Vector{Int})
		@assert length(station_weights) == N
		counts = zeros(N)
		for i in 1:people
			s_orig = weighted_choice(station_weights)
			s_dest = weighted_choice(station_weights)
			if s_dest > s_orig
				counts[s_orig:s_dest-1] += 1
			end
		end
		counts / people
	end

	function weighted_choice(weights::Vector{Int})
		r = rand(1:sum(weights))
		for (index, w) in enumerate(weights)
			r -= w
			if r < 1
				return index
			end
		end
	end

end