using DataFrames
using Distributions
using GLM
using Gadfly

cd("C:\\Users\\msbcr563\\BABJulia")

stock = readtable(".\\Data\\stock.csv")
mkt = readtable(".\\Data\\mkt.csv")
alive = readtable(".\\Data\\alive.csv")

include("InitType.jl")
include("func.jl")

Para = initPara()

srand(070298)

tic()

β_all = 10000ones(Float64,(Para.n_stocks,Para.T))
i = 1
j = 1
k = 1

for i =  1:Para.n_stocks
  nALV = alive[2,i] - alive[1,i] + 1
  ALV = alive[1,i]:alive[2,i]

  one_stock_ALV = convert(Array{Float64,1},stock[ALV,i])

  mkt_related = convert(Array{Float64,1},mkt[ALV,1])

  OLS = getOLS(one_stock_ALV,mkt_related)

  Prior = initPrior(OLS)

  β_1stock = zeros(Float64,(nALV,Para.M))

  for j = 1:Para.M
    β_1MC = zeros(Float64,(nALV,Para.N))

    MC_current = initMC(Prior,OLS,nALV)

    for k = 1:Para.N

      FFBS_input = conv2FFBS_type(one_stock_ALV,mkt_related,MC_current,Prior)

      MC_current.c = sample_c(MC_current::MC_current_type,Prior::Prior_type)

      MC_current.d = sample_d(MC_current::MC_current_type,Prior::Prior_type)

      MC_current.σλ2 = sample_σλ2(MC_current::MC_current_type,Prior::Prior_type)

      SV_input = conv2SV_type(one_stock_ALV,mkt_related,MC_current,Prior)

      MC_current.λ = SV(SV_input)

      (MC_current.β,β_1MC[:,k]) = FFBS(FFBS_input)

      MC_current.σβ2 = sample_σβ2(MC_current::MC_current_type,Prior::Prior_type)

      MC_current.α = sample_α(one_stock_ALV,mkt_related,MC_current,Prior)
    end

    β_1stock[:,j] = mean(β_1MC[:,Para.burnin+1:Para.N],2)

  end
  β_all[i,ALV] = mean(β_1stock,2)

end


toc()

writecsv(".\\Data\\βEst.csv",β_all)



