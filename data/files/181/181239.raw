module PolynomialProbabilities
using Distributions

import Base.getindex, Base.append!, Base.isequal, Base.==, Base.length

export PolynomialProbability, PolynomialProbabilityPiece, append!, ==, getindex, length

type PolynomialProbabilityPiece
    t0::Float64
    t1::Float64
    polys::Array{Float64, 2}
    exp::Vector{Float64}

    # Setting all attributes
    PolynomialProbabilityPiece(t0::Float64, t1::Float64, polys::Array{Float64, 2}, exp::Vector{Float64}) = new(t0, t1, polys, exp)
    # Uniform distribution
    PolynomialProbabilityPiece(t0::Float64, t1::Float64, constant::Float64) = new(t0, t1, eye(1) * constant, [0])
end

function ==(pp1::PolynomialProbabilityPiece, pp2::PolynomialProbabilityPiece)
    return pp1.t0 == pp2.t0 && pp1.t1 == pp2.t1 && pp1.polys == pp2.polys && pp1.exp == pp2.exp
end

type PolynomialProbability <: ContinuousUnivariateDistribution
    pieces::Vector{PolynomialProbabilityPiece}

    # Empty distribution
    PolynomialProbability() = new([])
    # Full domain simple distribution
    PolynomialProbability(polys::Array{Float64, 2}, exp::Vector{Float64}) = new([PolynomialProbabilityPiece(-Inf, Inf, polys, exp)])
end

length(pp::PolynomialProbability) = length(pp.pieces)
getindex(pp::PolynomialProbability, ii::Int64) = pp.pieces[ii]

function ==(pp1::PolynomialProbability, pp2::PolynomialProbability)
    if length(pp1) != length(pp2)
        return false
    end

    for ii = 1:length(pp1)
        if pp1[ii] != pp2[ii]
            return false
        end
    end

    return true
end

function append!(pp::PolynomialProbability, t0::Float64, t1::Float64, polys::Array{Float64, 2}, exp::Vector{Float64})
    piece = PolynomialProbabilityPiece(t0, t1, polys, exp)
    push!(pp.pieces, piece)

    pp
end

function append!(pp::PolynomialProbability, t0::Float64, t1::Float64, constant::Float64)
    piece = PolynomialProbabilityPiece(t0, t1, constant)
    push!(pp.pieces, piece)

    pp
end

include("ppsimple.jl")

end # module
