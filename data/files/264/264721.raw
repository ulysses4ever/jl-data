import FastGaussQuadrature: gausslegendre

#=
    Gaußian quadrature:

    \[\int\limits_a^b dx\;f(x)\approx
    \frac{b-a}{2}\sum_{i=1}^n w_i
    f\left(\frac{b-a}{2}x_i+\frac{a+b}{2}\right)\]
=#

function lgwt{T<:FloatingPoint}(x::Vector{T}, w::Vector{T},
                                a::T=zero(T), b::T=one(T))
    0.5((b-a)*x + a + b), 0.5(b-a)*w
end

# Return the evaluation points and weights for Gauß–Legendre
# quadrature given a knot sequence \(\{t_i\}\) and an order \(k\).
function lgwt{T<:FloatingPoint}(N::Integer, k::Integer, t::Vector{T})
    x, w = gausslegendre(k+1)

    xw = [zip([lgwt(x, w, t[k+i-1], t[k+i]) for i=1:N]...)...]
    vcat(xw[1]...),vcat(xw[2]...)
end
