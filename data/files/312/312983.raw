#! /usr/bin/julia

# Rosetta Code, Stem-and-leaf plot


function stemleaf{T<:Real}(a::Array{T,1}, leafsize=1)
    ls = 10^int(log10(leafsize))
    (stem, leaf) = divrem(sort(int(a/ls)), 10)
    leaf[sign(stem) .== -1] *= -1
    negzero = leaf .< 0
    if any(negzero)
        leaf[negzero] *= -1
        nz = @sprintf "%10s | " "-0"
        nz *= join(map(string, leaf[negzero]), " ")
        nz *= "\n"
        stem = stem[!negzero]
        leaf = leaf[!negzero]
    else
        nz = ""
    end
    slp = ""
    for i in stem[1]:stem[end]
        i != 0 || (slp *= nz)
        slp *= @sprintf "%10d | " i
        slp *= join(map(string, leaf[stem .== i]), " ")
        slp *= "\n"
    end
    slp *= " Leaf Unit = " * string(convert(T, ls)) * "\n"
    return slp
end

println("Using the Task's Test Data")
test = """12 127 28 42 39 113 42 18 44 118 44 37 113 124 37 48 127 36 29
   31 125 139 131 115 105 132 104 123 35 113 122 42 117 119 58 109 23 105
   63 27 44 105 99 41 128 121 116 125 32 61 37 127 29 113 121 58 114 126
   53 114 96 25 109 7 31 141 46 13 27 43 117 116 27 7 68 40 31 115 124 42
   128 52 71 118 117 38 27 106 33 117 116 111 40 119 47 105 57 122 109
   124 115 43 120 43 27 27 18 28 48 125 107 114 34 133 45 120 30 127 31
   116 146"""
test = map(parseint, split(test, r"\s"))
println(stemleaf(test))

println("Test with Reals and Negative Zero Stem")
test = [-23.678758, -12.45, -3.4, 4.43, 5.5, 5.678, 16.87, 24.7, 56.8]
println(stemleaf(test))

println("Test with Leaf Size Scaling")
test = int(500*randn(20))
println("Using:  ", test)
println(stemleaf(test, 10))
