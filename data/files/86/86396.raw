len,point,neg,buffer = Grisu.grisu(0.0, Grisu.SHORTEST, 0, buffer)
@test "0" == bytestring(pointer(buffer))
@test 1 == point
fill!(buffer,0);

len,point,neg,buffer = Grisu.grisu(float32(0.0), Grisu.SHORTEST, 0, buffer)
@test "0" == bytestring(pointer(buffer))
@test 1 == point
fill!(buffer,0);

len,point,neg,buffer = Grisu.grisu(0.0, Grisu.FIXED, 2, buffer)
@test 1 >= len-1
@test "0" == bytestring(pointer(buffer))
@test 1 == point
fill!(buffer,0);

len,point,neg,buffer = Grisu.grisu(0.0, Grisu.PRECISION, 3, buffer)
@test 1 >= len-1
@test "0" == bytestring(pointer(buffer))
@test 1 == point
fill!(buffer,0);

len,point,neg,buffer = Grisu.grisu(1.0, Grisu.SHORTEST, 0, buffer)
@test "1" == bytestring(pointer(buffer))
@test 1 == point
fill!(buffer,0);

len,point,neg,buffer = Grisu.grisu(float32(1.0), Grisu.SHORTEST, 0, buffer)
@test "1" == bytestring(pointer(buffer))
@test 1 == point
fill!(buffer,0);

len,point,neg,buffer = Grisu.grisu(1.0, Grisu.FIXED, 3, buffer)
@test 3 >= len-1-point
@test "1" == trimrep(buffer)
@test 1 == point
fill!(buffer,0);

len,point,neg,buffer = Grisu.grisu(1.0, Grisu.PRECISION, 3, buffer)
@test 3 >= len-1
@test "1" == trimrep(buffer)
@test 1 == point
fill!(buffer,0);

len,point,neg,buffer = Grisu.grisu(1.5, Grisu.SHORTEST, 0, buffer)
@test "15" == bytestring(pointer(buffer))
@test 1 == point
fill!(buffer,0);

len,point,neg,buffer = Grisu.grisu(float32(1.5), Grisu.SHORTEST, 0, buffer)
@test "15" == bytestring(pointer(buffer))
@test 1 == point
fill!(buffer,0);

len,point,neg,buffer = Grisu.grisu(1.5, Grisu.FIXED, 10, buffer)
@test 10 >= len-1-point
@test "15" == trimrep(buffer)
@test 1 == point
fill!(buffer,0);

len,point,neg,buffer = Grisu.grisu(1.5, Grisu.PRECISION, 10, buffer)
@test 10 >= len-1
@test "15" == trimrep(buffer)
@test 1 == point
fill!(buffer,0);

min_double = 5e-324
len,point,neg,buffer = Grisu.grisu(min_double, Grisu.SHORTEST, 0, buffer)
@test "5" == bytestring(pointer(buffer))
@test -323 == point
fill!(buffer,0);

min_float = 1e-45
len,point,neg,buffer = Grisu.grisu(float32(min_float), Grisu.SHORTEST, 0, buffer)
@test "1" == bytestring(pointer(buffer))
@test -44 == point
fill!(buffer,0);

len,point,neg,buffer = Grisu.grisu(min_double, Grisu.FIXED, 5, buffer)
@test 5 >= len-1-point
@test "" == trimrep(buffer)
@test -5 == point
fill!(buffer,0);

len,point,neg,buffer = Grisu.grisu(min_double, Grisu.PRECISION, 5, buffer)
@test 5 >= len-1
@test "49407" == trimrep(buffer)
@test -323 == point
fill!(buffer,0);

max_double = 1.7976931348623157e308
len,point,neg,buffer = Grisu.grisu(max_double, Grisu.SHORTEST, 0, buffer)
@test "17976931348623157" == bytestring(pointer(buffer))
@test 309 == point
fill!(buffer,0);

max_float = 3.4028234e38
len,point,neg,buffer = Grisu.grisu(float32(max_float), Grisu.SHORTEST, 0,buffer)
@test "34028235" == bytestring(pointer(buffer))
@test 39 == point
fill!(buffer,0);

len,point,neg,buffer = Grisu.grisu(max_double, Grisu.PRECISION, 7, buffer)
@test 7 >= len-1
@test "1797693" == trimrep(buffer)
@test 309 == point
fill!(buffer,0);

len,point,neg,buffer = Grisu.grisu(4294967272.0, Grisu.SHORTEST, 0, buffer)
@test "4294967272" == bytestring(pointer(buffer))
@test 10 == point
fill!(buffer,0);

len,point,neg,buffer = Grisu.grisu(float32(4294967272.0), Grisu.SHORTEST, 0, buffer)
@test "42949673" == bytestring(pointer(buffer))
@test 10 == point
fill!(buffer,0);

len,point,neg,buffer = Grisu.grisu(4294967272.0, Grisu.FIXED, 5, buffer)
@test 5 >= len-1-point
@test "4294967272" == trimrep(buffer)
@test 10 == point
fill!(buffer,0);

len,point,neg,buffer = Grisu.grisu(4294967272.0, Grisu.PRECISION, 14,buffer)
@test 14 >= len-1
@test "4294967272" == trimrep(buffer)
@test 10 == point
fill!(buffer,0);

len,point,neg,buffer = Grisu.grisu(4.1855804968213567e298, Grisu.SHORTEST, 0,buffer)
@test "4185580496821357" == bytestring(pointer(buffer))
@test 299 == point
fill!(buffer,0);

len,point,neg,buffer = Grisu.grisu(4.1855804968213567e298, Grisu.PRECISION, 20,buffer)
@test 20 >= len-1
@test "41855804968213567225" == trimrep(buffer)
@test 299 == point
fill!(buffer,0);

len,point,neg,buffer = Grisu.grisu(5.5626846462680035e-309, Grisu.SHORTEST, 0,buffer)
@test "5562684646268003" == bytestring(pointer(buffer))
@test -308 == point
fill!(buffer,0);

len,point,neg,buffer = Grisu.grisu(5.5626846462680035e-309, Grisu.PRECISION, 1,buffer)
@test 1 >= len-1
@test "6" == trimrep(buffer)
@test -308 == point
fill!(buffer,0);

len,point,neg,buffer = Grisu.grisu(-2147483648.0, Grisu.SHORTEST, 0,buffer)
@test 1 == neg
@test "2147483648" == bytestring(pointer(buffer))
@test 10 == point
fill!(buffer,0);

len,point,neg,buffer = Grisu.grisu(float32(-2147483648.), Grisu.SHORTEST, 0,buffer)
@test 1 == neg
@test "21474836" == bytestring(pointer(buffer))
@test 10 == point
fill!(buffer,0);


len,point,neg,buffer = Grisu.grisu(-2147483648.0, Grisu.FIXED, 2, buffer)
@test 2 >= len-1-point
@test "2147483648" == trimrep(buffer)
@test 10 == point
fill!(buffer,0);

len,point,neg,buffer = Grisu.grisu(-2147483648.0, Grisu.PRECISION, 5,buffer)
@test 5 >= len-1
@test "21475" == trimrep(buffer)
@test 10 == point
fill!(buffer,0);

len,point,neg,buffer = Grisu.grisu(-3.5844466002796428e+298, Grisu.SHORTEST, 0,buffer)
@test 1 == neg
@test "35844466002796428" == bytestring(pointer(buffer))
@test 299 == point
fill!(buffer,0);

len,point,neg,buffer = Grisu.grisu(-3.5844466002796428e+298, Grisu.PRECISION, 10,buffer)
@test 1 == neg
@test 10 >= len-1
@test "35844466" == trimrep(buffer)
@test 299 == point
fill!(buffer,0);

v = reinterpret(Float64,0x0010000000000000)
len,point,neg,buffer = Grisu.grisu(v, Grisu.SHORTEST, 0, buffer)
@test "22250738585072014" == bytestring(pointer(buffer))
@test -307 == point
fill!(buffer,0);

f = reinterpret(Float32,0x00800000)
len,point,neg,buffer = Grisu.grisu(f, Grisu.SHORTEST, 0, buffer)
@test "11754944" == bytestring(pointer(buffer))
@test -37 == point
fill!(buffer,0);

len,point,neg,buffer = Grisu.grisu(v, Grisu.PRECISION, 20, buffer)
@test 20 >= len-1
@test "22250738585072013831" == trimrep(buffer)
@test -307 == point
fill!(buffer,0);

v = reinterpret(Float64,0x000FFFFFFFFFFFFF)
len,point,neg,buffer = Grisu.grisu(v, Grisu.SHORTEST, 0, buffer)
@test "2225073858507201" == bytestring(pointer(buffer))
@test -307 == point
fill!(buffer,0);

f = reinterpret(Float32,0x007FFFFF)
len,point,neg,buffer = Grisu.grisu(f, Grisu.SHORTEST, 0, buffer)
@test "11754942" == bytestring(pointer(buffer))
@test -37 == point
fill!(buffer,0);

len,point,neg,buffer = Grisu.grisu(v, Grisu.PRECISION, 20, buffer)
@test 20 >= len-1
@test "2225073858507200889" == trimrep(buffer)
@test -307 == point
fill!(buffer,0);

len,point,neg,buffer = Grisu.grisu(4128420500802942e-24, Grisu.SHORTEST, 0,buffer)
@test 0 == neg
@test "4128420500802942" == bytestring(pointer(buffer))
@test -8 == point
fill!(buffer,0);

v = -3.9292015898194142585311918e-10
len,point,neg,buffer = Grisu.grisu(v, Grisu.SHORTEST, 0, buffer)
@test "39292015898194143" == bytestring(pointer(buffer))
fill!(buffer,0);

f = float32(-3.9292015898194142585311918e-10)
len,point,neg,buffer = Grisu.grisu(f, Grisu.SHORTEST, 0, buffer)
@test "39292017" == bytestring(pointer(buffer))
fill!(buffer,0);

v = 4194304.0
len,point,neg,buffer = Grisu.grisu(v, Grisu.FIXED, 5, buffer)
@test 5 >= len-1-point
@test "4194304" == trimrep(buffer)
fill!(buffer,0);

v = 3.3161339052167390562200598e-237
len,point,neg,buffer = Grisu.grisu(v, Grisu.PRECISION, 19, buffer)
@test 19 >= len-1
@test "3316133905216739056" == trimrep(buffer)
@test -236 == point
fill!(buffer,0);

len,point,neg,buffer = Grisu.grisu(0.0, Grisu.SHORTEST, 0, buffer)
@test !neg

len,point,neg,buffer = Grisu.grisu(-0.0, Grisu.SHORTEST, 0, buffer)
@test neg

len,point,neg,buffer = Grisu.grisu(1.0, Grisu.SHORTEST, 0, buffer)
@test !neg

len,point,neg,buffer = Grisu.grisu(-1.0, Grisu.SHORTEST, 0, buffer)
@test neg

len,point,neg,buffer = Grisu.grisu(float32(0.0), Grisu.SHORTEST, 0, buffer)
@test !neg

len,point,neg,buffer = Grisu.grisu(-float32(0.0), Grisu.SHORTEST, 0, buffer)
@test neg

len,point,neg,buffer = Grisu.grisu(float32(1.0), Grisu.SHORTEST, 0, buffer)
@test !neg

len,point,neg,buffer = Grisu.grisu(-float32(1.0), Grisu.SHORTEST, 0, buffer)
@test neg

len,point,neg,buffer = Grisu.grisu(0.0, Grisu.PRECISION, 1, buffer)
@test !neg

len,point,neg,buffer = Grisu.grisu(-0.0, Grisu.PRECISION, 1, buffer)
@test neg

len,point,neg,buffer = Grisu.grisu(1.0, Grisu.PRECISION, 1, buffer)
@test !neg

len,point,neg,buffer = Grisu.grisu(-1.0, Grisu.PRECISION, 1, buffer)
@test neg

len,point,neg,buffer = Grisu.grisu(0.0, Grisu.FIXED, 1, buffer)
@test !neg

len,point,neg,buffer = Grisu.grisu(-0.0, Grisu.FIXED, 1, buffer)
@test neg

len,point,neg,buffer = Grisu.grisu(1.0, Grisu.FIXED, 1, buffer)
@test !neg

len,point,neg,buffer = Grisu.grisu(-1.0, Grisu.FIXED, 1, buffer)
@test neg


len,point,neg,buffer = Grisu.grisu(0.0, Grisu.PRECISION, 0, buffer)
@test 0 >= len-1
@test "" == bytestring(pointer(buffer))
@test !neg

len,point,neg,buffer = Grisu.grisu(1.0, Grisu.PRECISION, 0, buffer)
@test 0 >= len-1
@test "" == bytestring(pointer(buffer))
@test !neg

len,point,neg,buffer = Grisu.grisu(0.0, Grisu.FIXED, 0, buffer)
@test 1 >= len-1
@test "0" == bytestring(pointer(buffer))
@test !neg

len,point,neg,buffer = Grisu.grisu(1.0, Grisu.FIXED, 0, buffer)
@test 1 >= len-1
@test "1" == bytestring(pointer(buffer))
@test !neg
