immutable Outliers
    nsamples    :: Int64
    low_severe  :: Int64
    low_mild    :: Int64
    high_mild   :: Int64
    high_severe :: Int64
    
    function Outliers(nsamples::Int64,
		      low_severe::Int64, low_mild::Int64,
		      high_mild::Int64, high_severe::Int64)
        new(nsamples, low_severe, low_mild,
	    high_mild, high_severe)
    end 

    function Outliers(n::Int64) 
        @assert n > 0
    end
end

abstract OutlierEffect
immutable Unaffected <: OutlierEffect end
immutable Slight <: OutlierEffect end
immutable Moderate <: OutlierEffect end
immutable Severe <: OutlierEffect end

function outlier_effect(var_outlier::Float64)
    if     var_outlier < 0.01 return Unaffected()
    elseif var_outlier < 0.10 return Slight()
    elseif var_outlier < 0.50 return Moderate()
    else return Severe()
    end 
end 

immutable OutlierVariance
    effect :: OutlierEffect 
    frac   :: Float64
end

function outlier_significance(mean_est::Float64,
			      var_est::Float64, 
			      niter::Integer)
    @printf("Checking outlier significance\n")
    std_est  = sqrt(var_est)
    mean_act = mean_est / niter
    mean_g_min = mean_act / 2.0
    sigma_g = min((mean_g_min / 4.0), (std_est / sqrt(niter)))
    var_g = sigma_g ^ 2
    c_max = (t_min) -> let j0 = mean_act - t_min
                           k0 = -1.0 * niter^2 * j0^2
                           k1 = var_est + -1.0 * niter * var_g + (niter * j0^2)
                           det = k1^2 - (4 * var_g * k0)
                       floor( -2.0 * k0 / (k1 + sqrt(det)))
                       end
    var_out = (c) -> let nmc = niter - c
                     (nmc / niter) * (var_est - (nmc * var_g))
                     end 
    min_f = (f, q, r) -> min(f(q), f(r))
    var_out_min = min_f(var_out, 1, min_f(c_max, 0, mean_g_min)) / var_est
    
    return OutlierVariance(outlier_effect(var_out_min),
			   var_out_min)
end


immutable SampleAnalysis
    mean::Float64
    std::Float64
    outlier_variance::Float64
end

function classify_outliers(samples::Vector{Float64})
    
    q1, q3 = quantile(samples, [0.25, 0.75])
    iqr = q3 - q1
    loS = q1 - (iqr * 3.0)
    loM = q1 - (iqr * 1.5)
    hiM = q3 + (iqr * 1.5)
    hiS = q3 + (iqr * 3.0)

    nsamples = length(samples)
    low_severe = 0
    low_mild = 0
    high_mild = 0
    high_severe = 0 
    
    for s in samples
        if s <= loS && s < hiM
            low_severe += 1
        elseif s > loS && s <= loM
            low_mild += 1
        elseif s >= hiM && s < hiS
            high_mild += 1
        elseif s >= hiS && s > loM
            high_severe += 1
	end
    end
    return Outliers(nsamples,
		    low_severe, 
		    low_mild,
		    high_mild,
		    high_severe)
end


function count_outliers(o::Outliers)
    return o.low_severe + o.low_mild + 
	   o.high_mild + o.high_severe
end


function count_samples(o::Outliers)
    return o.nsamples
end


function note_outliers(o::Outliers)
    frac  = (n) -> 100.0 * (n / o.nsamples)
    check = (k,t,d) -> let fk = frac(k)
			if fk > t
                           @printf(" %d (%.1f%%) %s\n", k, fk, d)
                        end
                       end
    noutliers = count_outliers(o)
    if noutliers > 0
        @printf("found %d outliers among %d samples (%.1f%%)\n",
		noutliers, o.nsamples, frac(noutliers))
        check(o.low_severe, 0, "low severe")
        check(o.low_mild, 1, "low mild")
        check(o.high_mild, 1, "high mild")
        check(o.high_severe, 0, "high severe")
    end
end

function analyze_mean(sample::Vector{Float64}, niter::Integer)
    u = mean(sample)
    @printf("mean is %s (%d iterations)\n", time_str(u), niters)
    note_outliers(classify_outliers(sample))
    return u
end


