include("../src/Iteration.jl")
include("testing.jl")

importall Iteration

print("testing iteration ")

@assert_equal({[1, 2], [3, 4]}, [e for e = slicerator([1, 2, 3, 4], 2)])
@assert_equal({[1, 2], [3, 4], [5, 6]}, [e for e = slicerator([1, 2, 3, 4, 5, 6], 2)])
@assert_equal({[1, 2, 3], [4, 5, 6]}, [e for e = slicerator([1, 2, 3, 4, 5, 6], 3)])

@assert_equal({[3, 4], [5, 6]}, [e for e = offset(1, slicerator([1, 2, 3, 4, 5, 6], 2))])
@assert_equal({[5, 6]}, [e for e = offset(2, slicerator([1, 2, 3, 4, 5, 6], 2))])
@assert_equal({}, [e for e = offset(3, slicerator([1, 2, 3, 4, 5, 6], 2))])
@assert_equal({}, [e for e = offset(4, slicerator([1, 2, 3, 4, 5, 6], 2))])

println()
println()