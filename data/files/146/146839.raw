using Optim: optimize

function irr{T<:Real}(cash_flow::Vector{T})
    fmin(irr::Real) = presentValue(irr, cash_flow)^2
    return optimize(fmin, 1e-10, 1.0 ).minimum
end

function presentValue{T<:Real}(r::Real, cash_flow::Vector{T})
    n = length(cash_flow)
    sum = 0.0
    for i=1:n
        sum += singleTerm(r, i-1, cash_flow[i])
    end
    return sum
end

function singleTerm(r::Real, n::Int, future_value::Real)
    return future_value/(1+r)^n
end

##################################

function equalPay_dicount(monthRate, totalMonth, leftMonth, fraction)
    base = 1 + monthRate
    cash_flow = [fraction*(base^(totalMonth - leftMonth) - base^totalMonth); repmat([monthRate * base^totalMonth], leftMonth)]
    return irr(cash_flow)
end

function equalPay(monthRate, totalMonth)
    return equalPay_dicount(monthRate, totalMonth, totalMonth, 1.0)
end
