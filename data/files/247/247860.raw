using Base.Test
using Logging

include("../src/Fox.jl")


# write your own tests here
@test 1 == 1

println("Running tests...")


cd(joinpath(pwd(), "TestPkg.jl"))
println("Running fox in $(pwd())...")

Logging.configure(output=STDOUT, level=Logging.INFO)
Fox.run([])

