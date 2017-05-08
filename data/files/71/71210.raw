# TODO: This is a hack. Fix this.
include("../src/UnionFind.jl")
using UnionFind
using Base.Test

println("Running tests:")

tests = ["polymorphism",
         "table",
         "errors",
         "benchmark"]

for name in tests
    file = "$name.jl"
    println("  *  $file")
    include(file)
end
