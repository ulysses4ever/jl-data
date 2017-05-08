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

# Calculates the weighted curve number
# for a watershed.
# region - array of dicts w/ the following structure:
#   [
#       {
#           "cn" => 61,
#           "area" => 30
#       },
#       {
#           "cn" => 74,
#           "area" => 70
#       },
#   ]
# area_is_percent - boolean indicating whether or not
# the region areas are measured in percent of area,
# instead of acres or sq mi, etc.
function weighted_cn(regions::Array{Dict{Any,Any}},
                     area_is_percent::Bool)

    total_area = reduce(+, map(x -> x["area"], regions))

    if area_is_percent && total_area != 100
        error("Using percents areas requires that " *
              "region areas sum to 100")
    end

    total_product = reduce(+, map(x -> x["area"] * x["cn"], regions))
    weighted_CN = total_product / total_area

    return convert(Int64, round(weighted_CN))
end

end # module
