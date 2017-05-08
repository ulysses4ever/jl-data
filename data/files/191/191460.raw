function test(len::Int)
	rng = MersenneTwister(0)
	x= Set{Int}()
	sum = 0
	for i in 1:len
		push!(x, rand(rng, Int))
	end
	tic()
	for i in 1:len
		if (∈(i, x))
			sum += 1
		end
	end
	toc()
	println(sum)
end
