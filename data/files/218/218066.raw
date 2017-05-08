function time_sec()
    time_ns() * 1e-9
end

function timed_result(action::Function, seed::Int64)
    start = time_sec()
    result = action(seed)
    delta = time_sec() - start
    return (delta, result)
end

function timed_noresult(action::Function, seed::Int64)
    start = time_sec()
    for _ in 1:seed
        action()
    end
    time_sec() - start
end


function run_for_atleast(howlong::Float64,
			 seed::Int64,
			 action::Function)
    init_time = time_sec()
    iters = 0
    while true
        now = time_sec()
        if ((now - init_time) > (howlong * 10))
           throw(error("took too long to run: seed $seed, iters $iters"))
        end
	elapsed, result = timed_result(action, seed)
	if elapsed < howlong
	    seed  *= 2
     	    iters += 1
   	else
 	    return elapsed, seed, result
	end
     end
end


function timed_func(func::Function, n::Integer)
    start = time_ns()
    local ret
    for _ in 1:n
	ret = func()
    end
    (int(time_ns() - start), 1.0)
end


function collect_samples(sample_count::Integer,
			 exec_count::Integer, 
			 func::Function,
			 gc_before::Bool)
    @assert sample_count > 0
    results = zeros(sample_count)
    times = zeros(sample_count)
    for i in 1:sample_count
        if gc_before
	    Base.gc()
	end
        t, r = timed_func(func, exec_count)
        times[i] = t;
        results[i] = r 
    end
    (times, results)
end

function s_to_ns(x)
    x * 1e9
end 

function ns_to_s(x)
    x * 1e-9
end 

function estimate_execution_count(period, func, 
			          gc_before_sample,
				  est_run_time)
    print("Estimating execution count...")
    n = int(max(period / est_run_time / 5, 1))
    while true
        times = collect_samples(1, n, func, gc_before_sample)[1]
        t = max(1.0, mean(times)) # prevent zero times 
   	print("....")
        if t >= period
            print("\n")
            return n
        end
        n = min(2 * n, n * (period / t) + 1)
    end 
    @printf("%d\n", n)
    return n
end

function fmt(time::Float64, unit::String)
    local str::String
    if time >= 1e9     str = @sprintf("%.4f %s", time, unit)
    elseif time >= 1e6 str = @sprintf("%.0f %s", time, unit)
    elseif time >= 1e5 str = @sprintf("%.1f %s", time, unit)
    elseif time >= 1e4 str = @sprintf("%.2f %s", time, unit)
    elseif time >= 1e3 str = @sprintf("%.3f %s", time, unit)
    elseif time >= 1e2 str = @sprintf("%.4f %s", time, unit)
    elseif time >= 1e1 str = @sprintf("%.5f %s", time, unit)
    else str =  @sprintf("%.6f %s", time, unit)
    end
    return str
end

function time_str(k::Float64)

    function fmt(time::Float64, unit::String)
        if     time >= 1e9 return @sprintf("%.4f %s", time, unit)
        elseif time >= 1e6 return @sprintf("%.0f %s", time, unit)
        elseif time >= 1e5 return @sprintf("%.1f %s", time, unit)
        elseif time >= 1e4 return @sprintf("%.2f %s", time, unit)
        elseif time >= 1e3 return @sprintf("%.3f %s", time, unit)
        elseif time >= 1e2 return @sprintf("%.4f %s", time, unit)
        elseif time >= 1e1 return @sprintf("%.5f %s", time, unit)
        else return @sprintf("%.6f %s", time, unit) end 
    end

    if k < 0          return "-" + secs(-k)
    elseif k >= 1     return fmt(k, "s")
    elseif k >= 1e-03 return fmt(k * 1e03, "ms")
    elseif k >= 1e-06 return fmt(k * 1e06, "us")
    elseif k >= 1e-09 return fmt(k * 1e09, "ns")
    elseif k >= 1e-12 return fmt(k * 1e12, "ps")
    else return @sprintf("%.6f %s", k * 1e12, "ps")
    end
end
