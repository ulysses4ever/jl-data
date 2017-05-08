# Routines for differentiating a spline (exactly)

#=
    \[\frac{d}{dx}B_{i,k,t}(x)=(k-1)\left[
    \frac{B_{i,k-1,t}(x)}{t_{i+k-1}-t_i}-
    \frac{B_{i+1,k-1,t}(x)}{t_{i+k}-t_{i+1}}
    \right]\]

    \[\implies\frac{d}{dx}f(x)=\sum_i(k-1)\frac{\alpha_i-\alpha_{i-1}}{t_{i+k-1}-t_i}B_{i,k-1}\]
=#
function ∂f∂x{T<:FloatingPoint, C<:Number}(f::Spline{T,C})
    function num(i)
        d = f.t[f.k+i-1]-f.t[i]
        d == 0 ? zero(T) : one(T)/d
    end
    αd = (f.k-1)*convert(Vector{C}, vcat(f.α[1]*num(1),
                                         [(f.α[i]-f.α[i-1])*num(i) for i=2:length(f.α)]...,
                                         -f.α[end]*num(length(f.α)+1)))
    Spline{T,C}(f.k-1, f.t, αd)
end

function ∂ⁿf∂xⁿ{T<:FloatingPoint,C<:Number}(f::Spline{T,C}, n::Integer)
    n == 0 ? f : ∂f∂x(n == 1 ? f : ∂ⁿf∂xⁿ(f, n-1))
end

# Construct a matrix representation of the derivative operator
# \(\{\frac{d^n}{dx^n}B_{i,k,t}(x)\}\), \(\forall i\), with optionally
# the first two splines combined to allow \(\frac{d^n}{dx^n}f(0)=0\),
# when solving eigenvalue problems.
function diff_matrix{T}(n::Integer, k::Integer,
                        t::Vector{T}, x::Vector{T},
                        boundary=0)
    if n<0
        throw("n must be non-negative!")
    end
    B = bsplvb(k-n, t, x) # Find the basis \(B_{k-n,t}\).
    Nspl = length(t)-k
    # Find the weights of \(\frac{d^n}{dx^n}\).
    D = hcat([∂ⁿf∂xⁿ(Spline(k, t,
                            [j==i || (j==2 && boundary==1) ?
                             one(T) : zero(T)
                             for j=1:Nspl]),
                     n).α
              for i=1:Nspl]...)
    # Compute the matrix of \(\frac{d^n}{dx^n}\).
    B*D
end
