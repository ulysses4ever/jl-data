function used_memory()
    int(Sys.total_memory()) - int(Sys.free_memory())
end 

function force_gc()
    MAX_GC_ATTEMPTS = 10
    force_gc(MAX_GC_ATTEMPTS)
end

function force_gc(max_attempts::Integer)
    @printf("Forcing GC....")
    used = used_memory()
    attempts = 1
    while true
        Base.gc()
	new_used = used_memory()
        if used > new_used && attempts < max_attempts
            used = new_used
            attempts += 1
	else
	    break
        end
    end
    @printf("Attempts %d\n", attempts)
end 

function final_gc() 
    @printf("Final GC...")
    time_body(force_gc())[1]
end

function benchmark(count, warmup, target_time, func, gc_before)
    force_gc()
    first_execution = @elapsed func()
end     

function run_benchmark(env::Environment, bench::Benchmark, force_gc::Bool)
    
    run_for_atleast(0.1, 10000, time)
    min_time = min(env.clock_res * 1000, 0.1)
    test_time, test_iter, _ = run_for_atleast(min_time, 1, bench.run)
    @printf("ran %d iterations in %s", test_iter, secs(test_time))
    
    new_iters = ceil(min_time * test_iter / test_time)
    #sample_count <- config
    sample_count = 1000
    est_time = (sample_count * new_iters * test_time / test_iter)
    if true || est_time > 5
    	@printf("collecting %d samples, %d iterations each, in estimate %s"
	    	samples_count, new_iters, sec(est_time))
    end
    
    # run the gc to make sure that garbage created by previous
    # benchmarks doesnt affect this benchmark
    Base.gc()
   
    function run_sample()
        for i in 1:new_iters
            bench.run()
        end
    end 

    times = zeros(sample_count)
    for sample in 1:sample_count
        t = timed_noresult(run_sample)
        times[i] = (t - env.clock_cost) / new_iters
	if force_gc
            Base.gc() 
        end
    end
    return times
end
