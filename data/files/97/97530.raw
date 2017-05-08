module icepdf

# package code goes here
using Distributions

type IcePdf # move me to ice module
    a::Float64
    b::Float64
    c::Float64
end

abstract SimplePdf # must have: mu::Float64, sigma::Float64, weight::Float64

type GaussianPdf <: SimplePdf # move us to pdf module
    mu::Float64
    sigma::Float64
    weight::Float64
    ## lower::Float64
    ## upper::Float64
end
    
type BoundedGaussianPdf <: SimplePdf
    mu::Float64
    sigma::Float64
    weight::Float64
    lower::Float64
    upper::Float64
end
    
type Pdf
    components::Array{SimplePdf,1}
end
## Alt use 
## julia> ?Distributions.MultivariateNormal
## DataType   : GenericMvNormal{PDMat} (constructor with 5 methods)
##   supertype: AbstractMvNormal
##   fields   : (:dim,:zeromean,:μ,:Σ)
## with identity corelation matrix


function evaluate(pdf::GaussianPdf, x::Float64)
    f = Distributions.Normal(pdf.mu, pdf.sigma)
    Distributions.pdf(f,x)
end

function evaluate(pdf::BoundedGaussianPdf, x::Float64)
    if pdf.lower <= x <= pdf.upper
        f = Distributions.Normal(pdf.mu, pdf.sigma)
        probability = Distributions.pdf(f,x)
    else
        probability = 0.0
    end
    return probability
end

function evaluate(pdf::Pdf, x::Float64)
    res = 0
    weights_sum = 0
    for cmp in pdf.components
        weights_sum += cmp.weight
        f = Distributions.Normal(cmp.mu, cmp.sigma)
        val = cmp.weight * Distributions.pdf(f,x)
        res += val
    end
    res / weights_sum
end

function cumulative(pdf::GaussianPdf, x)
    F = Distributions.Normal(pdf.mu, pdf.sigma)
    Distributions.cdf(F,x) # /weihts_sum
    end

function cumulative(pdf::Pdf, x::Number)
    res = 0
    weights_sum = 0
    for cmp in pdf.components
        weights_sum += cmp.weight
        f = Distributions.Normal(cmp.mu, cmp.sigma)
        val = cmp.weight * Distributions.cdf(f,x)
        res += val
    end
    res / weights_sum
end
    
# SimplePdf
n = GaussianPdf(0,1,1)
println("eval $(evaluate(n,1.3))")
println("cdf $(cumulative(n,9))")
println("cdf $(cumulative(n,0))")

# Pdf
p1 = GaussianPdf( 0.0, 1.0, 1.0)
p2 = GaussianPdf( 0.0, 1.0, 1.0)
p3 = GaussianPdf( 0.0, 1.0, 1.0)
#p2 = SimplePdf( 1.0, 0.5, 1.0)
#p3 = SimplePdf(-0.5, 0.6, 1.0)

p = SimplePdf[]
push!(p,p1)
push!(p,p2)
push!(p,p3)

P = Pdf(p)
println("eval $(evaluate(P,1.3))")
println("cdf $(cumulative(P,9))")
println("cdf $(cumulative(P,0))")

end # module
