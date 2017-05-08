#=
Bartłomiej Sadowski 
=#
print("max dla Float 64 z biblioteki: ")
println(realmax(Float64))
print("bity dla Float 64 z biblioteki: ")
println(bits(realmax(Float64)))
x=1.0
y=0.0
i=1.0

while i<54
	y=x+y
	x=1/2*x
	i=i+1
end
x=y

while !isinf(x)
	y=x
	x=x*2.0
end

println("wynik")
println(y)
println(bits(y))

##################################################################
print("max dla Float 32 z biblioteki: ")
println(realmax(Float32))
print("bity dla Float 32 z biblioteki: ")
println(bits(realmax(Float32)))

x32=1.0f0
y32=0.0f0
i32=1.0f0

while i32<25
	y32=x32+y32
	x32=1/2*x32
	i32=i32+1
end
x32=y32
println(float32(y32))
println(bits(float32(y32)))

while !isinf(float32(x32))
	y32=x32
	x32=x32*2.0
end

println("wynik")
println(float32(y32))
println(bits(float32(y32)))
###########################################################################
print("max dla Float 16 z biblioteki: ")
println(realmax(Float16))
print("bity dla Float 16 z biblioteki: ")
println(bits(realmax(Float16)))

x16=float16(1.0)
y16=float16(0.0)
i16=float16(1.0)

while i16<12
	y16=x16+y16
	x16=1/2*x16
	i16=i16+1
end
x16=y16
println(float16(y16))
println(bits(float16(y16)))

while !isinf(float16(x16))
	y16=x16
	x16=x16*2.0
end

println("wynik")
println(float16(y16))
println(bits(float16(y16)))





