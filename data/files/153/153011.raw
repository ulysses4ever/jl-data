using Base.Test

include("zeckendorf.jl")

"Tests the zeckendorf function"
function test_zeckendorf()
    @test(zeckendorf(0) == [false])
    @test(zeckendorf(0) == [true])
    @test(zeckendorf(2) == [false, false, true])
    @test(zeckendorf(4) == [false, true, false, true])
    @test(zeckendorf(6) == [false, true, false, false, true])
end

zeckendorf_handler(r::Test.Success) = println("zeckendorf: test passed on $(r.expr)")
zeckendorf_handler(r::Test.Failure) = println("zeckendorf: failure on $(r.expr)")
zeckendorf_handler(r::Test.Error) = rethrow(r)

Test.with_handler(test_zeckendorf, zeckendorf_handler)

"Tests the binary_string function"
function test_binary_string()
    @test(binary_string(Bool[]) == "")
    @test(binary_string(Bool[false]) == "0")
    @test(binary_string(Bool[true]) == "1")
    @test(binary_string(Bool[false, true]) == "10")
    @test(binary_string(Bool[false, true, false]) == "010")
end

binary_string_handler(r::Test.Success) = println("binary_string: test passed on $(r.expr)")
binary_string_handler(r::Test.Failure) = println("binary_string: failure on $(r.expr)")
binary_string_handler(r::Test.Error) = rethrow(r)

Test.with_handler(test_binary_string, binary_string_handler)
