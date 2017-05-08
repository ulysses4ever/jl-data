const numbers = Dict{Int,String}(
    0  => "",
    1  => "one",
    2  => "two",
    3  => "three",
    4  => "four",
    5  => "five",
    6  => "six",
    7  => "seven",
    8  => "eight",
    9  => "nine",
    10 => "ten",
    11 => "eleven",
    12 => "twelve",
    13 => "thirtenn",
    14 => "fourteen",
    15 => "fifteen",
    16 => "sixteen",
    17 => "seventeen",
    18 => "eighteen",
    19 => "nineteen",
    20 => "twenty",
    30 => "thirty",
    40 => "forty",
    50 => "fifty",
    60 => "sixty",
    70 => "seventy",
    80 => "eighty",
    90 => "ninety",
    100 => "hundred",
)

ndigits(n::Int) = n |> log10 |> floor |> int

function say_number(n::Int)
    @assert n > 0
    @assert ndigits(n) < 4
    # hundreds
    words = ASCIIString[]
    push_hundreds!(n, words)
    push_tens!(n, words)
    push_ones!(n, words)
    join(words, " ")
end

function push_hundreds!(n, words)
    if ndigits(n) > 1
        hd = div(n, 100)
        a = n % 100 == 0 ? "" : "and"
        push!(words, "$(numbers[hd]) hundred $a")
    end
end

function push_tens!(n, words)
    if (ndigits(n) > 0)
        td = n % 100
        td = td > 20 ? td - td % 10 : td
        push!(words, "$(numbers[td])")
    end
end

function push_ones!(n, words)
    if ~(n % 10 in [10, 20]) & ~(10 < n % 100 < 20)
        od = n % 10
        push!(words, "$(numbers[od])")
    end
end

function letter_sum()
    s = 0
    for i=1:999
        s += length(replace(say_number(i), " ", ""))
    end
    s + 11  # for "onethousand"
end
