module TR55

# Calculates the runoff (in) based off:
# S (potential maximum retention after runoff begins)
# P (rainfall (in))
function runoff(S::Number, P::Number)
    Q = (P - (0.2 * S))^2 / (P + (0.8 * S))

    return round(Q, 2)
end

# Calculates the potential maximum retention
# after runoff begins based off:
# CN (runoff curve number)
function max_retention(CN::Int64)
    S = (1000 / CN) - 10

    return round(S, 2)
end

end # module
