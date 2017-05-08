module PolynomialProbabilities

using Distributions

export PolynomialProbability

type PolynomialProbability <: ContinuousUnivariateDistribution
    t0::Vector{Float64}
    t1::Vector{Float64}
    polys::Array{Float64, 2}
    exp:Vector{Float64, 2}

    # Uniform distribution
    PolynomialProbability(t0::Float64, t1::Float64, constant::Float64) = new([t0], [t1], [constant], [0])
    # Segment of a distribution
    PolynomialProbability(t0::Float64, t1::Float64, polys::Vector{Float64}, exp::Vector{Float64}) = new([t0], [t1], polys, exp)
    # Full domain simple distribution
    PolynomialProbability(polys::Vector{Float64}, exp::Vector{Float64}) = new([-Inf], [Inf], polys, exp)
end

length(pp::PolynomialProbability) = size(pp.exp, 1)
getindex(pp::PolynomialProbability, ii::Float64) = PolynomialProbability(pp.t0[ii], pp.t1[ii], pp.polys[ii, :], pp.exp[ii, :])

function append!(pp::PolynomialProbability, t0::Float64, t1::Float64, polys::Vector{Float64}, exp::Vector{Float64})
    pp.t0.push!(t0)
    pp.t1.push!(t1)
    pp.polys = vcat(pp.polys, polys)
    pp.exp = vcat(pp.exp, exp)

    pp
end

end # module
