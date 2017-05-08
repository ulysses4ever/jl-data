function getmetric(scale::CardinalData, sp::SplitOut, metric::Function)
    vec, ranges = sp
    col = scale.data
    n = length(ranges)
    v = {dropna(col[view(vec, ranges[i])]) for i=1:n}
    x = 0.0
    for i in 1:(n - 1)
        for j in (i + 1):n
            x += metric(scale, v[i], v[j], i, j)
        end
    end
    x
end

function getmetric(scale::Scale, sp::SplitOut, metric::Function)
    vec, ranges = sp
    col = scale.data
    n = length(ranges)
    v = {col[view(vec, ranges[i])] for i=1:n}
    x = 0.0
    for i in 1:(n - 1)
        for j in (i + 1):n
            x += metric(scale, v[i], v[j], i, j)
        end
    end
    x
end

function getmetrics(scales::WeightedScales, s::SplitOut, metric::Function)
    x = 0.0
    for scale in scales
        error("Nail down WeightedScales")
        x += scale.weight * getmetric(scale, s, metric)
    end
    x
end

function getmetrics(scales::EvenScales, s::SplitOut, metric::Function)
    x = 0.0
    for scale in scales
        x += getmetric(scale, s, metric)
    end
    x
end
