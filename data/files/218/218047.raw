immutable Environment
    clock_resolution::Float64
    clock_cost::Float64
end

function resolution(k::Integer)
    times = [time() for _ in 1:k]
    return nonzeros(times[2:end] - times[1:end-1])
end


function cost(timelimit::Float64)
    timeclock = (k) -> timed_noresult(() -> for _ 1:k time() end)
    timeclock(1)
    (_, iters, elapsed) = run_for_atleast(0.01, 10000 timeclock)
    ntimes = ceil(timelimit / elapsed)
    times = [timeclock(iters) for _ in 1:ntimes]
    return times ./ iters 
end


function measure_environment()
    @printf("Warming up...")
    (_, seed, _) = run_for_atleast(0.1, 10000, resolution)
    @printf("Estimating clock resolution...")
    (_, _, tdiffs) = run_for_atleast(0.5, seed, resolution)
    clock_res = analyze_mean(tdiffs)
    @printf("Estimating cost of clock call...")
    time_limit = min(100000.0 * clock_res, 1.0)
    clock_cost = analyze_mean(cost(time_limit))
    return Environment(clock_res, clock_cost)
end
