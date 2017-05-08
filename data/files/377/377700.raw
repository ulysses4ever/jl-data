#!/usr/bin/julia
import myModule

using myModule

println("Algebra and Types")
println("-------------------------")

# 3 angle identity for cos
f3(x) = -3x + 4x^3
f(x) = f3(cos(x/3))


radians = 2.5

println(cos(radians)," vs ", f(radians))

#some conversions from a Rational
a = 2//6
println("Rational Value:",a," num:",num(a)," den:",den(a))
println("Float64  Value:",convert(Float64,a)," Result:",f3(convert(Float64,a)))
println("Float32  Value:",convert(Float32,a)," Result:",f3(convert(Float32,a)))
println("BigFloat Value:",convert(BigFloat,a)," Result:",f3(convert(BigFloat,a)))
println("FixedPoint Value:",convert(FixedPoint,a)," Result:",f3(convert(FixedPoint,a)))
println()

println("subtypes(Real)")
println(subtypes(Real))

println("super(BigFloat)")
println(super(BigFloat))


quit()

tp = FixedPoint 
#Int16
#Rational
#BigFloat
#Float64
#Int32
#FixedPoint


println("code_lowered")
println(code_lowered(f3,(tp,)))

println("code_typed")
println(code_typed(f3,(tp,)))

println("code_llvm")
println(code_llvm(f3,(tp,)))

println("code_native")
println(code_native(f3,(tp,)))


