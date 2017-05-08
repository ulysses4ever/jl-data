using DataFrames
using Distributions
using GLM
using Gadfly
cd("C:\\Users\\msbcr563\\BABJulia")

include("InitType.jl")
include("func.jl")

mkt = readtable(".\\Data\\mkt.csv")
mkt =  convert(Vector{Float64},mkt[:,1])
Sim = initSim()

srand(7298)
(stock,β_true,λ_true) = simData(mkt,Sim)

Para = initPara()

tic()

nALV = Para.T

one_stock_ALV = stock

mkt_related = mkt

OLS = getOLS(one_stock_ALV,mkt_related)

Prior = initPrior(OLS)

Prior.βμ = 2

β_1MC = zeros(Float64,(nALV,Para.N))
λ_1MC = zeros(Float64,(nALV,Para.N))
α_1MC = zeros(Float64,(nALV,Para.N))
a_1MC = zeros(Float64,Para.N)
b_1MC = zeros(Float64,Para.N)
c_1MC = zeros(Float64,Para.N)
d_1MC = zeros(Float64,Para.N)
σβ2_1MC = zeros(Float64,Para.N)
σλ2_1MC = zeros(Float64,Para.N)

MC_current = initMC(Prior,OLS,nALV)

for k = 1:Para.N
  SV_input = conv2SV_type(one_stock_ALV,mkt_related,MC_current,Prior)

  MC_current.λ = SV(SV_input)

  FFBS_input = conv2FFBS_type(one_stock_ALV,mkt_related,MC_current,Prior)

  (MC_current.β,β_1MC[:,k]) = FFBS(FFBS_input)

  MC_current.α = sample_α(one_stock_ALV,mkt_related,MC_current,Prior)

  MC_current.c = sample_c(MC_current::MC_current_type,Prior::Prior_type)

  MC_current.d = sample_d(MC_current::MC_current_type,Prior::Prior_type)

  MC_current.σβ2 = sample_σβ2(MC_current::MC_current_type,Prior::Prior_type)

  MC_current.σλ2 = sample_σλ2(MC_current::MC_current_type,Prior::Prior_type)

  λ_1MC[:,k] = MC_current.λ
  α_1MC[:,k] = MC_current.α
  a_1MC[k] = MC_current.a
  b_1MC[k] = MC_current.b
  c_1MC[k] = MC_current.c
  d_1MC[k] = MC_current.d
  σβ2_1MC[k] = MC_current.σβ2
  σλ2_1MC[k] = MC_current.σλ2

end

β_est = mean(β_1MC[:,Para.burnin+1:Para.N],2)
λ_est = mean(λ_1MC[:,Para.burnin+1:Para.N],2)
α_est = mean(α_1MC[:,Para.burnin+1:Para.N],2)
a_est = mean(a_1MC[Para.burnin+1:Para.N])
b_est = mean(b_1MC[Para.burnin+1:Para.N])
c_est = mean(c_1MC[Para.burnin+1:Para.N])
d_est = mean(d_1MC[Para.burnin+1:Para.N])
σβ2_est = mean(σβ2_1MC[Para.burnin+1:Para.N])
σλ2_est = mean(σλ2_1MC[Para.burnin+1:Para.N])


toc()

cor(β_est,β_true)
cor(λ_est,λ_true)

λ_est - λ_true
