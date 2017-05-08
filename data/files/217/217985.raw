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


