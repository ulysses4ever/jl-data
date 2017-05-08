# adjusted Rand index
# (L. Hubert and P. Arabie (1985) "Comparing Partitions" Journal of Classification 2:193-218)
# copied from http://www.kernel-methods.net/matlab/algorithms/adjrand.m

function adjusted_rand_index(labels1::Array{Int}, labels2::Array{Int})
    n = length(labels1)
    k1 = maximum(labels1)
    k2 = maximum(labels2)
    Cont = zeros(k1, k2)
    for i = 1 : n
        Cont[labels1[i],labels2[i]] += 1
    end
    row_sum = sum(Cont, 2)
    col_sum = sum(Cont, 1)
    a = 0
    for i = 1 : k1
        for j = 1 : k2
            if Cont[i,j] >= 0
                a += 0.5 * Cont[i,j] * (Cont[i,j] - 1)
            end
        end
    end
    b1 = 0
    b2 = 0
    for i = 1 : k1
        if row_sum[i] >= 0
            b1 += 0.5 * row_sum[i] * (row_sum[i] - 1)
        end
    end
    for i = 1 : k2
        if col_sum[i] >= 0
            b2 += 0.5 * col_sum[i] * (col_sum[i] - 1)
        end
    end
    c = 0.5 * n * (n - 1)
    (a - b1*b2/c) / (0.5*(b1 + b2) - b1*b2/c)
end
