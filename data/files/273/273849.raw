using SpatialCorrelation
using Distances
using Base.Test

# fix parameter values
σ² = 1.0
ϕ = 1.0
ν = 1.0

## test small symmetric distance matrices
x = linspace(0., 1., 10)
s = hcat([[a, b] for a in x, b in x]...)
D = pairwise(Euclidean(), s)

Σexp = exponential(D, σ², ϕ)
Σmat = matern(D, σ², ϕ, ν)
Σsph = spherical(D, σ², ϕ)

@test issym(Σexp)
@test isposdef(Σexp)
@test issym(Σmat)
@test isposdef(Σmat)
@test issym(Σsph)
@test isposdef(Σsph)

## test large symmetric distance matrices
x = linspace(0., 1., 50)
s = hcat([[a, b] for a in x, b in x]...)
D = pairwise(Euclidean(), s)

Σexp = exponential(D, σ², ϕ)
Σmat = matern(D, σ², ϕ, ν)
Σsph = spherical(D, σ², ϕ)

@test issym(Σexp)
@test isposdef(Σexp)
@test issym(Σmat)
@test isposdef(Σmat)
@test issym(Σsph)
@test isposdef(Σsph)

## test small asymmetric distance matrices
x1 = linspace(0., 1., 10)
y1 = linspace(0., 1., 10)
x2 = linspace(1., 2., 20)
y2 = linspace(1., 2., 20)
s1 = hcat([[a, b] for a in x1, b in y1]...)
s2 = hcat([[a, b] for a in x2, b in y2]...)
n = size(s1, 2)
m = size(s2, 2)
D = fill(0.0, n, m)
for j = 1:m, i = 1:n
  D[i, j] = Distances.euclidean(vec(s1[:, i]), vec(s2[:, j]))
end

Σexp = exponential(D, σ², ϕ)
Σmat = matern(D, σ², ϕ, ν)
Σsph = spherical(D, σ², ϕ)

##
##  add tests here
##

## test large asymmetric distance matrices
x1 = linspace(0., 1., 50)
y1 = linspace(0., 1., 50)
x2 = linspace(1., 2., 75)
y2 = linspace(1., 2., 75)
s1 = hcat([[a, b] for a in x1, b in y1]...)
s2 = hcat([[a, b] for a in x2, b in y2]...)
n = size(s1, 2)
m = size(s2, 2)
D = fill(0.0, n, m)
for j = 1:m, i = 1:n
  D[i, j] = Distances.euclidean(vec(s1[:, i]), vec(s2[:, j]))
end

Σexp = exponential(D, σ², ϕ)
Σmat = matern(D, σ², ϕ, ν)
Σsph = spherical(D, σ², ϕ)

##
##  add tests here
##
