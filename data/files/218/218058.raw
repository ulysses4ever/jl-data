function timed_result(action::Function)
    start = time()
    result = action()
    end = time()
    delta = end - start
    return delta, result
end


function timed_noresult(action::Function)
    start = time()
    action()
    end = time()
    delta = end - start
    return delta
end


function run_for_atleast(howlong::Int64,
			 seed::Int64,
			 action::Function)
    init_time = time()
    iters = 0
    while true
        if (now - init_time > howlong * 10)
           throw error("took too long to run: seed %d, iters %d")
        end
	elapsed, result = timer(() -> action(seed))
	if elapsed < howlong
	    seed *= 2; iters +=1
   	else
 	    return elapsed, seed, result
	end
     end
end


function secs(k::Float64)

    function fmt(time::Float64, unit::String)
        if     time >= 1e9 return @sprintf("%.4g %s", time, unit)
      	elseif time >= 1e6 return @sprintf("%.0f %s", time, unit)
      	elseif time >= 1e5 return @sprintf("%.1f %s", time, unit)
      	elseif time >= 1e4 return @sprintf("%.2f %s", time, unit)
      	elseif time >= 1e3 return @sprintf("%.3f %s", time, unit)
      	elseif time >= 1e2 return @sprintf("%.4f %s", time, unit)
      	elseif time >= 1e1 return @sprintf("%.5f %s", time, unit)
        else return @sprintf("%.6f %s", time, unit)
    end

  if k < 0 	    return "-" + secs(-k)
  elseif k >= 1     return fmt(k * 1e03, "s")
  elseif k >= 1e-03 return fmt(k * 1e06, "ms")
  elseif k >= 1e-06 return fmt(k * 1e09, "us")
  elseif k >= 1e-09 return fmt(k * 1e12, "ns")
  elseif k >= 1e-12 return fmt(k, "ps")
  else return @sprintf("%g s", k)
  end
end
