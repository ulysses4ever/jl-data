# from Polynomials.jl (Poly)

"""
* `FastPoly{T<:Number}(a::Vector)`: Construct a polynomial from its coefficients, lowest order first. That is if `p=a_n x^n + ... + a_2 x^2 + a_1 x^1 + a_0`, we construct this through `Poly([a_0, a_1, ..., a_n])`.
Example:
```
FastPoly([1,0,3,4])    # FastPoly(1 + 3x^2 + 4x^3)
```
An optional variable parameter can be added:
```
FastPoly([1,2,3], :s)       # FastPoly(1 + 2s + 3s^2)
```
"""
immutable FastPoly{T<:Number}
    a::Vector{T}
    var::Symbol
    function Poly(a::Vector{T}, var)
        # if a == [] we replace it with a = [0]
        if length(a) == 0
            return new(zeros(T,1), symbol(var))
        else
            # determine the last nonzero element and truncate a accordingly
            a_last = max(1,findlast(a))
            new(a[1:a_last], symbol(var))
        end
    end
end
#=
   via Julia High Performance by Avik Sengupta
=#
# from base
macro Horner(x, p...)
    ex = esc(p[end])
    for i = length(p)-1:-1:1
        ex = :(muladd(t, $ex, $(esc(p[i]))))
    end
    Expr(:block, :(t = $(esc(x))), ex)
end

f_Horner_macro(x) = @Horner(x, coeffs...)

# from base, with fma instead of muladd
macro HornerFMA(x, p...)
    ex = esc(p[end])
    for i = length(p)-1:-1:1
        ex = :(fma(t, $ex, $(esc(p[i]))))
    end
    Expr(:block, :(t = $(esc(x))), ex)
end

f_HornerFMA_macro(x) = @hornerFMA(x, coeffs...)



