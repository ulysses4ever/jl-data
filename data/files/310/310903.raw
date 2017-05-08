################################################
# Description:
# Black-Scholes option pricing
#
# Author: Asaf Manela
# Date: 2015-08-02
################################################
module BlackScholes

using Distributions
N(x) = cdf(Normal(),x)
Nx(x) = pdf(Normal(),x)
d1(S,K,σ,r,T,δ) = (log(S/K) + (r-δ+σ^2/2)*T)/(σ*sqrt(T))
d2(S,K,σ,r,T,δ) = d1(S,K,σ,r,T,δ) - σ*sqrt(T)

BSForward(S,K,r,T,δ) = S*exp(-δ*T) - K*exp(-r*T)
BSCall(S,K,σ,r,T,δ) = S*exp(-δ*T)*N(d1(S,K,σ,r,T,δ)) - K*exp(-r*T)*N(d2(S,K,σ,r,T,δ))
BSPut(S,K,σ,r,T,δ) = K*exp(-r*T)*N(-d2(S,K,σ,r,T,δ)) - S*exp(-δ*T)*N(-d1(S,K,σ,r,T,δ))
BSPremium(S,K,σ,r,T,δ,iscall) = iscall ? BSCall(S,K,σ,r,T,δ) : BSPut(S,K,σ,r,T,δ)

BSCallVega(S,K,σ,r,T,δ) = sqrt(T)*S*exp(-δ*T)*Nx(d1(S,K,σ,r,T,δ))

MAX_ITERATIONS = 100
function BSImpliedVol(S,K,r,T,δ,premium,iscall)
  if iscall
    C = premium
  else # convert usign put-call parity
    C = premium + BSForward(S,K,r,T,δ)
  end
  σ = 0.0
  σnext = sqrt(2*pi/T)*C/S
  i = 0
  while abs(σnext - σ) > eps(σnext) && i < MAX_ITERATIONS
    σ = σnext
    σnext = σ - (BSCall(S,K,σ,r,T,δ) - C)/BSCallVega(S,K,σ,r,T,δ)
    i = i+1
  end
  return σnext
end

export BSForward, BSPut, BSCall, BSImpliedVol, BSCallVega, BSPremium, N, Nx, d1, d2
end #module

