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
   via Julia High Performance by Avik Sengupta (pp 59-62)
=#
# from base
macro Horner(x, p...)
    ex = esc(p[end])
    for i = length(p)-1:-1:1
        ex = :(muladd(t, $ex, $(esc(p[i]))))
    end
    Expr(:block, :(t = $(esc(x))), ex)
end

polyvalHorner(x) = @Horner(x, coeffs)

# from base, with fma instead of muladd
macro HornerFMA(x, p...)
    ex = esc(p[end])
    for i = length(p)-1:-1:1
        ex = :(fma(t, $ex, $(esc(p[i]))))
    end
    Expr(:block, :(t = $(esc(x))), ex)
end

polyvalHornerFMA(x) = @HornerFMA(x, coeffs)



#=
https://github.com/JuliaLang/julia/pull/2987/commits/9c24795ac2918df7b8cba9bb129db8c535d321e8
+# evaluate p[1] + x * (p[2] + x * (....)), i.e. a polynomial via Horner's rule
 +macro horner(x, p...)
 +    ex = p[end]
 +    for i = length(p)-1:-1:1
 +        ex = :($(p[i]) + $x * $ex)
 +    end
 +    ex
 +end
 +
 +# Compute the inverse of the error function: erf(erfinv(x)) == x, 
 +# using the rational approximants tabulated in:
 +#     J. M. Blair, C. A. Edwards, and J. H. Johnson, "Rational Chebyshev 
 +#     approximations for the inverse of the error function," Math. Comp. 30,
 +#     pp. 827--830 (1976).
 +#         http://dx.doi.org/10.1090/S0025-5718-1976-0421040-7 
 +#         http://www.jstor.org/stable/2005402
 +function erfinv(x::Float64)
 +    a = abs(x)
 +    if a >= 1.0
 +        if x == 1.0
 +            return inf(Float64)
 +        elseif x == -1.0
 +            return -inf(Float64)
 +        end
 +        throw(DomainError())
 +    elseif a <= 0.75 # Table 17 in Blair et al.
 +        t = x*x - 0.5625
 +        return x * @horner(t, 0.16030_49558_44066_229311e2, 
 +                             -0.90784_95926_29603_26650e2,
 +                              0.18644_91486_16209_87391e3,
 +                             -0.16900_14273_46423_82420e3,
 +                              0.65454_66284_79448_7048e2,
 +                             -0.86421_30115_87247_794e1,
 +                              0.17605_87821_39059_0) /
 +                   @horner(t, 0.14780_64707_15138_316110e2,
 +                             -0.91374_16702_42603_13936e2,
 +                              0.21015_79048_62053_17714e3,
 +                             -0.22210_25412_18551_32366e3,
 +                              0.10760_45391_60551_23830e3,
 +                             -0.20601_07303_28265_443e2,
 +                              0.1e1)
 =#
#=
Base:math.jl

# evaluate p[1] + x * (p[2] + x * (....)), i.e. a polynomial via Horner's rule
macro horner(x, p...)
    ex = esc(p[end])
    for i = length(p)-1:-1:1
        ex = :(muladd(t, $ex, $(esc(p[i]))))
    end
    Expr(:block, :(t = $(esc(x))), ex)
end

# Evaluate p[1] + z*p[2] + z^2*p[3] + ... + z^(n-1)*p[n].  This uses
# Horner's method if z is real, but for complex z it uses a more
# efficient algorithm described in Knuth, TAOCP vol. 2, section 4.6.4,
# equation (3).
macro evalpoly(z, p...)
    a = :($(esc(p[end])))
    b = :($(esc(p[end-1])))
    as = []
    for i = length(p)-2:-1:1
        ai = Symbol("a", i)
        push!(as, :($ai = $a))
        a = :(muladd(r, $ai, $b))
        b = :($(esc(p[i])) - s * $ai) # see issue #15985 on fused mul-subtract
    end
    ai = :a0
    push!(as, :($ai = $a))
    C = Expr(:block,
             :(x = real(tt)),
             :(y = imag(tt)),
             :(r = x + x),
             :(s = muladd(x, x, y*y)),
             as...,
             :(muladd($ai, tt, $b)))
    R = Expr(:macrocall, Symbol("@horner"), :tt, map(esc, p)...)
    :(let tt = $(esc(z))
          isa(tt, Complex) ? $C : $R
      end)
end

  http://stackoverflow.com/questions/28077057/julia-evalpoly-macro-with-varargs

  from Erik Schnetter
  c=[1,2,3,4]
  @eval begin
    function f()
        @evalpoly 0.5 $(c...)
    end
end
=#
#=
Investigation of different methods of fast polynomial evaluation
Gavin S. Reynolds
September 2010
MSc in High Performance Computing
The University of Edinburgh
Year of Presentation: 2010

The Optimised Brute Force function pre-calculates the value of x^2 and use it where possible in
building up the powers for each monomial. For example, if a monomial contains x^7, instead of
7 multiplications of x by x, the function would multiply x^2 by x^2three times then multiply it by x
once. In this example, this would save three multiplications.

function hornerform(x,coeffs)
    n = length(coeffs)
    z = coeffs[1]*x
    for i in 2:(n-1)
         z = (z + coeffs[i])*x
    end
    z + coeffs[n]
end

function bruteforce(x,coeffs)
    n = length(coeffs)
    monomials = zeros(typeof(x),n)
    for i in 1:(n-1)
        monomials[i] = coeffs[i] * (x^(n-i))
    end
    monomials[n] = coeffs[n]
    sum(monomials)
end

function optforce(x,coeffs)
    n = length(coeffs)
    monomials = zeros(typeof(x),n)
    x2 = x*x
    for i in 1:(n-1)
        monomials[i] = coeffs[i]
        numsteps = (n-i) >> 1 # fld(n-i,2)
        for k in 1:numsteps
           monomials[k] *= x2
        end
        if isodd(n-i)
            monomial[i] *= x
        end
    end
    monomial[n] = coeffs[n]
    sum(monomials)
end

end
=#
