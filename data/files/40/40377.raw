module TR55

# Calculates the runoff (in) based off
# s (potential maximum retention after runoff begins)
# p (rainfall (in))
function q(s, p)
    Q = (p - (0.2 * s))^2 / (p + (0.8 * s))

    return round(Q, 2)
end

# Calculates the potential maximum retention
# after runoff begins based off
# cn (runoff curve number)
function s(cn)
    S = (1000 / cn) - 10

    return round(S, 2)
end

end # module
