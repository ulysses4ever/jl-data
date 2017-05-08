#! /usr/bin/julia

# Rosetta Code, Find the missing permutation

function find_missing_permutations{T<:String}(a::Array{T,1})
    std = unique(sort(split(a[1], "")))
    needsperm = trues(factorial(length(std)))
    for s in a
        b = split(s, "")
        p = map(x->findfirst(std, x), b)
        isperm(p) || throw(DomainError())
        needsperm[nthperm(p)] = false
    end
    mperms = T[]
    for i in findn(needsperm)[1]
        push!(mperms, join(nthperm(std, i), ""))
    end
    return mperms
end

test = ["ABCD", "CABD", "ACDB", "DACB", "BCDA", "ACBD",
        "ADCB", "CDAB", "DABC", "BCAD", "CADB", "CDBA",
        "CBAD", "ABDC", "ADBC", "BDCA", "DCBA", "BACD",
        "BADC", "BDAC", "CBDA", "DBCA", "DCAB"]

missperms = find_missing_permutations(test)

print("The test list is:\n    ")
i = 0
for s in test
    print(s, " ")
    i += 1
    i %= 5
    i != 0 || print("\n    ")
end
i == 0 || println()
if length(missperms) > 0
    println("The following permutations are missing:")
    for s in missperms
        println("    ", s)
    end
else
    println("There are no missing permutations.")
end



    
