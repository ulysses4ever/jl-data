module VARs

abstract VarPredModel
abstract VarChol
typealias BlasReal Union(Float32,Float64)

import Base.LinAlg: Cholesky


type VarResp{V<:BlasReal} 
    mu::Matrix{V}    
    Y::Matrix{V}
    E::Matrix{V}
end

VarResp{V<:BlasReal}(Y::Matrix{V}) =  VarResp(similar(Y), Y, similar(Y))

type SUR{T<:BlasReal} <: VarChol
    B0::Matrix{T}
    Xt::Matrix{T}
    SS::Matrix{T}
    chol::Cholesky{T}
end

function SUR{T<:BlasReal}(B0::Matrix{T}, X::Matrix{T})
    k, m = size(B0)
    SS = Array(T, m, m)
    XX = X'X
    XX = cholfact!(XX)
    SUR(B0, X, SS, XX)
end 



type Bayesian{T<:BlasReal} <: VarChol
    B0::Dict{ASCIIString,Array{Float64,2}}
    Xt::Matrix{T}
    SS::Matrix{T}
    chol::Cholesky{T}
    order::Int
    intercept::Bool
    predist::Dict{ASCIIString,Array{Float64,1}}
end 

type Projection{T<:BlasReal} <: VarChol
    order::Vector{Int}
    intercept::Vector{Bool}
    function Projected{T<:BlasReal}(D::Matrix{T}, order::Vector{Int},
                                    intercept::Vector{Bool})
        create_canonical_var_proj_model!(Xt, D, order, intercept)
        Xt = Array(T, r, c)
        XX = Array(T, c, c)
        new(Xt, B0, XX, order, intercept)
    end 
end

type LinearVarModel{T<:VarChol} <: VarPredModel
    rr::VarResp
    pp::T
end



function fit{V<:BlasReal, T<:VarChol}(::Type{LinearVarModel{T}}, D::Matrix{V}, order::Integer; intercept::Bool = true)    
    n, m = size(D)
    p = order
    sk   = intercept ? 1 : 0    
    X    = Array(V, n-p, sk+m*p)
    Y    = Array(V, n-p, m)
    B0   = Array(V, sk+p*m, m)
    get_canonical_form!(D, Y, X, p, intercept)    
    rr = VarResp(Y)
    pp = T(B0, X)
    updatelinpred!(putbeta!(pp, rr.Y), rr)
    residuals!(pp, rr)
    At_mul_B!(pp.SS, rr.E, rr.E)
    LinearVarModel(rr, pp)
end 

residuals!{T<:BlasReal}(p::VarChol, r::VarResp{T}) = r.E[:] = r.Y-r.mu

function updatelinpred!{T<:BlasReal}(p::VarChol, r::VarResp{T})
    A_mul_B!(r.mu, p.Xt, p.B0)
end 

function putbeta!{T<:BlasReal}(p::VarChol, r::Matrix{T})
    A_ldiv_B!(p.chol, At_mul_B!(p.B0, p.Xt, r))
    p
end

function get_canonical_form!(D::Matrix, Y::Matrix, X::Matrix, p, intercept)
    n, m = size(D)
    sk   = intercept ? 1 : 0
    idx  = repmat(1:m, p)    
    for j = 1+sk:(sk+m*p)
        for i = 1:(n-p)
            lg = int(ceil((j-sk)/m))-1
            @inbounds X[i, j] = D[i+p-1-lg, idx[j-sk]]
        end
    end

    if intercept
        for j=1:n-p
            X[j,1] = 1.0
        end
    end 

    for j = 1:m
        for i = 1:(n-p)
            @inbounds Y[i, j] = D[i+p, j]
        end
    end
end


## p = 12
## m = 120
## n = 480

## D = randn(n, m)
## X = Array(Float64, n-p, 1+m*p)
## Y = Array(Float64, n-p, m)

## get_canonical_form(D, Y, X, p, true)


abstract BVarPriorSpec

type MinnesotaPrior <: BVarPriorSpec
    ## stub
end

type OtherPrior <: BVarPriorSpec
    ## stub
end


## This is only an example. I am thinking of having something like This
##
## VAR(OLS, Data, 5)                       ## Estimate a VAR(5) using OLS
## This is the default, so we can do
##
## VAR(Data, 5)

## VAR(Projection, Data, order, maxh)

## Here order is an array --- since the order can be different for each lag length
## maxh is the maximu lead length at which the var is estimated


## irf1 = irf(var1, h = 12)
## irf(var1, h = 12, shocks = ...)   ## I may want to specify a specific shock
## plot(irf1)
## plot(irf1, options...)

## aic(var1)
## bic(var1)

## and so forth.....


function fit(::Type{LinearVarModel}, D::Matrix, order::Integer; kwargs...)
    fit(LinearVarModel{SUR}, D, order; kwargs...)
end


VAR(Y, order; kwargs...) = fit(LinearVarModel, Y, order; kwargs...) 

function irf(VAR::LinearVarModel, H::Int64, p::Int64, cholesky::Bool=true)
         # Default Cholesky identification and estimation with intercept
         K = size(VAR.pp.SS,1) # Number of variables          
         if cholesky == true Sigma =  chol(VAR.pp.SS)' else Sigma = eye(K,K) end # Cholesky or reduced form
         B0 = VAR.pp.B0'[:,2:end]
         B0 = [B0;[eye(K*(p-1)) zeros(K*(p-1),K)]] # Companion form 
         J = [eye(K,K) zeros(K,K*(p-1))]
         IRF = reshape((J*B0^0*J'*Sigma)',K^2,1)
         for i = 1:H
             IRF = [IRF reshape((J*B0^i*J'*Sigma)',K^2,1)] #Cholesky here has also the intercept 
         end
         return IRF
end

# Allow to specify a particular shock
function irf(VAR::LinearVarModel, H::Int64, shock::Int64, p::Int64, cholesky::Bool=true)
         # Default Cholesky identification
         K = size(VAR.pp.SS,1) # Number of variables          
         if cholesky == true Sigma = chol(VAR.pp.SS)' else Sigma = eye(K,K) end # Cholesky or reduced form
         if abs(shock)>K error("shock must be between 1 and $k") end # Check on shock number
         B0 = VAR.pp.B0'[:,2:end]
         B0 = [B0;[eye(K*(p-1)) zeros(K*(p-1),K)]] # Companion form 
         J = [eye(K,K) zeros(K,K*(p-1))]
         IRF = reshape((J*B0^0*J'*Sigma)',K^2,1) # before B0^0 why?
         for i = 1:H
             IRF = [IRF reshape((J*B0^i*J'*Sigma)',K^2,1)] #Cholesky here has also the intercept 
         end
         IRFs = zeros(K,H+1)
         IRFs[:,:] = IRF[shock:K:(size(IRF,1)-K+shock),:]
         return IRFs
end


export VAR, irf

# package code goes here

end # module
