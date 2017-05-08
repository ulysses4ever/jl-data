const bufsize = 500
buffer = zeros(Uint8,bufsize);
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(1.0, 1, buffer)
@test "1" == bytestring(pointer(buffer))
@test 1 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(1.0, 15, buffer)
@test "1" == bytestring(pointer(buffer))
@test 1 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(1.0, 0, buffer)
@test "1" == bytestring(pointer(buffer))
@test 1 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(0xFFFFFFFF, 5, buffer)
@test "4294967295" == bytestring(pointer(buffer))
@test 10 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(4294967296.0, 5, buffer)
@test "4294967296" == bytestring(pointer(buffer)) #todo
@test 10 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(1e21, 5, buffer)
@test "1" == bytestring(pointer(buffer)) #todo extra '0's
@test 22 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(999999999999999868928.00, 2, buffer)
@test "999999999999999868928" == bytestring(pointer(buffer)) #todo extra '0'
@test 21 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(6.9999999999999989514240000e+21, 5, buffer)
@test "6999999999999998951424" == bytestring(pointer(buffer)) #todo short several '9's
@test 22 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(1.5, 5, buffer)
@test "15" == bytestring(pointer(buffer))
@test 1 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(1.55, 5, buffer)
@test "155" == bytestring(pointer(buffer))
@test 1 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(1.55, 1, buffer)
@test "16" == bytestring(pointer(buffer))
@test 1 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(1.00000001, 15, buffer)
@test "100000001" == bytestring(pointer(buffer))
@test 1 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(0.1, 10, buffer)
@test "1" == bytestring(pointer(buffer))
@test 0 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(0.01, 10, buffer)
@test "1" == bytestring(pointer(buffer))
@test -1 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(0.001, 10, buffer)
@test "1" == bytestring(pointer(buffer))
@test -2 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(0.0001, 10, buffer) #todo
@test "1" == bytestring(pointer(buffer))
@test -3 == point
fill!(buffer,0);

v = 0.00001; fractional_count = 10
len,point,buffer = Grisu.fastfixedtoa(0.00001, 10, buffer) #todo
@test "1" == bytestring(pointer(buffer))
@test -4 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(0.000001, 10, buffer)
@test "1" == bytestring(pointer(buffer))
@test -5 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(0.0000001, 10, buffer)
@test "1" == bytestring(pointer(buffer))
@test -6 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(0.00000001, 10, buffer)
@test "1" == bytestring(pointer(buffer))
@test -7 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(0.000000001, 10, buffer)
@test "1" == bytestring(pointer(buffer))
@test -8 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(0.0000000001, 15, buffer)
@test "1" == bytestring(pointer(buffer))
@test -9 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(0.00000000001, 15, buffer)
@test "1" == bytestring(pointer(buffer))
@test -10 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(0.000000000001, 15, buffer)
@test "1" == bytestring(pointer(buffer))
@test -11 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(0.0000000000001, 15, buffer)
@test "1" == bytestring(pointer(buffer))
@test -12 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(0.00000000000001, 15, buffer)
@test "1" == bytestring(pointer(buffer))
@test -13 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(0.000000000000001, 20, buffer)
@test "1" == bytestring(pointer(buffer))
@test -14 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(0.0000000000000001, 20, buffer)
@test "1" == bytestring(pointer(buffer))
@test -15 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(0.00000000000000001, 20, buffer)
@test "1" == bytestring(pointer(buffer))
@test -16 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(0.000000000000000001, 20, buffer)
@test "1" == bytestring(pointer(buffer))
@test -17 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(0.0000000000000000001, 20, buffer)
@test "1" == bytestring(pointer(buffer))
@test -18 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(0.00000000000000000001, 20, buffer)
@test "1" == bytestring(pointer(buffer))
@test -19 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(0.10000000004, 10, buffer)
@test "1" == bytestring(pointer(buffer))
@test 0 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(0.01000000004, 10, buffer)
@test "1" == bytestring(pointer(buffer))
@test -1 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(0.00100000004, 10, buffer)
@test "1" == bytestring(pointer(buffer))
@test -2 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(0.00010000004, 10, buffer) #todo
@test "1" == bytestring(pointer(buffer))
@test -3 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(0.00001000004, 10, buffer)
@test "1" == bytestring(pointer(buffer))
@test -4 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(0.00000100004, 10, buffer)
@test "1" == bytestring(pointer(buffer))
@test -5 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(0.00000010004, 10, buffer)
@test "1" == bytestring(pointer(buffer))
@test -6 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(0.00000001004, 10, buffer)
@test "1" == bytestring(pointer(buffer))
@test -7 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(0.00000000104, 10, buffer)
@test "1" == bytestring(pointer(buffer))
@test -8 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(0.0000000001000004, 15, buffer)
@test "1" == bytestring(pointer(buffer))
@test -9 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(0.0000000000100004, 15, buffer)
@test "1" == bytestring(pointer(buffer))
@test -10 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(0.0000000000010004, 15, buffer)
@test "1" == bytestring(pointer(buffer))
@test -11 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(0.0000000000001004, 15, buffer)
@test "1" == bytestring(pointer(buffer))
@test -12 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(0.0000000000000104, 15, buffer)
@test "1" == bytestring(pointer(buffer))
@test -13 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(0.000000000000001000004, 20, buffer)
@test "1" == bytestring(pointer(buffer))
@test -14 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(0.000000000000000100004, 20, buffer)
@test "1" == bytestring(pointer(buffer))
@test -15 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(0.000000000000000010004, 20, buffer)
@test "1" == bytestring(pointer(buffer))
@test -16 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(0.000000000000000001004, 20, buffer)
@test "1" == bytestring(pointer(buffer))
@test -17 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(0.000000000000000000104, 20, buffer)
@test "1" == bytestring(pointer(buffer))
@test -18 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(0.000000000000000000014, 20, buffer)
@test "1" == bytestring(pointer(buffer))
@test -19 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(0.10000000006, 10, buffer)
@test "1000000001" == bytestring(pointer(buffer))
@test 0 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(0.01000000006, 10, buffer)
@test "100000001" == bytestring(pointer(buffer))
@test -1 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(0.00100000006, 10, buffer)
@test "10000001" == bytestring(pointer(buffer))
@test -2 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(0.00010000006, 10, buffer)
@test "1000001" == bytestring(pointer(buffer))
@test -3 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(0.00001000006, 10, buffer)
@test "100001" == bytestring(pointer(buffer))
@test -4 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(0.00000100006, 10, buffer)
@test "10001" == bytestring(pointer(buffer))
@test -5 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(0.00000010006, 10, buffer)
@test "1001" == bytestring(pointer(buffer))
@test -6 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(0.00000001006, 10, buffer)
@test "101" == bytestring(pointer(buffer))
@test -7 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(0.00000000106, 10, buffer)
@test "11" == bytestring(pointer(buffer))
@test -8 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(0.0000000001000006, 15, buffer)
@test "100001" == bytestring(pointer(buffer))
@test -9 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(0.0000000000100006, 15, buffer)
@test "10001" == bytestring(pointer(buffer))
@test -10 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(0.0000000000010006, 15, buffer)
@test "1001" == bytestring(pointer(buffer))
@test -11 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(0.0000000000001006, 15, buffer)
@test "101" == bytestring(pointer(buffer))
@test -12 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(0.0000000000000106, 15, buffer)
@test "11" == bytestring(pointer(buffer))
@test -13 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(0.000000000000001000006, 20, buffer)
@test "100001" == bytestring(pointer(buffer))
@test -14 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(0.000000000000000100006, 20, buffer)
@test "10001" == bytestring(pointer(buffer))
@test -15 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(0.000000000000000010006, 20, buffer)
@test "1001" == bytestring(pointer(buffer))
@test -16 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(0.000000000000000001006, 20, buffer)
@test "101" == bytestring(pointer(buffer))
@test -17 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(0.000000000000000000106, 20, buffer)
@test "11" == bytestring(pointer(buffer))
@test -18 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(0.000000000000000000016, 20, buffer)
@test "2" == bytestring(pointer(buffer))
@test -19 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(0.6, 0, buffer)
@test "1" == bytestring(pointer(buffer))
@test 1 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(0.96, 1, buffer)
@test "1" == bytestring(pointer(buffer))
@test 1 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(0.996, 2, buffer)
@test "1" == bytestring(pointer(buffer))
@test 1 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(0.9996, 3, buffer)
@test "1" == bytestring(pointer(buffer))
@test 1 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(0.99996, 4, buffer)
@test "1" == bytestring(pointer(buffer))
@test 1 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(0.999996, 5, buffer)
@test "1" == bytestring(pointer(buffer))
@test 1 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(0.9999996, 6, buffer)
@test "1" == bytestring(pointer(buffer))
@test 1 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(0.99999996, 7, buffer)
@test "1" == bytestring(pointer(buffer))
@test 1 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(0.999999996, 8, buffer)
@test "1" == bytestring(pointer(buffer))
@test 1 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(0.9999999996, 9, buffer)
@test "1" == bytestring(pointer(buffer))
@test 1 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(0.99999999996, 10, buffer)
@test "1" == bytestring(pointer(buffer))
@test 1 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(0.999999999996, 11, buffer)
@test "1" == bytestring(pointer(buffer))
@test 1 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(0.9999999999996, 12, buffer)
@test "1" == bytestring(pointer(buffer))
@test 1 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(0.99999999999996, 13, buffer)
@test "1" == bytestring(pointer(buffer))
@test 1 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(0.999999999999996, 14, buffer)
@test "1" == bytestring(pointer(buffer))
@test 1 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(0.9999999999999996, 15, buffer)
@test "1" == bytestring(pointer(buffer))
@test 1 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(0.00999999999999996, 16, buffer)
@test "1" == bytestring(pointer(buffer))
@test -1 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(0.000999999999999996, 17, buffer)
@test "1" == bytestring(pointer(buffer))
@test -2 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(0.0000999999999999996, 18, buffer)
@test "1" == bytestring(pointer(buffer))
@test -3 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(0.00000999999999999996, 19, buffer)
@test "1" == bytestring(pointer(buffer))
@test -4 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(0.000000999999999999996, 20, buffer)
@test "1" == bytestring(pointer(buffer))
@test -5 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(323423.234234, 10, buffer)
@test "323423234234" == bytestring(pointer(buffer))
@test 6 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(12345678.901234, 4, buffer)
@test "123456789012" == bytestring(pointer(buffer))
@test 8 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(98765.432109, 5, buffer)
@test "9876543211" == bytestring(pointer(buffer))
@test 5 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(42, 20, buffer)
@test "42" == bytestring(pointer(buffer))
@test 2 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(0.5, 0, buffer)
@test "1" == bytestring(pointer(buffer))
@test 1 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(1e-23, 10, buffer)
@test "" == bytestring(pointer(buffer))
@test -10 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(1e-123, 2, buffer)
@test "" == bytestring(pointer(buffer))
@test -2 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(1e-123, 0, buffer)
@test "" == bytestring(pointer(buffer))
@test 0 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(1e-23, 20, buffer)
@test "" == bytestring(pointer(buffer))
@test -20 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(1e-21, 20, buffer)
@test "" == bytestring(pointer(buffer))
@test -20 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(1e-22, 20, buffer)
@test "" == bytestring(pointer(buffer))
@test -20 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(6e-21, 20, buffer)
@test "1" == bytestring(pointer(buffer))
@test -19 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(9.1193616301674545152000000e+19, 0,
buffer)
@test "91193616301674545152" == bytestring(pointer(buffer))
@test 20 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(4.8184662102767651659096515e-04, 19,
buffer)
@test "4818466210276765" == bytestring(pointer(buffer))
@test -3 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(1.9023164229540652612705182e-23, 8,
buffer)
@test "" == bytestring(pointer(buffer))
@test -8 == point
fill!(buffer,0);

len,point,buffer = Grisu.fastfixedtoa(1000000000000000128.0, 0,
buffer)
@test "1000000000000000128" == bytestring(pointer(buffer))
@test 19 == point
fill!(buffer,0);

function testfixed(tests)
    const bufsize = 500
    buffer = zeros(Uint8,bufsize);
    fill!(buffer,0);
    iter = 1
    for t in tests
        n = t.number_digits
        len,point,buffer = Grisu.fastfixedtoa(t.v,n,buffer)
        @test t.representation == bytestring(pointer(buffer))
        @test t.decimal_point == point
        fill!(buffer,0);
        iter += 1
    end
    return iter
end

if !isdefined(:FixedTestNumbers)
  include("C:/Users/karbarcca/.julia/v0.3/Grisu/test/gay-fixed.jl")
end  
@time testfixed(FixedTestNumbers)
