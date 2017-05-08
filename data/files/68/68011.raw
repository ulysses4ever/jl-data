module ClusterAnalysis

export adjusted_rand_index

function adjusted_rand_index(labels::Array{Int64}, expected::Array{Int64})
    a = b = c = d = 0
    if length(labels) != length(expected)
        error("Trying to compute Adjusted Rand Index for different length arrays!")
    end
    n = length(labels)
    for i = 1:n
        for j = (i+1):n
            if labels[i] == labels[j] && expected[i] == expected[j]
                a += 1
            elseif labels[i] == labels[j] && expected[i] != expected[j]
                b += 1
            elseif labels[i] != labels[j] && expected[i] == expected[j]
                c += 1
            else
                d += 1
            end
        end
    end
    m = n * (n-1) / 2.
    top = a - ((a+c)*(a+b)) / m
    bottom = ((a+c)+(a+b)) / 2.0 - ((a+c)*(a+b)) / m
    return bottom != 0.0 ? top / bottom : 0.0
end

end
