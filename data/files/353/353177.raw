using DataFrames
using Distributions
using GLM

cd("C:\\Users\\msbcr563\\BABJulia")

stock = readtable(".\\Data\\stock.csv")
size(stock)
mkt = readtable(".\\Data\\mkt.csv")
alive = readtable(".\\Data\\alive.csv")

include("InitType.jl")
include("func.jl")

Para = initPara()

srand(7298)

tic()

betaDtMat = zeros(Float64,(Para.T,Para.n_stocks))


for i = 1#:Para.n_stocks
  nALV = alive[2,i] - alive[1,i] + 1
  ALV = alive[1,i]:alive[2,i]

  one_stock_ALV = convert(Array{Float64,1},stock[ALV,i])

  mkt_related = convert(Array{Float64,1},mkt[ALV,1])

  OLS = getOLS(one_stock_ALV,mkt_related)

  Prior = initPrior(OLS)

  MC_current = initMC(Prior,OLS,nALV)

  FFBS_input = conv2FFBS_type(one_stock_ALV,mkt_related,MC_current,Prior)
  for j = 1:Para.M
    local betaMat = zeros(Float64,(nALV,Para.N))

    for k = 1:Para.N

      (MC_current.β,betaMat[:,k]) = FFBS(FFBS_input)

      SV_input = conv2SV_type(one_stock_ALV,mkt_related,MC_current,Prior)

      MC_current.λ = SV(SV_input)

      MC_current.α = sample_α(one_stock_ALV,mkt_related,MC_current,Prior)

      MC_current.c = sample_c(MC_current::MC_current_type,Prior::Prior_type)

      MC_current.d = sample_d(MC_current::MC_current_type,Prior::Prior_type)

      MC_current.σβ2 = sample_σβ2(MC_current::MC_current_type,Prior::Prior_type)

      MC_current.σλ2 = sample_σλ2(MC_current::MC_current_type,Prior::Prior_type)
    end
  end
end


toc()
