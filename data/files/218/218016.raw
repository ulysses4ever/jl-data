immutable Outliers
    nsamples    :: Int64
    low_severe  :: Int64
    low_mild    :: Int64
    high_mild   :: Int64
    high_severe :: Int64
        
    function Outliers(n::Int64) 
        @assert n > 0
        new(n, 0, 0, 0, 0)
    end
end


abstract OutlierEffect
immutable Unaffected <: OutlierEffect end
immutable Slight <: OutlierEffect end
immutable Moderate <: OutlierEffect end
immutable Severe <: OutlierEffect end


immutable OutlierVariance
    effect :: OutlierEffect 
    desc   :: String
    frac   :: Float64
end


immutable SampleAnalysis
    mean :: Float64
    std  :: Float64
    outlier_variance :: Float64
end


function classify_outliers(samples::Vector{Float64})
    q1, q2, q3 = quantile(samples, [0.25, 0.50, 0.75])
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
	   o.low_mild + o.high_severe
end


function count_samples(o::Outliers)
    return o.nsamples
end


function note_outliers(o::Outliers)
    frac  = (n) -> 100.0 * (n / o.nsamples)
    check = (k,t,d) -> let fk = frac(k)
			if fk > t
                           @printf(" %d (%.1g%%) %s", k, fk, d)
                        end
                       end
    noutliers = count_outliers(o)
    if noutliers > 0
        @printf("found %d outliers among %d samples (%.1g%%)",
		noutliers, nsamples(o), frac(noutliers))
        check(o.low_severe, 0, "low severe")
        check(o.low_mild, 1, "low mild")
        check(o.high_mild, 1, "high mild")
        check(o.high_severe, 0, "high severe")
    end
end


function analyze_mean(sample::Vector{Float64}, 
		      iters::Int64)
    u = mean(sample)
    @printf("mean is %s (%d iterations)", secs(u), iters)
    note_outliers(classify_outliers(sample))
    return u
end
