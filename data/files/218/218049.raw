immutable Environment
    clock_resolution::Float64
    clock_cost::Float64
end

Base.print(env::Environment) = let res  = env.clock_resolution
                                   cost = env.clock_cost
	print("Environment(\n  clock_resolution:$res ns\n  clock_cost:$cost ns\n)")
end 

const SEED = 1000 :: Int64

function resolution(k::Integer)
    times = zeros(Float64, k)
    for i in 1:k 
        times[i] = time_sec()
    end
    return nonzeros(times[2:end] - times[1:end-1])
end

function cost(timelimit::Float64)
    
    function time_clock(niter::Integer)
        start = time_sec()
        for _ in 1:niter
            time_sec()
        end
        time_sec() - start
    end 

    time_clock(1)
    (_, iters, elapsed) = run_for_atleast(0.1, SEED, time_clock)
    ntimes = ceil(timelimit / elapsed)
    [time_clock(iters) / iters  for _ in 1:ntimes]
end

function analyze_mean(sample, niter)
    u = mean(sample)
    @printf("mean is %s (%d iterations)\n", time_str(u), length(sample))
    return u
end 

function measure_environment()
    Base.gc()
    @printf("Warming up...\n")
    (_, seed, _) = run_for_atleast(0.1, SEED, resolution)
    Base.gc()
    @printf("Estimating clock resolution...")
    (_, _, tdiffs) = run_for_atleast(0.5, seed, resolution)
    clock_res = analyze_mean(tdiffs)
    @printf("Estimating cost of clock call...")
    time_limit = min(100000.0 * clock_res, 1.0)
    clock_cost = analyze_mean(cost(time_limit))
    return Environment(clock_res, clock_cost)
end
