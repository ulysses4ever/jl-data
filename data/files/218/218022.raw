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


function outlier_effect(var_outlier::Float64)
    if     var_outlier < 0.01 return Unaffected()
    elseif var_outlier < 0.10 return Slight()
    elseif var_outlier < 0.50 return Moderate()
    else return Severe()
    end 
end 


immutable OutlierVariance
    effect :: OutlierEffect 
    desc   :: String
    frac   :: Float64
end


function outlier_significance(mean_est::Float64,
			      var_est::Float64, 
			      n::Integer)
    @printf("Checking outlier significance\n")
    mean_block = mean_est
    var_block  = var_est
    std_block  = sqrt(var_block)
    mean_act = mean_block / n
    mean_g_min = mean_act / 2.0
    sigma_g = min((mean_g_min / 4.0), (std_block / sqrt(n)))
    var_g = sigma_g ^ 2
    c_max = (t_min) -> let j0 = mean_act - t_min
                           k0 = -1.0 * n^2 * j0^2
                           k1 = var_block + -1.0 * n * var_g + (n * j0^2)
                           det = k1^2 - (4 * var_g * k0)
                       floor( -2.0 * k0 / (k1 + sqrt(det)))
                       end
    var_out = (c) -> let nmc = n - c
                     (nmc / n) * (var_block - (nmc * var_g))
                     end 
    min_f = (f q r) -> min(f(q), f(r))
    min_f(var_out, 1, min-f(c_max, 0, mean_g_min)) / var_block
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

function normal_cdf(x::Float64) 
    0.5 * (1.0 + erf(x / sqrt(2.0)))
end

function normal_quantile(x)
    
    let a = [2509.0809287301226727, 
	     33430.575583588128105, 
	     67265.770927008700853,
	     45921.953931549871457, 
	     13731.693765509461125,
   	     1971.5909503065514427,
	     133.14166789178437745,
	     3.3871328727963666080]
        b = [5226.4952788528545610,
	     28729.085735721942674,
	     39307.895800092710610,
	     21213.794301586595867,
	     5394.1960214247511077,
	     687.18700749205790830,
	     42.313330701600911252,
	     1.0]
        c = [0.000774545014278341407640,
	     0.0227238449892691845833,
	     0.241780725177450611770,
	     1.27045825245236838258,
	     3.64784832476320460504,
	     5.76949722146069140550,
	     4.63033784615654529590,
	     1.42343711074968357734]
  	d = [1.05075007164441684324e-9,
	     0.000547593808499534494600,
	     0.0151986665636164571966,
             0.148103976427480074590,
	     0.689767334985100004550,
	     1.67638483018380384940,
	     2.05319162663775882187,
	     1.0]
        e = [2.01033439929228813265e-7,
	     0.0000271155556874348757815,
	     0.00124266094738807843860,
	     0.0265321895265761230930,
	     0.296560571828504891230,
	     1.78482653991729133580,
	     5.46378491116411436990,
	     6.6579046435011037772]
	f = [2.04426310338993978564e-15,
	     1.42151175831644588870e-7,
	     1.84631831751005468180e-5,
	     0.000786869131145613259100,
	     0.0148753612908506148525,
	     0.136929880922735805310,
	     0.599832206555887937690,
	     1.0]
	end

    function polynomial_value(x, coeff)
        fcoeff = coeff[1]
        lcoeff = coeff[2:end]
        reduce((x1, x2) -> (x * x1 + x2), coeff[1], coeff[2:end])
    end
    
    if 0.75 <= x <= 0.95
        v = x - 0.5
        r = 180625e-6 * v^2
  	pa = polynomial_value(r, a)
        pb = polynomial_value(r, b)
        return v * (pa / pb)
    else
        r = (x < 0.5) ? x : 1.0 - x
        r = sqrt(-log(r))
        if r <= 0.5
            r = r - (16.0 / 10.0)
            pc = polynomial_value(r, c)
            pd = polynomial_value(r, d)
            return sign(x - 0.5) * (pc / pd)
        else
            r = r - 5.0
            pe = polynomial_value(r, e)
            pc = polynomial_value(r, f)
            return sign(x - 0.5) * (pe / pc) 
end

function drop_at(arr::Vector{Float64}, n::Integer)
    @assert 1 <= n <= length(arr)
    vcat(arr[1:n-1], arr[n+1:end])
end

function jacknife(data, stat)
    map((n) -> stat(drop_at(data, n)), [1:length(data)])
end 

function bca_nonparametric_eval(n, size, data, z_alpha, estimate, sample, jack_samples)
    z0 = normal_quantile(sum(estimate .> samples) / size)
    jack_mean = mean(jack_samples)
    jack_dev = jack_samples - jack_mean
    acc = sum(jack_dev.^3) / (6.0 * sum(sqrt(jack_dev))^1.5)
    tt =  [normal_cdf(z0 + (z0 + x) / (1.0 - (acc * (z0 + x)))) for x in z_alpha]
    ooo = [trunc(x * size) for x in tt]
    sorted_samples = sort(samples)
    confpoints = [sorted_samples[i] for i in ooo]
    (confpoints, z0, acc, jack_mean, jack_samples)
end

function bca_nonparametric(data, statistic, size, alpha)
    n = length(data)
    data = sort(data)
    estimate = statistic(data)
    samples = bootstrap_sample(data, statistic, size)
    jack_samps = jacknife(data, statistic)
    alpha = isa(alpha, Vector) ? alpha : [alpha]
    z_alpha = [normal_quantile(a) for a in alpha]
    if isa(a, Vector)
      map((est, samp, jksamp) ->
	      bca_nonparametric_eval(n, size, data, z_alpha, est, samp, jksamp),
	   estimate, samples, jack_samples)
    else
        bca_nonparametric_eval(n, size, data, z_alpha,
			       estimate, samples, jack_samples)
    end 
end 


function bca_to_estimate(alpha, bca_estimate)
    (bca_estimate[1][1], bca_estimate[2][1])
end


function model_estimation_const(h_k, samp_var)
    sqrt(1.0 + h_k^2 / samp_var)
end 

function smoothed_sample(c_k, h_k, data, deviates]
    [c_k * (d + h_k * dev) for d in data, dev in deviates]
end 

function gaussian_weight(t)
    k = (2.0 * pi) ^ 0.5
    k * exp(t^2  / -2.0)
end 

defn kernel_density_est(h K n X x)
    reduce((a,b) -> (a + K((x - b) / h)), 0, X) / (n * h)
end 
