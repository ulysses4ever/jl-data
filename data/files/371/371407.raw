function iterate(fn::Function, initval::Number, k::Integer)
  x = sizehint([initval], k)
  for _ in 1:k-1
    push!(x, fn(x[end]))
  end
  x
end

function fixedpoint(x::Array{Float64, 1}; ϵ::Float64=1e-4)
  findfirst(d -> d < ϵ, abs(diff(x)))
end
