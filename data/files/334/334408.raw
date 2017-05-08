using SpatialCorrelation
using Distances

ns = 10
s = hcat(linspace(1, 10, 10), linspace(1, 10, 10))
d = fill(0.0, ns, ns)
for j = 1:ns, i = 1:ns
  d[i, j] = Distances.euclidean(vec(s[i, :]), vec(s[j, :]))
end

σ² = 4
ϕ = 2
Σ = exponential(d, σ², ϕ)

ν = 0.7
Σmat = matern(d, σ², ν, ϕ)
