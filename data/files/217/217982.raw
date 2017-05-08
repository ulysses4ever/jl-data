function used_memory()
    int(Sys.total_memory()) - int(Sys.free_memory())
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
    min_time = min(env.clock_resolution * 1000, 0.1)
    
    test_time, test_iter, _ = run_for_atleast(min_time, 1, bench.run)
    @printf("ran %d iterations in %s\n", test_iter, time_str(test_time))
    
    new_iters = int(ceil(min_time * test_iter / test_time))

    #sample_count <- config
    sample_count = 1000
    
    gc_time = @elapsed Base.gc()

    est_time = sample_count * new_iters * test_time * bench.ntimes / test_iter
    est_time = force_gc ? est_time + (new_iters * sample_count  * gc_time) : est_time
    if true || est_time > 5
    	@printf("collecting %d samples, %d iterations each, estimated time %s\n",
	    	sample_count, new_iters, time_str(est_time))
    end

    function run_once()
        bench.run(1)
    end
    
    @printf("\rProgress 0.0%%")
    run_once()
    times = zeros(sample_count)
    time_begin = time_sec()
    for sample in 1:sample_count
        progress = int((sample / sample_count) * 100)
        if progress % 10 == 0
 		time_now = time_sec()
    		diff = time_now - time_begin
		to_go = (diff * (100.0 / progress)) - diff
		if to_go > 1
                    @printf("\rprogress %d%%  |  time remaining %s",
                            progress, time_str(to_go))
                end 
        end 
        t = timed_noresult(run_once, int(new_iters))
        times[sample] = (t - env.clock_cost) / new_iters
        if force_gc
            Base.gc()
        end
    end
    @printf("\rprogress %d%%  |  time remaining %s\n",
	    100, "0.00000 s")
    return times
end

function report_benchmark(desc::String, est::Estimate)
    @printf("%s: %s, lb %s, ub %s, ci %.3f\n",
            desc, time_str(est.point), time_str(est.lbound),
            time_str(est.ubound), est.confidence_level)
end 

function report_outlier_variance(outvar::OutlierVariance)
    effect_str = (e::OutlierEffect) ->
	if     typeof(e) == Severe     "severely inflated"
	elseif typeof(e) == Moderate   "moderately inflated"
        elseif typeof(e) == Slight     "slightly inflated"
        elseif typeof(e) == Unaffected "unaffected"
        end
    @printf("variance introduced by outliers: %.3f%%\n", outvar.frac)
    @printf("variance is %s by outliers\n", effect_str(outvar.effect))
end
     
function run_analyze_one(env::Environment, desc::String, bench::Benchmark)
    times = run_benchmark(env, bench, true) 
    # ci <- get config item
    # num_resamples <- get config item
    tail_quantile = 0.025
    n_resamples = 1000
    @printf("analyzing with %d resamples...\n", n_resamples)
    analysis = analyze_sample(times, tail_quantile, n_resamples)
    report_benchmark("mean ", analysis.mean)
    report_benchmark("stdev", analysis.std)
    outliers = classify_outliers(times)
    note_outliers(outliers)
    report_outlier_variance(analysis.outlier_variance)
    (times, analysis, outliers)
end
