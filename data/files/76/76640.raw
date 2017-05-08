tests = [
    "test",
]

println("Testing Units.jl")
println("----------------")

for t in tests
    fp = joinpath("$(t).jl")
    print("* running $(fp) ")
    include(fp)
    println('\n')
end
