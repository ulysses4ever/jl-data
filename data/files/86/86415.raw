status,len,point,buffer = Grisu.bignumdtoa(1.0, Grisu.SHORTEST, 0, buffer)
@test "1" == trimrep(buffer)
@test 1 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.bignumdtoa(1.0, Grisu.FIXED, 3, buffer)
@test 3 >= len - 1 - point
@test "1" == trimrep(buffer)
@test 1 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.bignumdtoa(1.0, Grisu.PRECISION, 3, buffer)
@test 3 >= len - 1
@test "1" == trimrep(buffer)
@test 1 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.bignumdtoa(1.5, Grisu.SHORTEST, 0, buffer)
@test "15" == trimrep(buffer)
@test 1 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.bignumdtoa(1.5, Grisu.FIXED, 10, buffer)
@test 10 >= len - 1 - point
@test "15" == trimrep(buffer)
@test 1 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.bignumdtoa(1.5, Grisu.PRECISION, 10, buffer)
@test 10 >= len - 1
@test "15" == trimrep(buffer)
@test 1 == point
fill!(buffer,0);

min_double = 5e-324
status,len,point,buffer = Grisu.bignumdtoa(min_double, Grisu.SHORTEST, 0, buffer)
@test "5" == trimrep(buffer)
@test -323 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.bignumdtoa(min_double, Grisu.FIXED, 5, buffer)
@test 5 >= len - 1 - point
@test "" == trimrep(buffer)

status,len,point,buffer = Grisu.bignumdtoa(min_double, Grisu.PRECISION, 5, buffer)
@test 5 >= len - 1
@test "49407" == trimrep(buffer)
@test -323 == point
fill!(buffer,0);

max_double = 1.7976931348623157e308
status,len,point,buffer = Grisu.bignumdtoa(max_double, Grisu.SHORTEST, 0, buffer)
@test "17976931348623157" == trimrep(buffer)
@test 309 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.bignumdtoa(max_double, Grisu.PRECISION, 7, buffer)
@test 7 >= len - 1
@test "1797693" == trimrep(buffer)
@test 309 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.bignumdtoa(4294967272.0, Grisu.SHORTEST, 0, buffer)
@test "4294967272" == bytestring(pointer(buffer))
@test 10 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.bignumdtoa(4294967272.0, Grisu.FIXED, 5, buffer)
@test "429496727200000" == bytestring(pointer(buffer))
@test 10 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.bignumdtoa(4294967272.0, Grisu.PRECISION, 14, buffer)
@test 14 >= len - 1
@test "4294967272" == trimrep(buffer)
@test 10 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.bignumdtoa(4.1855804968213567e298, Grisu.SHORTEST, 0,buffer)
@test "4185580496821357" == trimrep(buffer)
@test 299 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.bignumdtoa(4.1855804968213567e298, Grisu.PRECISION, 20,buffer)
@test 20 >= len - 1
@test "41855804968213567225" == trimrep(buffer)
@test 299 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.bignumdtoa(5.5626846462680035e-309, Grisu.SHORTEST, 0, buffer)
@test "5562684646268003" == trimrep(buffer)
@test -308 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.bignumdtoa(5.5626846462680035e-309, Grisu.PRECISION, 1, buffer)
@test 1 >= len - 1
@test "6" == trimrep(buffer)
@test -308 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.bignumdtoa(2147483648.0, Grisu.SHORTEST, 0, buffer)
@test "2147483648" == trimrep(buffer)
@test 10 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.bignumdtoa(2147483648.0, Grisu.FIXED, 2, buffer)
@test 2 >= len - 1 - point
@test "2147483648" == trimrep(buffer)
@test 10 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.bignumdtoa(2147483648.0, Grisu.PRECISION, 5, buffer)
@test 5 >= len - 1
@test "21475" == trimrep(buffer)
@test 10 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.bignumdtoa(3.5844466002796428e+298, Grisu.SHORTEST, 0, buffer)
@test "35844466002796428" == trimrep(buffer)
@test 299 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.bignumdtoa(3.5844466002796428e+298, Grisu.PRECISION, 10, buffer)
@test 10 >= len - 1
@test "35844466" == trimrep(buffer)
@test 299 == point
fill!(buffer,0);

v = reinterpret(Float64,0x0010000000000000)
status,len,point,buffer = Grisu.bignumdtoa(v, Grisu.SHORTEST, 0, buffer)
@test "22250738585072014" == trimrep(buffer)
@test -307 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.bignumdtoa(v, Grisu.PRECISION, 20, buffer)
@test 20 >= len - 1
@test "22250738585072013831" == trimrep(buffer)
@test -307 == point
fill!(buffer,0);

v = reinterpret(Float64,0x000FFFFFFFFFFFFF)
status,len,point,buffer = Grisu.bignumdtoa(v, Grisu.SHORTEST, 0, buffer)
@test "2225073858507201" == trimrep(buffer)
@test -307 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.bignumdtoa(v, Grisu.PRECISION, 20, buffer)
@test 20 >= len - 1
@test "2225073858507200889" == trimrep(buffer)
@test -307 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.bignumdtoa(4128420500802942e-24, Grisu.SHORTEST, 0, buffer)
@test "4128420500802942" == trimrep(buffer)
@test -8 == point
fill!(buffer,0);

v = 3.9292015898194142585311918e-10;
status,len,point,buffer = Grisu.bignumdtoa(v, Grisu.SHORTEST, 0, buffer)
@test "39292015898194143" == trimrep(buffer)

v = 4194304.0;
status,len,point,buffer = Grisu.bignumdtoa(v, Grisu.FIXED, 5, buffer)
@test 5 >= len - 1 - point
@test "4194304" == trimrep(buffer)

v = 3.3161339052167390562200598e-237;
status,len,point,buffer = Grisu.bignumdtoa(v, Grisu.PRECISION, 19, buffer)
@test 19 >= len - 1
@test "3316133905216739056" == trimrep(buffer)
@test -236 == point
fill!(buffer,0);

v = 7.9885183916008099497815232e+191;
status,len,point,buffer = Grisu.bignumdtoa(v, Grisu.PRECISION, 4, buffer)
@test 4 >= len - 1
@test "7989" == trimrep(buffer)
@test 192 == point
fill!(buffer,0);

v = 1.0000000000000012800000000e+17;
status,len,point,buffer = Grisu.bignumdtoa(v, Grisu.FIXED, 1, buffer)
@test 1 >= len - 1 - point
@test "100000000000000128" == trimrep(buffer)
@test 18 == point
fill!(buffer,0);


min_float = float32(1e-45)
status,len,point,buffer = Grisu.bignumdtoa(min_float, Grisu.SHORTEST, 0, buffer)
@test "1" == trimrep(buffer)
@test -44 == point
fill!(buffer,0);

max_float = float32(3.4028234e38)
status,len,point,buffer = Grisu.bignumdtoa(max_float, Grisu.SHORTEST, 0, buffer)
@test "34028235" == trimrep(buffer)
@test 39 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.bignumdtoa(float32(4294967272.0), Grisu.SHORTEST, 0, buffer)
@test "42949673" == trimrep(buffer)
@test 10 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.bignumdtoa(float32(3.32306998946228968226e+35), Grisu.SHORTEST, 0, buffer)
@test "332307" == trimrep(buffer)
@test 36 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.bignumdtoa(float32(1.2341e-41), Grisu.SHORTEST, 0, buffer)
@test "12341" == trimrep(buffer)
@test -40 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.bignumdtoa(float32(3.3554432e7), Grisu.SHORTEST, 0, buffer)
@test "33554432" == trimrep(buffer)
@test 8 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.bignumdtoa(float32(3.26494756798464e14), Grisu.SHORTEST, 0, buffer)
@test "32649476" == trimrep(buffer)
@test 15 == point
fill!(buffer,0);

status,len,point,buffer = Grisu.bignumdtoa(float32(3.91132223637771935344e37), Grisu.SHORTEST, 0, buffer)
@test "39113222" == trimrep(buffer)
@test 38 == point
fill!(buffer,0);

v = reinterpret(Float32,0x00800000)
status,len,point,buffer = Grisu.bignumdtoa(v, Grisu.SHORTEST, 0, buffer)
@test "11754944" == trimrep(buffer)
@test -37 == point
fill!(buffer,0);

v = reinterpret(Float32,0x007FFFFF)
status,len,point,buffer = Grisu.bignumdtoa(v, Grisu.SHORTEST, 0, buffer)
@test "11754942" == trimrep(buffer)
@test -37 == point
fill!(buffer,0);