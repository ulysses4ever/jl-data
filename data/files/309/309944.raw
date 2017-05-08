using DictIO
using Base.Test

# ASCIIString,Int64 dict
d = Dict{ASCIIString,Int64}()
d["a"] = 2
d["b"] = 6
d["g"] = 1
writedict("tmp.txt", d)
d2 = readdict("tmp.txt")
@test d2["a"] == 2
@test d2["b"] == 6
@test d2["g"] == 1
@test typeof(d2["g"]) == Int64
@test typeof(first(keys(d2))) == ASCIIString

# Float64,Any dict reversed
d = Dict{Float64,Any}()
d[1.0] = 8
d[100.0] = "6"
open(f->writedict(f, d), "tmp.txt", "w")
d2 = readdict("tmp.txt", reversed=true)
@test d2["8"] == 1.0
@test d2["6"] == 100.0
@test typeof(d2["8"]) == Float64
