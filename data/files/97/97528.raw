module icepdf

# package code goes here
using Distributions

#function gaussian(x, m, s) = 
    
type IcePdf
    a::Float64
    b::Float64
    c::Float64
end

type SimplePdf
    mu::Float64
    sigma::Float64
    ## lower::Float64
    ## upper::Float64
end
    
## type BoundedSimplePdf <: SimplePdf
##     lower::Float64
##     upper::Float64
## end
    
type Pdf
    components::Array{SimplePdf,1}
    weights::Array{Float64,1}
    #components::Array{(SimplePdf,Float64),1}
    #components::typeof(Int64[])
    #mu::Float64
    #sigma::Float64
end
## Alt use 
## julia> ?Distributions.MultivariateNormal
## DataType   : GenericMvNormal{PDMat} (constructor with 5 methods)
##   supertype: AbstractMvNormal
##   fields   : (:dim,:zeromean,:μ,:Σ)
## with identity corelation matrix


function evaluate(pdf::SimplePdf, x::Float64)
    f = Distributions.Normal(pdf.mu, pdf.sigma)
    Distributions.pdf(f,x)
    end

function evaluate(pdf::Pdf, x::Float64)
    res = 0
    for cmpwgt in zip(pdf.components,pdf.weights)
        cmp, wgt = cmpwgt
        f = Distributions.Normal(cmp.mu, cmp.sigma)
        val = wgt * Distributions.pdf(f,x)
        res += val # / weights_sum
    end
    res / sum(pdf.weights)
end

function cumulative(pdf::SimplePdf, x)
    F = Distributions.Normal(pdf.mu, pdf.sigma)
    Distributions.cdf(F,x) # /weihts_sum
    end

function cumulative(pdf::Pdf, x::Number)
    res = 0
    for cmpwgt in zip(pdf.components,pdf.weights)
        cmp, wgt = cmpwgt
        f = Distributions.Normal(cmp.mu, cmp.sigma)
        val = wgt * Distributions.cdf(f,x)
        res += val # / weights_sum
    end
    res / sum(pdf.weights)
end
    
# SimplePdf
n = SimplePdf(0,1)
println("eval $(evaluate(n,1.3))")
println("cdf $(cumulative(n,9))")
println("cdf $(cumulative(n,0))")

# Pdf
p1 = SimplePdf( 0.0, 1.0)
p2 = SimplePdf( 0.0, 1.0)
p3 = SimplePdf( 0.0, 1.0)
#p2 = SimplePdf( 1.0, 0.5)
#p3 = SimplePdf(-0.5, 0.6)

p = SimplePdf[]
push!(p,p1)
push!(p,p2)
push!(p,p3)

w = Float64[]
push!(w,1.0)
push!(w,1.0)
push!(w,1.0)

P = Pdf(p,w)
println("eval $(evaluate(P,1.3))")
println("cdf $(cumulative(P,9))")
println("cdf $(cumulative(P,0))")



end # module
