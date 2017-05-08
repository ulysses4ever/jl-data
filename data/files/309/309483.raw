const EPS64 = eps(Float64)

function metric1(scale::FixedNominal, a::Vector, b::Vector, i, j)
    r = scale.range
    actual = [counts(a, r), counts(b, r)]

    expected = vcat(scale.counts[[i,j]]...)

    1.0 / (p_value(ChisqTest, actual, expected) + EPS64)
 end

function metric1(scale::Cardinal, a::Vector, b::Vector, i , j)
    0.5 / (pvalue(UnequalVarianceTTest(a, b)) + EPS64) +
    0.5 / (pvalue(MannWhitneyUTest(a, b)) + EPS64)
end
