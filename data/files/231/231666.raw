function multiGauss(Σ, X, μ)
  n = length(μ)
  Xμ = X - μ
  k = sqrt((2*π)^n * det(Σ))
  power = (Xμ' * inv(Σ) * Xμ)[1]
  return convert(Float64, exp(-0.5 * power) / k)
end

Σ  = eye(2)
x1 = [0.2, 1.3]
x2 = [2.2, -1.3]
u  = [0, 1]
multiGauss(Σ, x1, u)
multiGauss(Σ, x2, u)

typeof(Σ)

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



function distribution(a::NormalDistribution, X)
  return multiGauss(a.Σ, X, a.μ)
end

distribution(NormalDistribution(eye(2), u), x1)

nd = NormalDistribution(Σ, u)
nd.Σ


###################################################
μ1 = [1, 1]
μ2 = [3, 3]
Σ1 = Σ2 = eye(2)

type ObjectClass
  name::String # class name
  ω::Float64   # a priori probability
  Φ::NormalDistribution
end

a = ObjectClass("A", 0.5, NormalDistribution(Σ1, μ1))
b = ObjectClass("B", 0.5, NormalDistribution(Σ2, μ2))
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

x = [1.8, 1.8]
bayes(a, b, x)

###############################################

function multivariateNormalRandom(a::NormalDistribution, N=1::Int)
  R = chol(a.Σ)
  z = repmat(a.μ', N, 1) + randn(N, size(a.μ)[1])*R
end

multivariateNormalRandom(nd, 5)

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

multivariateNormalRandom2(nd, 10)

