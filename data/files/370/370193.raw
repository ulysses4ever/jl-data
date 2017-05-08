#! /usr/bin/julia

# Rosetta Code, Permutation test

delta_mean{T<:Real}(a::Array{T,1}, b::Array{T,1}) = mean(a) - mean(b)

function bifurcate{T<:Integer}(a::AbstractVector, sel::Array{T,1})
    x = a[sel]
    asel = trues(length(a))
    asel[sel] = false
    y = a[asel]
    return (x, y)
end

function perm_sig_test{T<:Real}(treat::Array{T,1}, control::Array{T,1})
    base_effect = delta_mean(treat, control)
    pool = [treat, control]
    tlen = length(treat)
    plen = length(pool)
    better = 0
    worse = 0
    for s in combinations(1:plen, tlen)
        (t, c) = bifurcate(pool, s)
        if base_effect < delta_mean(t, c)
            better += 1
        else
            worse += 1
        end
    end
    return (better, worse)
end
    
treat = [85, 88, 75, 66, 25, 29, 83, 39, 97]
control = [68, 41, 10, 49, 16, 65, 32, 92, 28, 98]

(better, worse) = perm_sig_test(treat, control)

tot = better + worse

println("Permutation test using the following data:")
println("Treated:  ", treat)
println("Control:  ", control)

println()
println("There are ", tot, " different permuted groups of these data.")
print(@sprintf("%8d, %5.2f%% ", better, 100better/tot))
println("showed better than actual results.")
print(@sprintf("%8d, %5.2f%% ", worse, 100worse/tot))
println("showed equalivalent or worse results.")
