using Distributions
using ForwardDiff
using Base.Test

tests = [
    "normal",
    "mvnormal",
    "mvnormalcanon",
    "mvtdist",
    "wishart",
    "inversewishart"
    ]

print_with_color(:blue, "Running tests:\n")

srand(12345)

include("utils.jl")

for t in tests
    test_fn = "$t.jl"
    print_with_color(:green, "* $test_fn\n")
    include(test_fn)
end
