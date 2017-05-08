#=
    \[B_{i,1,t}(x) = \begin{cases}
    1, & x \in [t_i, t_{i+1})\\
    0, & \textrm{else}
    \end{cases}\]
=#
B₁{T<:FloatingPoint}(i::Integer, t::Vector{T}) = x::Real -> (t[i] <= x < t[i+1]) ? one(T) : zero(T)

#=
    \[B_{i,k,t}(x)=\frac{x-t_i}{t_{i+k-1}-t_i}B_{i,k-1,t}(x)-
    \frac{t_{i+k}-x}{t_{i+k}-t_{i+1}}B_{i+1,k-1,t}(x)\]
=#
function B{T<:FloatingPoint}(i::Integer, k::Integer, t::Vector{T})
    if k==1
        B₁(i, t)
    else
        function(x::Real)
            d₁ = t[i+k-1]-t[i]
            d₂ = t[i+k]-t[i+1]
            f₁ = d₁ == 0 ? 0 : convert(T, (x-t[i])/d₁)
            f₂ = d₂ == 0 ? 0 : convert(T, (t[i+k]-x)/d₂)
            f₁*B(i,k-1,t)(x) + f₂*B(i+1,k-1,t)(x)
        end
    end
end

#=
    \[f(x)=\sum_i\alpha_iB_{i,k,t}(x)\equiv \mathsf{B}_{k,t}(x)\vec{\alpha}.\]

    This function calculates the matrix \(B_{k,t}(x) = \{B_{i,k,t}(x)\}\), \(\forall i\).
=#
function bsplvb{T<:FloatingPoint}(k::Integer, t::Vector{T}, x::Vector{T})
    bi = [B(i,k,t) for i=1:length(t)-k]
    hcat([convert(Array{T,1},[b(x[j]) for j=1:length(x)]) for b=bi]...)
end
