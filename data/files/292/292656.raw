function initPrior(OLS)
  αμ = 0.0
  ασ = sqrt(5)
  βμ = OLS.β
  βσ = sqrt(5)
  λμ = log(OLS.σ^2)
  λσ = 4.0
  aμ = 0.0
  aσ = 10.0
  bμ = 0.5
  bσ = 10.0
  cμ = 0.0
  cσ = 10.0
  dμ = 0.5
  dσ = 10.0
  σβ2a = 2.1
  σβ2b = 1(σβ2a - 1)
  σλ2a = 1e-6
  σλ2b = 1e-6
  Prior = Prior_type(αμ,ασ,βμ,βσ,λμ,λσ,
                     aμ,aσ,bμ,bσ,cμ,cσ,dμ,dσ,
                     σβ2a,σβ2b,σλ2a,σλ2b)
  return(Prior)
end

function initPara()
  # global const
  M = 3
  N = 1000
  T = 1040
  n_stocks = 2878
  burnin = N/2
  Para = Para_type(M,N,T,n_stocks,burnin)
  return(Para)
end

function getOLS(one_stock_ALV::Vector{Float64},mkt_related::Vector{Float64})
  n = length(one_stock_ALV)

  data = DataFrame(Y = one_stock_ALV,X = mkt_related)
  OLS = lm(Y~X,data)
  (α,β) = coef(OLS)
  σ = sqrt(sum(residuals(OLS).^2)/(n-2))

  OLS = OLS_type(α,β,σ)
  return(OLS)
end


function initMC(Prior::Prior_type,OLS::OLS_type,nALV::Int64)
  β = fill(OLS.β,nALV)
  λ = 5rand(nALV)
  α = fill(OLS.α,nALV)
  a = 0
  b = 1
  c = rand(Normal(Prior.cμ,Prior.cσ))
  d = rand(Truncated(Normal(Prior.dμ,Prior.dσ),0,1))
  σβ2 = rand()
  σλ2 = 10rand()

  MC_current = MC_current_type(β,λ,α,a,b,c,d,σβ2,σλ2)
  return(MC_current)
end

function conv2FFBS_type(one_stock_ALV::Vector{Float64},mkt_related::Vector{Float64},
                        MC_current::MC_current_type,Prior::Prior_type)
  y = one_stock_ALV
  α = MC_current.α
  F = mkt_related
  V = exp(MC_current.λ)
  γ = MC_current.a
  G = MC_current.b
  W = MC_current.σβ2
  a1 = Prior.βμ
  R1 = Prior.βσ^2

  FFBS_input = FFBS_type(y,α,F,V,γ,G,W,a1,R1)
  return(FFBS_input)
end

function conv2SV_type(one_stock_ALV::Vector{Float64},mkt_related::Vector{Float64},
                        MC_current::MC_current_type,Prior::Prior_type)
  y = one_stock_ALV - MC_current.β .* mkt_related - MC_current.α
  λ = MC_current.λ
  γ = MC_current.c
  G = MC_current.d
  W = MC_current.σλ2
  a1 = Prior.λμ
  R1 = Prior.λσ^2

  SV_input = SV_type(y,λ,γ,G,W,a1,R1)
  return(SV_input)
end

function FFBS(FFBS_input)
  # y(t) ~ N(α(t) + θ(t)F(t),V(t))
  # θ(t) ~ N(γ + G*θ(t-1),W)
  y = FFBS_input.y
  α = FFBS_input.α
  F = FFBS_input.F
  V = FFBS_input.V
  γ = FFBS_input.γ
  G = FFBS_input.G
  W = FFBS_input.W
  a1 = FFBS_input.a1
  R1 = FFBS_input.R1

  n = length(FFBS_input.y)
  a = zeros(Float64,n)
  R = zeros(Float64,n)
  m = zeros(Float64,n)
  C = zeros(Float64,n)
  A = zeros(Float64,n)
  Q = zeros(Float64,n)
  f = zeros(Float64,n)
  B = zeros(Float64,n-1)
  H = zeros(Float64,n-1)

  # time t = 1
  a[1] = a1
  R[1] = R1
  f[1] = α[1] + F[1]*a[1]
  Q[1] = R[1]*F[1]^2+V[1]
  A[1] = R[1]*F[1]/Q[1]
  m[1] = a[1]+A[1]*(y[1]-f[1])
  C[1] = max(R[1]-Q[1]*A[1]^2,0)

  for t in 2:n
    a[t] = γ + G*m[t-1]
    R[t] = C[t-1]*G^2 + W
    f[t] = α[t] + F[t]*a[t]
    Q[t] = R[t]*F[t]^2+V[t]
    A[t] = R[t]*F[t]/Q[t]
    m[t] = a[t]+A[t]*(y[t]-f[t])
    C[t] = max(R[t]-Q[t]*A[t]^2,0)

    if R[t]-Q[t]*A[t]^2 < -10e-6
      error("Variance is negative")
    end

    B[t-1] = C[t-1]*G/R[t]
    H[t-1] = sqrt(max(C[t-1]-R[t]*B[t-1]^2,0)) # this may go negative because round error

    if C[t-1]-R[t]*B[t-1]^2 < -10e-6
      error("Variance is negative")
    end

  end

  # draw theta
  theta = zeros(Float64,n)
  theta[n] = rand(Normal(m[n],sqrt(C[n])))

  for t = (n-1):-1:1
    theta[t] = rand(Normal(m[t]+B[t]*(theta[t+1]-a[t+1]),H[t]))
  end

  return theta, m
end

function sample_z(y::Float64,μ::Vector{Float64},σ::Vector{Float64},q::Vector{Float64})
  n = length(μ)
  density_vec = zeros(Float64,n)
  for i = 1:n
    d = Normal(μ[i],σ[i])
    density_vec[i] = pdf(d,y)
  end
  w = density_vec .* q
  if sum(w) == 0
    return(rand(DiscreteUniform(1,n)))
  else
    return(rand(Categorical(w./sum(w))))
  end
end

function SV(SV_input::SV_type)
  y = SV_input.y
  λ = SV_input.λ
  γ = SV_input.γ
  G = SV_input.G
  W = SV_input.W
  a1 = SV_input.a1
  R1 = SV_input.R1

  n = length(y)

  μ = [-11.40039,-5.24321,-9.83726,1.50746,-0.65098,0.52478,-2.35859]
  σ2 = [5.795960,2.613690,5.179500,0.167350,0.640090,0.340230,1.262610]
  q = [0.007300,0.105560,0.000020,0.043950,0.340010,0.245660,0.257500]

  if sum(y==0)>5
    error("Too many perfect fit on observation level.")
  end

  y = log(y.^2)
  σ = sqrt(σ2)
  z = zeros(Int64,n)
  for i = 1:n
    z[i] = sample_z(y[i]-λ[i],μ,σ,q)
  end

  y = y
  α = μ[z]
  F = ones(Float64,n)
  V = σ2[z]

  FFBS_input = FFBS_type(y,α,F,V,γ,G,W,a1,R1)

  (theta,) = FFBS(FFBS_input)

  return(theta)
end

function posNormal(Prμ::Float64,Prσ::Float64,LKμ::Float64,LKσ2::Float64,n::Float64)
  Posσ2 = 1/(Prσ^(-2) + LKσ2^(-1)*n)
  Posσ =  sqrt(Posσ2)
  Posμ = Posσ2 * (Prμ * Prσ^(-2) + LKμ * LKσ2^(-1))

  return(Normal(Posμ,Posσ))
end

function sample_α(one_stock_ALV::Vector{Float64},mkt_related::Vector{Float64},
                        MC_current::MC_current_type,Prior::Prior_type)
  λ = MC_current.λ
  β = MC_current.β

  n = length(λ)

  LKσ2 = 1/sum(exp(-λ))
  LKμ = LKσ2 * sum((one_stock_ALV - β .* mkt_related)./exp(λ))

  dis = posNormal(Prior.αμ,Prior.ασ,LKμ,LKσ2,1.)
  return(fill(rand(dis),n))
end

function sample_c(MC_current::MC_current_type,Prior::Prior_type)
  λ = MC_current.λ
  d = MC_current.d
  σλ2 = MC_current.σλ2

  n = convert(Float64,length(λ))

  LKμ = sum(λ[2:end] - d.* λ[1:end-1])
  LKσ2 = σλ2

  dis = posNormal(Prior.cμ,Prior.cσ,LKμ,LKσ2,n-1)
  return(rand(dis))
end

function sample_d(MC_current::MC_current_type,Prior::Prior_type)
  λ = MC_current.λ
  c = MC_current.c
  d = MC_current.d
  σλ2 = MC_current.σλ2

  λ_stat_mean = c/(1-d)

  LKμ = sum((λ[2:end] - λ_stat_mean).*(λ[1:end-1] - λ_stat_mean))
  LKσ2 = σλ2
  n = sum((λ[1:end-1]-λ_stat_mean).^2)

  dis = posNormal(Prior.dμ,Prior.dσ,LKμ,LKσ2,n)

  (μ,) = params(dis)

  draw = rand(Truncated(dis,0,1))

  if isfinite(draw)
    if draw == 1
      return(rand(Uniform(0,1e-8)))
    else
      return(draw)
    end
  else
    if μ < 0
      return(rand(Uniform(0,1e-8)))
    else
      return(rand(Uniform(1-1e-8,1)))
    end
  end
end

function sample_σβ2(MC_current::MC_current_type,Prior::Prior_type)
  β = MC_current.β
  a = MC_current.a
  b = MC_current.b
  n = length(β)

  LKa = n/2
  LKb = 1/2*sum((β[2:end] - a - b * β[1:end-1]).^2)

  dis = InverseGamma(Prior.σβ2a + LKa, Prior.σβ2b + LKb)
  return(rand(dis))
end

function sample_σλ2(MC_current::MC_current_type,Prior::Prior_type)
  λ = MC_current.λ
  c = MC_current.c
  d = MC_current.d
  n = length(λ)

  λ_stat_mean = c/(1-d)

  LKa = n/2
  if d != 1
    LKb = 1/2*sum((λ[2:end] - λ_stat_mean - d*(λ[1:end-1] - λ_stat_mean)).^2)
  else
    LKb = 1/2*sum((λ[2:end] - c - d * λ[1:end-1]).^2)
  end

  dis = InverseGamma(Prior.σλ2a + LKa, Prior.σλ2b + LKb)
  return(rand(dis))
end

function initSim()
  β1 = 1
  λ1 = 2
  α = 0.5
  a = 0
  b = 1
  c = 0.4
  d = 0.8
  σβ = 0.4
  σλ = 2
  Sim = Sim_type(β1,λ1,α,a,b,c,d,σβ,σλ)
  return(Sim)
end


function simData(mkt::Vector{Float64},Sim::Sim_type)
  β1 = Sim.β1
  λ1 = Sim.λ1
  α = Sim.α
  a = Sim.a
  b = Sim.b
  c = Sim.c
  d = Sim.d
  σβ = Sim.σβ
  σλ = Sim.σλ

  n = length(mkt)

  β = zeros(Float64,n)
  β[1] = β1

  λ = zeros(Float64,n)
  λ[1] = λ1

  for i = 2:n
    β[i] = rand(Normal(β[i-1],σβ))
    λ[i] = rand(Normal(c + d*λ[i-1], σλ))
  end

  # λ = 2ones(Float64,n)
  stock = zeros(Float64,n)
  for i = 1:n
    stock[i] = rand(Normal(α + β[i]*mkt[i],exp(λ[i]/2)))
  end

  return stock,β,λ
end


