function log_sum_exp(a::Float64, b::Float64)
    if a > b
        return a + log(1 + exp(b-a))
    else
        return b + log(1 + exp(a-b))
    end
end

function log_sum_exp(a::Vector{Float64})
    max_a = maximum(a)
    max_a + log(sum(exp(a - max_a)))
end
