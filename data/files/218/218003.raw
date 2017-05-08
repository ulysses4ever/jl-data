immutable Estimate
    point  :: Float64
    lbound :: Float64
    ubound :: Float64
    confidence_level :: Float64

    function Estimate {T<:Real} (pt::T, lb::T, ub::T, cl::T)
        @assert lb <= ub
        @assert cl > 0 && cl < 1
        return new(float64(pt), float64(lb), 
	           float64(ub), float64(cl))
    end
end

function uniform_dist(max_val::Real)
    rand() * max_val
end

function sample_uniform{T<:Integer}(::Type{T}, n::Integer, max_val::T)
    [1 + int(uniform_dist(max_val - 1)) for _ in 1:n]
end

function sample_uniform{T<:FloatingPoint}(::Type{T}, n::Integer, max_val::T)
    [1 + uniform_dist(max_val - 1) for _ in 1:n]
end

function sample{T<:Real}(x::Vector{T})
    n = length(x)
    @assert n > 0
    samples = Array(T, n)
    if n == 1
        samples[1] = x[1]
    elseif n == 2
        # pick pair with replacement
        ridx1 = (rand() < 0.5) ? 1 : 2
        ridx2 = (rand() < 0.5) ? 1 : 2
        samples[1] = x[ridx1]
        samples[2] = x[ridx2]
    else
        # sample with replacement
        for s in 1:n
            ridx = int(round(1 + rand() * (n - 1))) 
            samples[s] = x[ridx]
        end
    end 
    return samples
end

function bootstrap_sample{T<:Real}(data::Vector{T},
				   stat::Function,
				   nsamples::Integer)
    samples = Array(T, nsamples)
    for idx in 1:nsamples
        samples[idx] = stat(sample(data))
    end
    return samples
end 

function confidence_interval(mean::Float64,
			     variance::Float64)
    delta = 1.96 * sqrt(variance)
    (mean - delta, mean + delta)
end 

function normal_cdf(x::Float64)
    0.5 * (1.0 + erf(x / sqrt(2.0)))
end

function normal_quantile(x::Float64)
    
    a = [2509.0809287301226727, 
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

    function polynomial_value(x, coeff)
        fcoeff = coeff[1]
        lcoeff = coeff[2:end]
        reduce((x1, x2) -> (x * x1 + x2), coeff[1], coeff[2:end])
    end
    
    if 0.075 <= x <= 0.925
        v = x - 0.5
        r = 180625e-6 - v^2
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
            pf = polynomial_value(r, f)
            return sign(x - 0.5) * (pe / pf)
        end
    end 
end

function jacknife{T<:Real}(data::Vector{T},
			   stat::Function)
    n = length(data)
    samples = Array(Float64, n)
    sample_data = Array(T, n-1)
    for i in 1:n
        idx = 0
        for j in 1:n
            if j != i
                idx += 1
                sample_data[idx] = data[i]
            end
        end
        samples[i] = stat(sample_data)
    end
    return samples
end 

function bootstrap_percentile{T<:Real}(data::Vector{T},
				       statistic::Function,
				       alpha::Float64,
				       nsamples::Integer)
    @assert nsamples > 0 && alpha > 0.0
    n = length(data)
    boot_samples = bootstrap_sample(data, statistic, nsamples)
    sort!(boot_samples)
    idx_L = int(round(nsamples * alpha/2.0))
    idx_U = int(round(nsamples * (1.0 - alpha/2.0)))
    ci_L = boot_samples[idx_L]
    ci_U = boot_samples[idx_U]
    return (ci_L, ci_U)
end 

function bootstrap_bca{T<:Float64}(data::Vector{T}, 
			           statistic::Function,
				   alpha::Float64, 
				   nsamples::Integer)
    @assert nsamples > 0 && alpha > 0.0  && alpha < 1.0
    
    n = length(data)
    ci = 1.0 - (2.0 * alpha)
    
    boot_samples = bootstrap_sample(data, statistic, nsamples)
    est = statistic(data)
    z0 = normal_quantile(sum(boot_samples .< est) / nsamples)

    jack_samples = jacknife(data, statistic)
    jack_mean = mean(jack_samples)

    jack_dev = jack_samples - jack_mean
    jack_dev = Array(Float64, n)
   
    neps = 0
    for i in 1:length(jack_dev)
        d = jack_samples[i] - jack_mean
        if isapprox(d, 0.0)
            neps += 1
        end
        jack_dev[i] = d
    end
   
    # special case when all numbers are exactly the same or within fp tolerance
    if neps == length(jack_dev)
        return Estimate(jack_mean, jack_mean, jack_mean, ci)
    end
    
    a = sum((jack_dev .^ 3) / (6.0 * sum((jack_dev) .^ 2) ^ 1.5))
    #zL = z0 - normal_quantile((1.0 - alpha) / 2.0)
    #zU = z0 + normal_quantile((1.0 - alpha) / 2.0)
 
    #aL = normal_cdf(z0 + zL / (1.0 - a * zL))
    #aU = normal_cdf(z0 + zU / (1.0 - a * zU))
    
    #a_cdf = (zalpha) -> normal_cdf(z0 + (z0 + zalpha) / (1.0 - a * (z0 + zalpha)))
    
    aL = normal_cdf(z0 + (z0 + alpha) / (1.0 - a * (z0 + alpha)))
    aM = normal_cdf(z0 + (z0 + 0.5) / (1.0 - a * (z0 + 0.5)))
    aU = normal_cdf(z0 + (z0 + (1.0 - alpha)) / (1.0 - a * (z0 + (1.0 - alpha))))
    
    sort!(boot_samples)
    idxL = int(round(nsamples * aL))
    idxM = int(round(nsamples * aM))
    idxU = int(round(nsamples * aU))

    ciL = boot_samples[idxL]
    med = boot_samples[idxM]
    ciU = boot_samples[idxU]
    
    return Estimate(med, ciL, ciU, ci)
end 


function scale_estimate(est::Estimate, factor::Real)
    return Estimate(factor * est.point,
	            factor * est.lbound,
		    factor * est.ubound,
		    est.confidence_level)
end 

function scale_bootstrap_estimate(est::(Float64, Float64),
				  scale::Float64)
    (est[1] * scale, est[2] * scale)
end 

function model_estimation_const(h_k::Float64,
				samp_var::Float64)
    @assert samp_var != 0.0
    sqrt(1.0 + h_k^2 / samp_var)
end 

function smoothed_sample{T<:Float64}(c_k::T, h_k::T,
			             data::Vector{T},
			             deviates::Vector{T})
    [c_k * (d + h_k * dev) for d in data, dev in deviates]
end 

function gaussian_weight(t::Float64)
    k = sqrt(2.0 * pi)
    k * exp(t^2  / -2.0)
end 

function kernel_density_est(h::Float64, K::Function,
		        n::Float64, X::Float64, x::Float64)
    reduce((a,b) -> (a + K((x - b) / h)), 0, X) / (n * h)
end 
