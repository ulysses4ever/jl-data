true # true
false # false

1 # 1
typeof(1) # Int64

1.0 # 1.0
typeof(1.0) # Float64

1 == 1.0 # true
1 === 1.0 # false

isa(1, Int64) # true

isa(1, Int) # true

typeof("a") # ASCIIString
typeof('a') # Char
typeof("λ") # UTF8String

# Vector (i.e. 1-d array)

a1 = ["a", "b", "c"]
typeof(a1) # Array{ASCIIString,1}

push!(a1, "d")
a1 # ["a", "b", "c", "d"]

a1[0] # BoundsError (Julia arrays are 1-indexed)
a1[1] # "a"
a1[end] # "d"
a1[endof(a1)] # "d"

a1[1:2] # First two elements
a1[end-1:end] # Last two elements

a2 = ["e", "f", "g", "h"]

vcat(a1, a2) # ["a", "b", ..., "g", "h"]

# Tuple

t1 = ("a", "b", "c")
typeof(t1) # Tuple{ASCIIString,ASCIIString,ASCIIString}
t2 = ("a", 1.0, :hello)
typeof(t2) # Tuple{ASCIIString,Float64,Symbol}

# Dictionary

d1 = Dict("a"=>1, "b"=>2)
typeof(d1) # Dict{Symbol,Int64}
d1["c"] = 3

# Set
s1 = Set([1, 2, 2, 1, 3, 2])
s1 # e.g. Set([2,3,1])
