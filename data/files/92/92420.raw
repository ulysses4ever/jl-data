module TruncatedNormal

include("table.jl")
dlopen("../deps/mvt.dylib", 1)


using Distributions
import Base.cor 
import Distributions.cdf

    

function mvt(N::Int64,
             NU::Int64,
             LOWER::StridedArray{Float64},
             UPPER::StridedArray{Float64},
             INFIN::Vector{Int64},
             CORREL::StridedArray{Float64},
             DELTA::StridedArray{Float64},
             MAXPTS::Int64,
             ABSEPS::Float64,
             RELEPS::Float64,
             ERROR::Vector{Float64},
             VALUE::Vector{Float64})

    INFIN_ = Array(Int32, N)
    for(j in 1:N)
        INFIN_[j] = INFIN[j]
    end 

    INFO = Int32[1]



 ## MVTDST( N, NU, LOWER, UPPER, INFIN, CORREL, DELTA, 
 ##         MAXPTS, ABSEPS, RELEPS, ERROR, VALUE, INFORM )

 ##     N      INTEGER, the number of variables.    
 ##     NU     INTEGER, the number of degrees of freedom.
 ##            If NU < 1, then an MVN probability is computed.
 ##     LOWER  DOUBLE PRECISION, array of lower integration limits.
 ##     UPPER  DOUBLE PRECISION, array of upper integration limits.
 ##     INFIN  INTEGER, array of integration limits flags:
 ##             if INFIN(I) < 0, Ith limits are (-infinity, infinity);
 ##             if INFIN(I) = 0, Ith limits are (-infinity, UPPER(I)];
 ##             if INFIN(I) = 1, Ith limits are [LOWER(I), infinity);
 ##             if INFIN(I) = 2, Ith limits are [LOWER(I), UPPER(I)].
 ##     CORREL DOUBLE PRECISION, array of correlation coefficients; 
 ##            the correlation coefficient in row I column J of the 
 ##            correlation matrixshould be stored in 
 ##               CORREL( J + ((I-2)(I-1))/2 ), for J < I.
 ##            The correlation matrix must be positive semi-definite.
 ##     DELTA  DOUBLE PRECISION, array of non-centrality parameters.
 ##     MAXPTS INTEGER, maximum number of function values allowed. This 
 ##            parameter can be used to limit the time. A sensible 
 ##            strategy is to start with MAXPTS = 1000N, and then
 ##            increase MAXPTS if ERROR is too large.
 ##     ABSEPS DOUBLE PRECISION absolute error tolerance.
 ##     RELEPS DOUBLE PRECISION relative error tolerance.
 ##     ERROR  DOUBLE PRECISION estimated absolute error, 
 ##            with 99% confidence level.
 ##     VALUE  DOUBLE PRECISION estimated value for the integral

    ccall( (:mvtdst_, "mvt"), Void, (Ptr{Int32},    
                                    Ptr{Int32},
                                    Ptr{Float64},
                                    Ptr{Float64},
                                    Ptr{Int32},
                                    Ptr{Float64},
                                    Ptr{Float64},
                                    Ptr{Int32},
                                    Ptr{Float64},
                                    Ptr{Float64},
                                    Ptr{Float64},
                                    Ptr{Float64},
                                    Ptr{Int32}),
          &N, &NU, LOWER, UPPER, INFIN_, CORREL, DELTA, &MAXPTS, &ABSEPS, &RELEPS, ERROR, VALUE, INFO )
    
    return INFO, ERROR, VALUE
    
end


function pmvnorm(N::Int64,                 
                 LOWER::Vector{Float64},
                 UPPER::Vector{Float64},             
                 CORREL::Vector{Float64},
                 DELTA::Vector{Float64})

    if(length(LOWER)!=N || length(UPPER)!=N || length(DELTA)!=N)
        throw("Dimensions are inconsistent")
    end

    if(any(LOWER.>UPPER))
        throw("At leat one 'lower>UPPER'")
    end

    NU     = -1
    MAXPTS = 50000
    ABSEPS = 0.0
    RELEPS = 0.0004
    ERROR  = [0.0]
    VALUE  = [0.0]
    INFIN  = Array(Int64, N)

    for(j in 1:N)
        if(isinf(LOWER[j]) && isinf(UPPER[j]))
            INFIN[j] = -1
        elseif isinf(LOWER[j])
            INFIN[j] = 0
        elseif isinf(UPPER[j])
            INFIN[j] = 1
        else
            INFIN[j] = 2
        end
    end

    info, value, error = mvt(N, NU, LOWER, UPPER, INFIN, CORREL, DELTA, MAXPTS, ABSEPS, RELEPS, ERROR, VALUE)

    return info, value, error
end 



## mvt(2,
##     1,
##     [0., 0.],
##     [1., 1.],
##     [0, 0],
##     [0.5],
##     [1.0 ,1.0],
##     25000,
##     0.0,
##     0.0005,
##     [0.0],
##     [0.0])


function cor(d::MvNormal)
    corr = zeros(D.dim, D.dim)
    for(j in 1:D.dim)
        for(i in 1:D.dim)
            corr[i,j] = D.Σ.mat[i,j]/sqrt(D.Σ.mat[i,i]*D.Σ.mat[j,j])
        end
    end
    return(corr)
end 


function cdf(d::MvNormal, lower::Vector{Float64}, upper::Vector{Float64})
    N     = D.dim    
    NN    = convert(Int64, (N-1)*N/2)
    Sigma = cov(D)
    
    if(length(lower)!=N || length(upper)!=N)
        throw("Wrong dimension")
    end

    if(any(lower.>upper))
       throw("Wrong dimension")
    end

    DELTA  = D.μ
    
    CORREL = Array(Float64, NN)
    for i = 1:N, j = 1:(i-1)
        CORREL[ j + ((i-2)*(i-1))/2 ] = Sigma[i,j]/sqrt(Sigma[i,i]*Sigma[j,j])
    end
    
    INFO, ERROR, VALUE = pmvnorm(N, lower, upper, CORREL, DELTA)
    return VALUE[1]

end
    

function rmvnorm(N::Int64, mean::Vector, Sigma::Matrix, lower::Vector, upper::Vector, LC::Matrix)

    K    = length(mean)
    Y    = zeros(K, N)
    ns   = N
    nast = 0

    D = MvNormal(mean, Sigma)    
    alpha = cdf(D, lower, upper)

    while ns>0
        np  = begin
            if ns/alpha>10000
                ns
            else
                int(ceil(maximum([ns/alpha, 10.])))
            end
        end 

        X  = rand(D, np)
        X2 = LC*X
        ind = Array(Bool, np)
        for i = 1:np
            ind[i] = all( (X2[:,i] .>= lower) & (X2[:,i] .<= upper) )
        end 
        
        nas = length(ind[ind])
        
        if(length(nas)==0 || nas==0)
            continue
        end

        alpha = nas/np

        nns = minimum([nas, ns])

        Y[:, (nast + 1):(nast + nns)] = X[:, find(ind)[1:nns]]

        nast = nast + nas

        ns = ns - nas
    end

    return Y
end 

@time rtmvnorm2(1, D.μ, cov(D), lower, upper, diagm([1, 1, 1]))        

function dmvnorm(mean::Vector, Sigma::Matrix, lower::Vector, upper::Vector)
    D = MvNormal(mean, Sigma)
    logpdf(D) - log(cdf(D, lower, upper))
end 
    

abstract AbstractTruncatedMvNormal <: ContinuousMultivariateDistribution

immutable GenericTruncatedMvNormal{Cov<:AbstractPDMat} <: AbstractTruncatedMvNormal
    dim::Int
    zeromean::Bool
    μ::Vector{Float64}
    Σ::Cov
    lower::Vector{Float64}
    upper::Vector{Float64}
end

    
D = MvNormal([1.,1,1], [2. 0.75 0.65; 0.75 1 0.65; 0.75 0.65 1])    
    
@time cdf(D, [0., 0, 0], [3, 3, 3.])    



type Truncated{D<:GenericMvNormal}
    untruncated::D
    lower::Float64
    upper::Float64
    nc::Float64
    function Truncated{T<:GenericMvNormal}(d::T, l::Real, u::Real, nc::Real)
        if l >= u
        error("upper must be > lower")
    end
        new(d, float64(l), float64(u), float64(nc))
    end
end




D = Normal(0., 1.)

Truncated(D, 0., +Inf, .2)

d = TruncatedNo(D, 0., +Inf, 0.)

rand(100, d)

function cdf!(r::Array{Float64}, d::AbstractMvNormal, x::Matrix{Float64})
    





function rtnorm(n::Int64, μ::Real, σ::Real, a::Real, b::Real)
    a = (a-μ)/σ 
    b = (b-μ)/σ
    r = rtnomr(a, b)
    r = r*σ + μ
    Z = sqrt(pi/2)*σ*(erf(b/sqrt(2))-erf(a/sqrt(2)))
    Z = max(Z,1e-15)      
    p = exp(-(r-μ).^2/2/σ^2) / Z
    return draw, p
end

function rtnorm(a::Real, b::Real)
    
    const xmin = -2.00443204036
    const xmax = 3.48672170399
    stop = false
    
    if a>=b    
        throw("B must be greater than A.")
    elseif abs(a)>abs(b)
        r = -rtnorm(-b, -a)
    elseif a > xmax
        stop = 0
        twoasq = 2*a^2
        expab = exp(-a*(b-a)) - 1
        while ~stop
            z = log(1 + rand()*expab)
            e = -log(rand())
            stop = (twoasq*e > z^2)
        end
        r = a - z/a        
    elseif a<xmin
        stop = 0
        while ~stop
            r = randn()
            stop = (r>=a) && (r<=b)
        end
    else
        const kmin = 5          
        const INVH = 1631.73284006;  
        const I0 = 3271;                      
        const ALPHA = 1.837877066409345;      
        const N = 4001;                       
        const yl0 = 0.053513975472;           
        const ylN = 0.000914116389555;        

        i = I0 + floor(a*INVH)
        ka = ncell[i+1]
        if b >= xmax
            kb = N
        else
            i = I0 + floor(b*INVH)
            kb = ncell[i+1]
        end

        if abs(kb-ka) < kmin            
            stop = false 
            twoasq = 2*a^2
            expab = exp(-a*(b-a)) - 1
            while ~stop
                z = log( 1 + rand()*expab )
                e = -log(rand())
                stop = (twoasq*e > z^2)
            end
            r = a - z/a
            return r
        end

        while 1>0
            ## Sample integer between ka and kb
            k = rand(ka:kb) + 1           
            if k == N+1            
            ## Right tail            
                lbound = x[end]
                z = -log(rand())
                e = -log(rand())
                z = z / lbound
                if (z^2 <= 2*e) && (z < b-lbound)
                    ## Accept this proposition, otherwise reject
                    r = lbound + z
                    return r
                end
            elseif (k<=ka+2) || (k>=kb && b<xmax)
                ## Two leftmost and rightmost regions            
                sim = x[k] + (x[k+1]-x[k]) * rand()
                if (sim >= a) && (sim <= b)
                    # Accept this proposition, otherwise reject
                    simy = yu[k]*rand()               
                    # Compute y_l from y_k
                    if k == 1
                        ylk = yl0
                    elseif k == N
                        ylk = ylN
                    elseif k <= 1954
                        ylk = yu(k-1)
                    else
                        ylk = yu(k+1)
                    end;
                    
                    if (simy<ylk) || (sim^2 + 2*log(simy) + ALPHA < 0)
                        r = sim
                        return r
                    end
                end
            else
                
                ## All the other boxes            
                u = rand()
                simy = yu[k] * u
                d = x[k+1] - x[k]
                
                ## Compute y_l from y_k
                if k == 1
                    ylk = yl0
                elseif k == N
                    ylk = ylN
                elseif k <= 1954
                    ylk = yu(k-1)
                else
                    ylk = yu(k+1)
                end
                
                if simy < ylk
                    r = x[k] + u*d*yu[k]/ylk
                    return r
                end
                sim = x(k) + d * rand()
                # Otherwise, check you're below the pdf curve

                if sim^2 + 2*log(simy) + ALPHA < 0
                    r = sim
                    return r
                end
            end  # end if
        end    # end while    
    end

end

end

