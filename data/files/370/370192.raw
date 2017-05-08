#! /usr/bin/julia

# Rosetta Code, Number names

const stext = ["one", "two", "three", "four", "five",
               "six", "seven", "eight", "nine"]
const teentext = ["eleven", "twelve", "thirteen", "fourteen",
                  "fifteen", "sixteen", "seventeen",
                  "eighteen", "nineteen"]
const tenstext = ["ten", "twenty", "thirty", "forty", "fifty",
                  "sixty", "seventy", "eighty", "ninety"]
const ordstext = ["thousand", "million", "billion", "trillion",
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

function digits2text!{T<:Integer}(d::Array{T,1})
    ndig = normalize_digits!(d)
    0 < ndig || return ""
    if ndig < 4
        s = ""
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
    nord = div(ndig, 3)
    if ndig%3 == 0
        nord -= 1
    end
    s = digits2text!(d[1:3])
    d = d[4:end]
    for i in 1:(nord-1)
        t = digits2text!(d[1:3])
        d = d[4:end]
        0 < length(t) || continue
        t = t*" "*ordstext[i]
        if length(s) == 0
            s = t
        else
            s = t*" "*s
        end
    end
    t = digits2text!(d)*" "*ordstext[nord]
    0 < length(s) || return t
    return t*" "*s
end

function num2text{T<:Integer}(n::T)
    -1 < n || return "minus "*num2text(-n)
    0 < n || return "zero"
    n < big(10)^66 || return "too big to say"
    return digits2text!(digits(n, 10))
end
