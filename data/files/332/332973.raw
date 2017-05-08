module TestInterp

reload("interpolation.jl")

using FactCheck
using Dierckx
using Interp

# Two hard functions
f1(x) = 1 ./ (1 + 25x.^2)
f2(x) = e.^(sin(x))

# Two easy functions
f3(x) = x.^4 - 2x.^2 + 12
f4(x) = 2*x
f5(x) = exp(-x)

f3p(x) = 3x.^3 - 4x
f4p(x) = 2

const funcs = [
               # f1,
               f2,
               f3,
               f4,
               f5
               ]
const funcsp = [
               # f1,
               # f2,
               f3p,
               f4p,
               # f5
               ]
const a, b, N = -2.0, 2.0, 100
const xs = linspace(a, b, N)



function test_func(f::Function, xs::Vector, fbs::FunctionalSpace)
    # Create Interpolator
    ii = Interpoland(fbs, f)

    true_y = f(xs)
    i_y = evaluate(ii, xs)

    return maxabs(i_y - true_y)
end

Interp.HKSplineBasis(n) = Interp.HKSplineBasis(n, a, b)

function gen_bases(ns::Union(Int, Vector{Int}),
                  fbs=[ChebyshevBasis, MonomialBasis, HKSplineBasis])
    bases = BasisFunctions[]
    for n in ns, fb in fbs
        push!(bases, fb(n))
    end

    return bases
end

const n_pts = [9, 11, 15, 25, 55]
const bases = gen_bases(n_pts)
const c_bases = filter(x->isa(x, ChebyshevBasis), bases)
const m_bases = filter(x->isa(x, MonomialBasis), bases)
const hk_bases = filter(x->isa(x, HKSplineBasis), bases)


facts("Testing type-system") do
    for b in c_bases
        @fact isa(b, BasisFunctions) &&
              isa(b, SpectralBasis) &&
              isa(b, PolynomialBasis) &&
              isa(b, OrthogonalPolynomialBasis) &&
              !isa(b, FiniteElementBasis) &&
              !isa(b, SplineBasis) => true
    end

    for b in m_bases
        @fact isa(b, BasisFunctions) &&
              isa(b, SpectralBasis) &&
              isa(b, PolynomialBasis) &&
              !isa(b, OrthogonalPolynomialBasis) &&
              !isa(b, FiniteElementBasis) &&
              !isa(b, SplineBasis) => true
    end

    for b in hk_bases
        @fact isa(b, BasisFunctions) &&
              !isa(b, SpectralBasis) &&
              !isa(b, PolynomialBasis) &&
              !isa(b, OrthogonalPolynomialBasis) &&
              isa(b, FiniteElementBasis) &&
              isa(b, SplineBasis) => true
    end
end






facts("Testing API") do
    @fact 1 => 1
end

#
# Monomials
#
facts("Testing Monomials") do
    for f in funcs, mfbs in m_bases
        spc = FunctionalSpace(mfbs, a, b)
        @fact test_func(f, xs, spc) => less_than_or_equal(1e-4)
    end
end




# #
# # Chebyshev
# #
facts("Testing chebyshev") do

    context("Testing function evaluation") do
        tic()
        for f in funcs, cfbs in c_bases
            spc = FunctionalSpace(cfbs, a, b)
            @fact test_func(f, nodes(spc), spc) => less_than_or_equal(1e-14)
        end
        println("Time for chebyshev computation: $(toq())")
    end

    # context("Testing derivative evaluation") do
    #     for f in funcsp, cfbs in c_bases
    #         spc = FunctionalSpace(cfbs, a, b)
    #         ii = Interpoland(spc, f)
    #         prime = differentiate(ii)
    #         @fact maxabs(f(xs) - evaluate(prime, xs)) => less_than_or_equal(1e-5)
    #     end
    # end
end



#
# HKB Spline
#
facts("Testing HKB splines") do
    for f in funcs, hkfbs in hk_bases
        spc = FunctionalSpace(hkfbs)
        @fact test_func(f, xs, spc) => less_than_or_equal(1e-1)
    end
end

facts("Testing Dierckx splines") do
    tic()
    db = DierckxSplineBasis(3)
    for f in funcs, n in n_pts
        spc = FunctionalSpace(db, linspace(a, b, n))
        x = nodes(spc)
        y = f(x)
        ii = Interpoland(spc; y=y)
        @fact maxabs(f(xs) - evaluate(ii, xs)) => less_than_or_equal(1e-2)
    end
    println("Time for Dierckx computation: $(toq())")
end



end  # Module End
