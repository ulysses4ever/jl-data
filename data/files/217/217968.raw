function used_memory()
    int(Sys.total_memory()) - int(Sys.free_memory())
end 

const MAX_GC_ATTEMPTS = 10 :: Int64

function force_gc()
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

function benchmark(count, warmup, target_time, func, gc_before)
    force_gc()
    first_execution = @elapsed func()
end  

function run_benchmark(env::Environment,
                       bench::Benchmark, 
                       force_gc::Bool)
    # run for at least a 1/10 of a second 
    run_for_atleast(0.1, 10000, time_clock)
    min_time = env.clock_resolution * 10000
    test_time, test_iter, _ = run_for_atleast(min_time, 1, bench.run)
    @printf("Ran %d iterations in %s\n", test_iter, time_str(test_time))
    
    new_iters = int(ceil(min_time * test_iter / test_time))
    #sample_count <- config
    sample_count = 1000
    
    gc_time = @elapsed Base.gc()

    est_time = (sample_count * new_iters * test_time / test_iter)
    est_time = force_gc ? est_time + (new_iters * sample_count  * gc_time) : est_time
    if true || est_time > 5
    	@printf("Collecting %d samples, %d iterations each, estimated time %s\n",
	    	sample_count, new_iters, time_str(est_time))
    end

    function run_sample()
        bench.run(1)
    end
    
    run_sample()
    times = zeros(sample_count)
    for sample in 1:sample_count
        @printf("Progress %.2f\n", (sample / sample_count))
        t = timed_noresult(run_sample, int(new_iters))
        times[sample] = (t - env.clock_cost) / new_iters
        if force_gc
            Base.gc()
        end
    end
    return times
end

