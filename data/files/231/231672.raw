######### exercise 2.1

function multiGauss(Σ, X, μ)
  n = length(μ)
  Xμ = X - μ
  k = sqrt((2*π)^n * det(Σ))
  power = (Xμ' * inv(Σ) * Xμ)[1]
  return convert(Float64, exp(-0.5 * power) / k)
end

Σ  = eye(2)
u  = [0, 1]

x1 = [0.2, 1.3]
multiGauss(Σ, x1, u)

x2 = [2.2, -1.3]
multiGauss(Σ, x2, u)

type NormalDistribution
  Σ::Matrix # covariance matrix
  μ::Vector # mean vector
end

function density(a::NormalDistribution, X::Vector)
  n = length(a.μ)
  Xμ = X - a.μ
  k = sqrt((2*π)^n * det(a.Σ))
  power = (Xμ' * inv(a.Σ) * Xμ)[1]
  return convert(Float64, exp(-0.5 * power) / k)
end

density(NormalDistribution(Σ, u), x1)
density(NormalDistribution(Σ, u), x2)


function distribution(a::NormalDistribution, X)
  return multiGauss(a.Σ, X, a.μ)
end

distribution(NormalDistribution(eye(2), u), x1)

nd = NormalDistribution(Σ, u)
nd.Σ


###################################################
### exercise 2.2
μ1 = [1, 1]
μ2 = [3, 3]
Σ1 = Σ2 = eye(2)

type ObjectClass
  name::String # class name
  ω::Float64   # a priori probability
  Φ::NormalDistribution
end

function bayes(a::ObjectClass, b::ObjectClass, x)
  to_a = density(a.Φ, x) * a.ω
  to_b = density(b.Φ, x) * b.ω

  its_a = to_a / (to_a + to_b)
  its_b = to_b / (to_b + to_a)

  print_with_color(:red, "A=")
  println(its_a)
  print_with_color(:green, "B=")
  println(its_b)

  if its_a > its_b
    return a.name
  elseif its_b > its_a
    return b.name
  else
    return "equal"
  end
end

a = ObjectClass("A", 0.5, NormalDistribution(Σ1, μ1))
b = ObjectClass("B", 0.5, NormalDistribution(Σ2, μ2))
x = [1.8, 1.8]
bayes(a, b, x)

###############################################
# exercise 2.3
function normrnd(μ, σ)
  u = v = s = 0
  while s >= 1 || s == 0
    u = rand() * 2.0 - 1.0
    v = rand() * 2.0 - 1.0
    s = u * u + v * v
  end
  return μ + σ * u * sqrt(-2.0 * log(s) / s)
end

function normrnd(μ, σ, N::Int)
  [normrnd(μ, σ) for i in range(1,N)]
end

function normrnd(μ, σ, N::Int, M::Int)
  map(x -> normrnd(μ, σ), zeros(N, M))
end

μ=0.0
σ=1
v = normrnd(μ, σ, 130)
w = normrnd(μ, σ, 2, 5)

function singlevariableNormalRandom(μ, σ, N=1::Int)
  rep(μ, N, 1) + randn(N, 1)*σ
end

normrnd(mu,sigma,m,n)

normrnd(0.5, 0.1)

singlevariableNormalRandom(0.5, 1.0, 10)


###############################################
# exercise 2.4

function multivariateNormalRandom(a::NormalDistribution, N=1::Int)
  R = chol(a.Σ)
  z = repmat(a.μ', N, 1) + randn(N, size(a.μ)[1])*R
end

multivariateNormalRandom(nd, 5)
vec(multivariateNormalRandom(nd, 1))

function boxmuller()
  U1 = rand()
  U2 = rand()
  return sqrt(-2.0 * log(U1)) .* cos(2*π*U2)
end

boxmuller()

function boxmuller(N, K)
  reshape([boxmuller() for i in 1:N*K], N, K)
end

bm = boxmuller(10,2)
show(bm)
randn(10, 2)
boxmuller(10, 2)

function multivariateNormalRandom2(a::NormalDistribution, N=1::Int)
  R = chol(a.Σ)
  repmat(a.μ', N, 1) + boxmuller(N, size(a.μ)[1]) * R
end

multivariateNormalRandom2(nd, 5)

###################################################
## exercise 2.5
function getLabel(Ω)
  r = rand()
  label = 0
  for value in Ω
    label += 1
    if value > r
      break
    end
  end
  return label
end

function toMatrix(foo)
  flat(A) = mapreduce(x->isa(x,Array)? flat(x): x, vcat, A)
  reshape(flat(foo), length(foo[1]), length(foo))'
end

function generateData(N::Int, ω::Vector, nd::Vector{NormalDistribution})
  cummulativeProbability = cumsum(ω[1:end])
  y = [ getLabel(cummulativeProbability) for i in 1:N]
  X = map(label -> vec(multivariateNormalRandom(nd[label], 1)), y)
  return toMatrix(X), vec(y)
end

ω = vec([0.5 0.5])
distributions = vec([NormalDistribution(Σ1, μ1), NormalDistribution(Σ2, μ2)])
X, y = generateData(10, ω, distributions)
