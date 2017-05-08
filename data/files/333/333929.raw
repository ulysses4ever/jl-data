module Orthopolys
using Polynomials

#export chebyshevT, chebyshevU
#export gegenbauer
export hermiteH, hermiteHe
#export jacobi
#export laguerre
export legendre

"""
Generates additional signatures for user convenience.

It assumes that the function `f` is defined with the signature

    f(::Type, n::Integer, sym::Symbol)

It then uses that to generate the additional signatures with the definitions

    f(n::Integer) = f(default_type, n)                                         \
    f(n::Integer, sym::Symbol) = f(default_type, n, sym)
"""
macro signatures(f, default_type)
    quote
        $(esc(f))(n::Integer) = $(esc(f))($(esc(default_type)), n)
        $(esc(f))(n::Integer, sym::Symbol) = $(esc(f))($(esc(default_type)), n, sym)
    end
end

#include("chebyshev.jl")
#include("gegenbauer.jl")
include("hermite.jl")
#include("jacobi.jl")
#include("laguerre.jl")
include("legendre.jl")

end # module
