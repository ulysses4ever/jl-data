module MathUtils

export log_sum_exp
function log_sum_exp(logs)
  maxlog = maximum(logs)
  return maxlog + log(sum(exp(logs - maxlog)))
end

export sample_discrete
function sample_discrete(dist)
  r = rand()
  s = 0.
  for i=1:length(dist)
    s += dist[i]
    if r <= s
      return(i)
    end
  end
  return(length(dist))
end

export sample_discrete_logspace
function sample_discrete_logspace(log_unnormalized_dist)
  n = length(log_unnormalized_dist)
  logsum = log_sum_exp(log_unnormalized_dist)
  logr = log(rand())
  logc = log_unnormalized_dist[1] - logsum
  for i=1:n-1
    if logr <= logc
      return i
    end
    logp = log_unnormalized_dist[i+1] - logsum
    if logp > logc
      logc = logp + log1p(exp(logc - logp))
    else
      logc = logc + log1p(exp(logp - logc))
    end
  end
  return(n)
end

export normalize_log_dist
function normalize_log_dist(d)
  d - log_sum_exp(d)
end

export is_valid_dist
function is_valid_dist(dist)
  abs(sum(dist) - 1.0) <= eps(1.0) && minimum(dist) >= 0.0
end

export importance_sample
function importance_sample(π, q, n)
  assert(length(π) == length(q))
  assert(is_valid_dist(π))
  assert(is_valid_dist(q))
  p = zeros(length(π))
  counts = zeros(length(π))
  for i=1:n
    x = sample_discrete(q)
    p[x] += (1.0 / n) * π[x] / q[x]
    counts[x] += 1
  end
  p, counts
end

end # module
