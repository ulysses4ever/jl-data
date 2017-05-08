#! /usr/bin/julia

# Rosetta Code, Number names

const stext = ["one", "two", "three", "four", "five",
               "six", "seven", "eight", "nine"]
const teentext = ["eleven", "twelve", "thirteen", "fourteen",
                  "fifteen", "sixteen", "seventeen",
                  "eighteen", "nineteen"]
const tenstext = ["ten", "twenty", "thirty", "forty", "fifty",
                  "sixty", "seventy", "eighty", "ninety"]
const ordstext = ["million", "billion", "trillion",
                  "quadrillion", "quintillion", "sextillion",
                  "septillion", "octillion", "nonillion",
                  "decillion", "undecillion", "duodecillion",
                  "tredecillion", "quattuordecillion", "quindecillion",
                  "sexdecillion", "septendecillion", "octodecillion",
                  "novemdecillion", "vigintillion"]

function normalize_digits!{T<:Integer}(a::Array{T,1})
    while  0 < length(a) && a[end] == 0
        pop!(a)
    end
    return length(a)
end

function digits2text!{T<:Integer}(d::Array{T,1}, use_short_scale=true)
    ndig = normalize_digits!(d)
    0 < ndig || return ""
    if ndig < 7
        s = ""
        if 3 < ndig
            t = digits2text!(d[1:3])
            s = digits2text!(d[4:end])*" thousand"
            0 < length(t) || return s
            if contains(t, "and")
                return s*" "*t
            else
                return s*" and "*t
            end
        end
        if ndig == 3
            s *= stext[pop!(d)]*" hundred"
            ndig = normalize_digits!(d)
            0 < ndig || return s
            s *= " and "
        end
        1 < ndig || return s*stext[pop!(d)]
        j, i = d
        j != 0 || return s*tenstext[i]
        i != 1 || return s*teentext[j]
        return s*tenstext[i]*"-"*stext[j]
    end
    s = digits2text!(d[1:6])
    d = d[7:end]
    dgrp = use_short_scale ? 3 : 6
    ord = 0
    while(dgrp < length(d))
        ord += 1
        t = digits2text!(d[1:dgrp])
        d = d[(dgrp+1):end]
        0 < length(t) || continue
        t = t*" "*ordstext[ord]
        if length(s) == 0
            s = t
        else
            s = t*" "*s
        end
    end
    ord += 1
    t = digits2text!(d)*" "*ordstext[ord]
    0 < length(s) || return t
    return t*" "*s
end

function num2text{T<:Integer}(n::T, use_short_scale=true)
    -1 < n || return "minus "*num2text(-n, use_short_scale)
    0 < n || return "zero"
    toobig = use_short_scale ? big(10)^66 : big(10)^126
    n < toobig || return "too big to say"
    return digits2text!(digits(n, 10), use_short_scale)
end

function wrap{T<:String,U<:Integer}(str::T, width::U=70, indent::U=4)
    sdent = " "^(indent-1)
    s = sdent
    llen = indent
    for t in split(str, " ")
        s *= " "*t
        llen += length(t) + 1
        width < llen || continue
        s *= "\n"*sdent
        llen = indent
    end
    return rstrip(s)
end
    
println("Testing num2text")
println()    
println("Some easy ones to start with")
println()
tests = [-1:21, 100, 101, 10000, 10001, 1000000, 1010101]
for i in tests
    println(@sprintf("%8d is %s", i, num2text(i)))
end

println()
println("Some larger numbers")
println()
println("The largest signed literal integer (short-scale)")
i = typemax(1)
println("    ", i, " is")
println(wrap(num2text(i)))
println()
println("The largest signed literal integer (long-scale)")
println("    ", i, " is")
println(wrap(num2text(i, false)))
println()
println("The largest unsigned integer (short-scale)")
i = typemax(Uint128)
println("    ", i, " is")
println(wrap(num2text(i)))
println()
println("50! (short-scale)")
i = factorial(big(50))
println("    ", i, " is")
println(wrap(num2text(i)))
println()
println("51! (short-scale)")
i = factorial(big(51))
println("    ", i, " is")
println(wrap(num2text(i)))
println()
println("51! (long-scale)")
println("    ", i, " is")
println(wrap(num2text(i, false)))

