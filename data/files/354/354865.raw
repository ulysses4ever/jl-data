using CodeToString
using Base.Test

try
    f(a, b) = a + b
    code_llvm_to_bytestring(f, (Int64, Int64))
    @code_llvm_to_bytestring f(1,2)
    @test typeof(code_llvm_to_bytestring(f, (Int64, Int64))) == Array{UInt8,1}
    @test typeof(@code_llvm_to_bytestring f(1,2)) == Array{UInt8,1}
    code_native_to_bytestring(f, (Int64, Int64))
    @code_native_to_bytestring f(1,2)
    @test typeof(code_native_to_bytestring(f, (Int64, Int64))) == Array{UInt8,1}
    @test typeof(@code_native_to_bytestring f(1,2)) == Array{UInt8,1}
    code_warntype_to_bytestring(f, (Int64, Int64))
    @code_warntype_to_bytestring f(1,2)
    @test typeof(code_warntype_to_bytestring(f, (Int64, Int64))) == Array{UInt8,1}
    @test typeof(@code_warntype_to_bytestring f(1,2)) == Array{UInt8,1}
catch
    @test false
end

@test true
