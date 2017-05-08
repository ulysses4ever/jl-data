
function SimpleTest{T1<:Real}(pdedata::SolvData, mu_actual::Vector{T1}, nu_actual::Vector{T1}, v0::Vector{T1}, epsilon::T1, beta::Vector{T1}, delta::T1, l::T1, R::T1, s0::T1, show_trace::Bool)
  function func{T<:Real}(v::Vector{T})
    center = ones(T,length(v))
    return sumabs2(v - center)
  end
  return func
end

for func=(:SimpleTest,)
  @eval begin
    $(func){T1<:Real}(pdedata::SolvData, mu_actual::Vector{T1}, nu_actual::Vector{T1}, v0::Vector{T1}, epsilon::T1, beta::Vector{T1}, delta::T1, l::T1, R::T1, s0::T1) = $(func)(pdedata, mu_actual, nu_actual, v0, epsilon, beta, delta, l, R, s0, true)
    $(func){T1<:Real}(pdedata::SolvData, mu_actual::Vector{T1}, nu_actual::Vector{T1}, v0::Vector{T1}, epsilon::T1, beta::Vector{T1}, delta::T1, l::T1, R::T1) = $(func)(pdedata, mu_actual, nu_actual, v0, epsilon, beta, delta, l, R, v0[1])
    $(func){T1<:Real}(pdedata::SolvData, mu_actual::Vector{T1}, nu_actual::Vector{T1}, v0::Vector{T1}, epsilon::T1, delta::T1, l::T1, R::T1) = $(func)(pdedata, mu_actual, nu_actual, v0, epsilon, [one(T1), one(T1)], delta, l, R)
    $(func){T1<:Real}(pdedata::SolvData, mu_actual::Vector{T1}, nu_actual::Vector{T1}, v0::Vector{T1}, delta::T1, l::T1, R::T1) = $(func)(pdedata, mu_actual, nu_actual, v0, zero(T1), delta, l, R)
    $(func){T1<:Real}(pdedata::SolvData, u::Function, v0::Vector{T1}, delta::T1, l::T1, R::T1) = $(func)(pdedata, T1[u(s(t), t) for t in pdedata.grid.tgrid], T1[u(zero(t), t) for t in pdedata.grid.tgrid], v0, zero(T1), delta, l, R)
  end
end
