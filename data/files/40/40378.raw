module TR55

# Calculates the runoff (in) based off
# s (potential maximum retention after runoff begins)
# p (rainfall (in))
function runoff(S, P)
    Q = (P - (0.2 * S))^2 / (P + (0.8 * S))

    return round(Q, 2)
end

# Calculates the potential maximum retention
# after runoff begins based off
# cn (runoff curve number)
function max_retention(CN)
    S = (1000 / CN) - 10

    return round(S, 2)
end

end # module
