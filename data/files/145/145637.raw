using Distributions: Normal, Multinomial, Binomial, MvNormal
# Useful functions
ess(w) = 1/sum(w.^2)
phi(n, p) = n/p

function resample_idx(p:: Array{Float64}, idx::Array{Int16})
  # Fairly fast function for doing resampling
  n = length(p);
  y = rand(Multinomial(n, p));
  k = 1;
  n_part = 0;
  for i in 1:n
    n_part = y[i];
    for j = 1:n_part
      idx[k] = i;
      k = k+1;
    end
  end
  idx;
end

function reset_weights!(X::Array{Float64}, value::Float64, idx::Int64)
  # Resets the weights in a row of a matrix to the value given in value. Operates in place
  for i = 1:length(X[idx,:])
    X[idx, i] = value
  end
end

γ = 0.5 #ESS threshold
N = 1000 #number of particles
p = 100 # Annealing steps π_n(x) ∝ [π(x)]^ϕ_n [μ_1(x)]^(1-ϕ_n)   0 ≤ ϕ_1 ≤ ... ≤ ϕ_p = 1
q = Normal(0, 1) # Proposal Distribution
xs = zeros(Float64, p, N) # particles
w = zeros(Float64, p, N) # weights
essi = zeros(Float64, p) # ESS values

# SMC Algorithm
# INITIALIZATION
n = 1;
# sample particles initial distribution
xs[n, :] = rand(q,N);
# compute log weights for numerical stability
lw[n, :] = log(q) - lop(p);
idx = zeros(Int16, N);
while true
  # RESAMPLING
  essi[n]=ess(w[n,:]);
  if essi[n] < N*γ # Gamma is set above to 0.5 by default
    idx = resample_idx(w, idx);
    xs[n, :] = xs[n, idx];
    reset_weights!(w, 1/N, n);
  end
  n = n + 1;
  if n == p+1
    break;
  end
end
