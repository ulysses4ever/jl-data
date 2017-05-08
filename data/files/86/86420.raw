status,len,point,buffer = Grisu.fastfixedtoa(1.0, 0,1, buffer)
@test "1" == bytestring(pointer(buffer))
@test 1 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(1.0, 0,15, buffer)
@test "1" == bytestring(pointer(buffer))
@test 1 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(1.0, 0,0, buffer)
@test "1" == bytestring(pointer(buffer))
@test 1 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(0xFFFFFFFF, 0,5, buffer)
@test "4294967295" == bytestring(pointer(buffer))
@test 10 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(4294967296.0, 0,5, buffer)
@test "4294967296" == bytestring(pointer(buffer)) #todo
@test 10 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(1e21, 0,5, buffer)
@test "1" == bytestring(pointer(buffer)) #todo extra '0's
@test 22 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(999999999999999868928.00, 0,2, buffer)
@test "999999999999999868928" == bytestring(pointer(buffer)) #todo extra '0'
@test 21 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(6.9999999999999989514240000e+21, 0,5, buffer)
@test "6999999999999998951424" == bytestring(pointer(buffer)) #todo short several '9's
@test 22 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(1.5, 0,5, buffer)
@test "15" == bytestring(pointer(buffer))
@test 1 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(1.55, 0,5, buffer)
@test "155" == bytestring(pointer(buffer))
@test 1 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(1.55, 0,1, buffer)
@test "16" == bytestring(pointer(buffer))
@test 1 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(1.00000001, 0,15, buffer)
@test "100000001" == bytestring(pointer(buffer))
@test 1 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(0.1, 0,10, buffer)
@test "1" == bytestring(pointer(buffer))
@test 0 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(0.01, 0,10, buffer)
@test "1" == bytestring(pointer(buffer))
@test -1 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(0.001, 0,10, buffer)
@test "1" == bytestring(pointer(buffer))
@test -2 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(0.0001, 0,10, buffer) #todo
@test "1" == bytestring(pointer(buffer))
@test -3 == point
fill!(buffer,0);

v = 0.00001; fractional_count = 10
status,len,point,buffer = Grisu.fastfixedtoa(0.00001, 0,10, buffer) #todo
@test "1" == bytestring(pointer(buffer))
@test -4 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(0.000001, 0,10, buffer)
@test "1" == bytestring(pointer(buffer))
@test -5 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(0.0000001, 0,10, buffer)
@test "1" == bytestring(pointer(buffer))
@test -6 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(0.00000001, 0,10, buffer)
@test "1" == bytestring(pointer(buffer))
@test -7 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(0.000000001, 0,10, buffer)
@test "1" == bytestring(pointer(buffer))
@test -8 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(0.0000000001, 0,15, buffer)
@test "1" == bytestring(pointer(buffer))
@test -9 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(0.00000000001, 0,15, buffer)
@test "1" == bytestring(pointer(buffer))
@test -10 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(0.000000000001, 0,15, buffer)
@test "1" == bytestring(pointer(buffer))
@test -11 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(0.0000000000001, 0,15, buffer)
@test "1" == bytestring(pointer(buffer))
@test -12 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(0.00000000000001, 0,15, buffer)
@test "1" == bytestring(pointer(buffer))
@test -13 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(0.000000000000001, 0,20, buffer)
@test "1" == bytestring(pointer(buffer))
@test -14 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(0.0000000000000001, 0,20, buffer)
@test "1" == bytestring(pointer(buffer))
@test -15 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(0.00000000000000001, 0,20, buffer)
@test "1" == bytestring(pointer(buffer))
@test -16 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(0.000000000000000001, 0,20, buffer)
@test "1" == bytestring(pointer(buffer))
@test -17 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(0.0000000000000000001, 0,20, buffer)
@test "1" == bytestring(pointer(buffer))
@test -18 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(0.00000000000000000001, 0,20, buffer)
@test "1" == bytestring(pointer(buffer))
@test -19 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(0.10000000004, 0,10, buffer)
@test "1" == bytestring(pointer(buffer))
@test 0 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(0.01000000004, 0,10, buffer)
@test "1" == bytestring(pointer(buffer))
@test -1 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(0.00100000004, 0,10, buffer)
@test "1" == bytestring(pointer(buffer))
@test -2 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(0.00010000004, 0,10, buffer) #todo
@test "1" == bytestring(pointer(buffer))
@test -3 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(0.00001000004, 0,10, buffer)
@test "1" == bytestring(pointer(buffer))
@test -4 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(0.00000100004, 0,10, buffer)
@test "1" == bytestring(pointer(buffer))
@test -5 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(0.00000010004, 0,10, buffer)
@test "1" == bytestring(pointer(buffer))
@test -6 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(0.00000001004, 0,10, buffer)
@test "1" == bytestring(pointer(buffer))
@test -7 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(0.00000000104, 0,10, buffer)
@test "1" == bytestring(pointer(buffer))
@test -8 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(0.0000000001000004, 0,15, buffer)
@test "1" == bytestring(pointer(buffer))
@test -9 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(0.0000000000100004, 0,15, buffer)
@test "1" == bytestring(pointer(buffer))
@test -10 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(0.0000000000010004, 0,15, buffer)
@test "1" == bytestring(pointer(buffer))
@test -11 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(0.0000000000001004, 0,15, buffer)
@test "1" == bytestring(pointer(buffer))
@test -12 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(0.0000000000000104, 0,15, buffer)
@test "1" == bytestring(pointer(buffer))
@test -13 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(0.000000000000001000004, 0,20, buffer)
@test "1" == bytestring(pointer(buffer))
@test -14 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(0.000000000000000100004, 0,20, buffer)
@test "1" == bytestring(pointer(buffer))
@test -15 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(0.000000000000000010004, 0,20, buffer)
@test "1" == bytestring(pointer(buffer))
@test -16 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(0.000000000000000001004, 0,20, buffer)
@test "1" == bytestring(pointer(buffer))
@test -17 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(0.000000000000000000104, 0,20, buffer)
@test "1" == bytestring(pointer(buffer))
@test -18 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(0.000000000000000000014, 0,20, buffer)
@test "1" == bytestring(pointer(buffer))
@test -19 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(0.10000000006, 0,10, buffer)
@test "1000000001" == bytestring(pointer(buffer))
@test 0 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(0.01000000006, 0,10, buffer)
@test "100000001" == bytestring(pointer(buffer))
@test -1 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(0.00100000006, 0,10, buffer)
@test "10000001" == bytestring(pointer(buffer))
@test -2 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(0.00010000006, 0,10, buffer)
@test "1000001" == bytestring(pointer(buffer))
@test -3 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(0.00001000006, 0,10, buffer)
@test "100001" == bytestring(pointer(buffer))
@test -4 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(0.00000100006, 0,10, buffer)
@test "10001" == bytestring(pointer(buffer))
@test -5 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(0.00000010006, 0,10, buffer)
@test "1001" == bytestring(pointer(buffer))
@test -6 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(0.00000001006, 0,10, buffer)
@test "101" == bytestring(pointer(buffer))
@test -7 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(0.00000000106, 0,10, buffer)
@test "11" == bytestring(pointer(buffer))
@test -8 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(0.0000000001000006, 0,15, buffer)
@test "100001" == bytestring(pointer(buffer))
@test -9 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(0.0000000000100006, 0,15, buffer)
@test "10001" == bytestring(pointer(buffer))
@test -10 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(0.0000000000010006, 0,15, buffer)
@test "1001" == bytestring(pointer(buffer))
@test -11 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(0.0000000000001006, 0,15, buffer)
@test "101" == bytestring(pointer(buffer))
@test -12 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(0.0000000000000106, 0,15, buffer)
@test "11" == bytestring(pointer(buffer))
@test -13 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(0.000000000000001000006, 0,20, buffer)
@test "100001" == bytestring(pointer(buffer))
@test -14 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(0.000000000000000100006, 0,20, buffer)
@test "10001" == bytestring(pointer(buffer))
@test -15 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(0.000000000000000010006, 0,20, buffer)
@test "1001" == bytestring(pointer(buffer))
@test -16 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(0.000000000000000001006, 0,20, buffer)
@test "101" == bytestring(pointer(buffer))
@test -17 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(0.000000000000000000106, 0,20, buffer)
@test "11" == bytestring(pointer(buffer))
@test -18 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(0.000000000000000000016, 0,20, buffer)
@test "2" == bytestring(pointer(buffer))
@test -19 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(0.6, 0,0, buffer)
@test "1" == bytestring(pointer(buffer))
@test 1 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(0.96, 0,1, buffer)
@test "1" == bytestring(pointer(buffer))
@test 1 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(0.996, 0,2, buffer)
@test "1" == bytestring(pointer(buffer))
@test 1 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(0.9996, 0,3, buffer)
@test "1" == bytestring(pointer(buffer))
@test 1 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(0.99996, 0,4, buffer)
@test "1" == bytestring(pointer(buffer))
@test 1 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(0.999996, 0,5, buffer)
@test "1" == bytestring(pointer(buffer))
@test 1 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(0.9999996, 0,6, buffer)
@test "1" == bytestring(pointer(buffer))
@test 1 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(0.99999996, 0,7, buffer)
@test "1" == bytestring(pointer(buffer))
@test 1 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(0.999999996, 0,8, buffer)
@test "1" == bytestring(pointer(buffer))
@test 1 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(0.9999999996, 0,9, buffer)
@test "1" == bytestring(pointer(buffer))
@test 1 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(0.99999999996, 0,10, buffer)
@test "1" == bytestring(pointer(buffer))
@test 1 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(0.999999999996, 0,11, buffer)
@test "1" == bytestring(pointer(buffer))
@test 1 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(0.9999999999996, 0,12, buffer)
@test "1" == bytestring(pointer(buffer))
@test 1 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(0.99999999999996, 0,13, buffer)
@test "1" == bytestring(pointer(buffer))
@test 1 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(0.999999999999996, 0,14, buffer)
@test "1" == bytestring(pointer(buffer))
@test 1 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(0.9999999999999996, 0,15, buffer)
@test "1" == bytestring(pointer(buffer))
@test 1 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(0.00999999999999996, 0,16, buffer)
@test "1" == bytestring(pointer(buffer))
@test -1 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(0.000999999999999996, 0,17, buffer)
@test "1" == bytestring(pointer(buffer))
@test -2 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(0.0000999999999999996, 0,18, buffer)
@test "1" == bytestring(pointer(buffer))
@test -3 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(0.00000999999999999996, 0,19, buffer)
@test "1" == bytestring(pointer(buffer))
@test -4 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(0.000000999999999999996, 0,20, buffer)
@test "1" == bytestring(pointer(buffer))
@test -5 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(323423.234234, 0,10, buffer)
@test "323423234234" == bytestring(pointer(buffer))
@test 6 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(12345678.901234, 0,4, buffer)
@test "123456789012" == bytestring(pointer(buffer))
@test 8 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(98765.432109, 0,5, buffer)
@test "9876543211" == bytestring(pointer(buffer))
@test 5 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(42, 0,20, buffer)
@test "42" == bytestring(pointer(buffer))
@test 2 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(0.5, 0,0, buffer)
@test "1" == bytestring(pointer(buffer))
@test 1 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(1e-23, 0,10, buffer)
@test "" == bytestring(pointer(buffer))
@test -10 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(1e-123, 0,2, buffer)
@test "" == bytestring(pointer(buffer))
@test -2 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(1e-123, 0,0, buffer)
@test "" == bytestring(pointer(buffer))
@test 0 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(1e-23, 0,20, buffer)
@test "" == bytestring(pointer(buffer))
@test -20 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(1e-21, 0,20, buffer)
@test "" == bytestring(pointer(buffer))
@test -20 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(1e-22, 0,20, buffer)
@test "" == bytestring(pointer(buffer))
@test -20 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(6e-21, 0,20, buffer)
@test "1" == bytestring(pointer(buffer))
@test -19 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(9.1193616301674545152000000e+19, 0,0,buffer)
@test "91193616301674545152" == bytestring(pointer(buffer))
@test 20 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(4.8184662102767651659096515e-04, 0,19,buffer)
@test "4818466210276765" == bytestring(pointer(buffer))
@test -3 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(1.9023164229540652612705182e-23, 0,8,buffer)
@test "" == bytestring(pointer(buffer))
@test -8 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.fastfixedtoa(1000000000000000128.0, 0,0,buffer)
@test "1000000000000000128" == bytestring(pointer(buffer))
@test 19 == point
fill!(buffer,0);