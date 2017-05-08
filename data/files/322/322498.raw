using CompilerOptions
using Base.Test

# write your own tests here
@test code_coverage() # cover your code!
@test !check_bounds()
@test !dump_bitcode()

if VERSION >= v"0.4"
    @test !compile_enabled()
end
