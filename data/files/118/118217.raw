tests = ("constructors.jl",)

for test in tests
    try
        include(test)
    catch err
        println("Test $test failed.")
        throw(err)
    end
end
