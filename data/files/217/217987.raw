function uniform_dist(max_val::Float64)
    int(rand() * max_val)
end

function sample_uniform(n::Integer, max_val::Float64)
    [1 + uniform_dist(max_val - 1) for _ in 1:n]
end

function sample(x)
    n = length(x)
    samples = sample_uniform(n, n)
    return [x[i] for i in samples]
end

function bootstrap-sample(data, stat, size)
    [stat(sort(sample data)) for _ in 1:size]
end 

function confidence_interval(mean, variance)
    n_sigma = 1.96
    delta = n_sigma * sqrt(variance)
    (mean - delta, mean + delta)
end 

function bootstrap_estimate(sampled_stat)
    u = mean(sampled_stat)
    v = var(sampled_stat)
    (u, s, confidence_interval(u, v))
end

function scale_bootstrap_est(est, scale)
    (est[1] * scale, [e * scale for e in est[end]])
end

function normal_cdf(x)
    0.5 * 1.0 + erf(x / sqrt(2.0))
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
