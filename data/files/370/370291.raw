#! /usr/bin/julia

# Rosetta Code, Ranking methods

function ties{T<:Real}(a::Array{T,1})
    unique(a[2:end][a[2:end] .== a[1:end-1]])
end

function rankstandard{T<:Real}(a::Array{T,1})
    r = collect(1:length(a))
    1 < r[end] || return r
    for i in ties(a)
        r[a.==i] = r[a.==i][1]
    end
    return r
end

function rankmodified{T<:Real}(a::Array{T,1})
    indexin(a, a)
end

function rankdense{T<:Real}(a::Array{T,1})
    indexin(a, unique(a))
end

function rankordinal{T<:Real}(a::Array{T,1})
    collect(1:length(a))
end

function rankfractional{T<:Real}(a::Array{T,1})
    r = float64(collect(1:length(a)))
    1.0 < r[end] || return r
    for i in ties(a)
        r[a.==i] = mean(r[a.==i])
    end
    return r
end

scores = [44, 42, 42, 41, 41, 41, 39]
names = ["Solomon", "Jason", "Errol", "Garry",
         "Bernard", "Barry", "Stephen"]

srank = rankstandard(scores)
mrank = rankmodified(scores)
drank = rankdense(scores)
orank = rankordinal(scores)
frank = rankfractional(scores)

println("    Name    Score  Std  Mod  Den  Ord  Frac")
for i in 1:length(scores)
    print(@sprintf("   %-7s", names[i]))
    print(@sprintf("%5d ", scores[i]))
    print(@sprintf("%5d", srank[i]))
    print(@sprintf("%5d", mrank[i]))
    print(@sprintf("%5d", drank[i]))
    print(@sprintf("%5d", orank[i]))
    print(@sprintf("%7.2f", frank[i]))
    println()
end
                                                                      
