#! /usr/bin/julia

# Rosetta Code, Ordered words

function isordered{T<:String}(w::T)
    p = '\0'
    for c in w
        p <= c || return false
        p = c
    end
    return true
end

maxlen = 0
wlst = String[]
WL = open("ordered_words.txt", "r")

for w in eachline(WL)
    w = chomp(w)
    wlen = length(w)
    wlen>=maxlen && isordered(w) || continue
    if wlen > maxlen
        maxlen = wlen
        wlst = [w]
    else
        push!(wlst, w)
    end
end
close(WL)

for w in wlst
    println("    ", w)
end


