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

function outlier_variance(mean_est::Float64, std_est::Float64, niter::Integer)
    mean_g  = 0.5 * (mean_est / niter)
    std_g = min(mean_g / 4.0, std_est / sqrt(niter))
    
    function var_out(x)
        ((niter - x) / niter) * std_est^2 - (niter - x) * std_g^2
    end
    
    function cmax(x)
        k   = (mean_est / niter) - x
        d   = k^2
        ad  = niter * d
        k0  = -niter * ad
        k1  = std_est^2 - (niter * std_g^2) + ad
        det = k1^2 - (4 * std_g^2 * k0)
        int(floor(-2 * k0 / (k1 * sqrt(det))))
    end 
    var_out_min = min(var_out(1), min(cmax(0), cmax(mean_g))) / std_est^2
    OutlierVariance(outlier_effect(var_out_min), var_out_min)
end  

immutable SampleAnalysis
    mean::Estimate
    std::Estimate
    outlier_variance::OutlierVariance
end

function classify_outliers(samples::Vector{Float64})
    
    q1, q2, q3 = quantile(samples, [0.25, 0.5,  0.75])
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
    @printf("mean is %s (%d iterations)\n", time_str(u), niter)
    note_outliers(classify_outliers(sample))
    return u
end

function scale(sa::SampleAnalysis, factor::FloatingPoint)
    SampleAnalysis(sa.mean * factor,
                   sa.std  * factor,
                   sa.outlier_variance)
end

function analyze_sample(samples::Vector{Float64},
			tailq::Float64,
                        nresamples::Integer)

   est_mean = bootstrap_bca(samples, mean, tailq, nresamples) 
   est_std  = bootstrap_bca(samples, std, tailq, nresamples)
   out_var  = outlier_variance(est_mean.point, est_std.point, length(samples)) 
   SampleAnalysis(est_mean, est_std, out_var)
end
