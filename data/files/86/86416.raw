function trimrep(buffer)
    ind = first(search(join(reverse(buffer)),r"[^0]"))
    return join(buffer[1:100-ind+1])
end

const bufsize = 100
buffer = Array(Char,bufsize);
fill!(buffer,'0');

min_double = 5e-324
status,len,point,buffer = Grisu.fastdtoa(min_double, Grisu.FAST_DTOA_SHORTEST, 0,buffer)
@test status
@test "5" == trimrep(buffer)
@test -323 == point
fill!(buffer,'0');

max_double = 1.7976931348623157e308
status,len,point,buffer = Grisu.fastdtoa(max_double, Grisu.FAST_DTOA_SHORTEST, 0,buffer)
@test status
@test "17976931348623157" == trimrep(buffer)
@test 309 == point
fill!(buffer,'0');

status,len,point,buffer = Grisu.fastdtoa(4294967272.0, Grisu.FAST_DTOA_SHORTEST, 0,buffer)
@test status
@test "4294967272" == trimrep(buffer)
@test 10 == point
fill!(buffer,'0');

status,len,point,buffer = Grisu.fastdtoa(4.1855804968213567e298, Grisu.FAST_DTOA_SHORTEST, 0,buffer)
@test status
@test "4185580496821357" == trimrep(buffer)
@test 299 == point
fill!(buffer,'0');

status,len,point,buffer = Grisu.fastdtoa(5.5626846462680035e-309, Grisu.FAST_DTOA_SHORTEST, 0,buffer)
@test status
@test "5562684646268003" == trimrep(buffer)
@test -308 == point
fill!(buffer,'0');

status,len,point,buffer = Grisu.fastdtoa(2147483648.0, Grisu.FAST_DTOA_SHORTEST, 0,buffer)
@test status
@test "2147483648" == trimrep(buffer)
@test 10 == point
fill!(buffer,'0');

status,len,point,buffer = Grisu.fastdtoa(3.5844466002796428e+298, Grisu.FAST_DTOA_SHORTEST, 0,buffer)
@test !status  # Not all Grisu.fastdtoa variants manage to compute this number.
if status
  @test "35844466002796428" == trimrep(buffer)
  @test 299 == point
  fill!(buffer,'0');
end

smallest_normal64 = 0x0010000000000000
v = reinterpret(Float64,smallest_normal64)
status,len,point,buffer = Grisu.fastdtoa(v, Grisu.FAST_DTOA_SHORTEST, 0, buffer)
if status
  @test "22250738585072014" == trimrep(buffer)
  @test -307 == point
  fill!(buffer,'0');
end

largest_denormal64 = 0x000FFFFFFFFFFFFF
v = reinterpret(Float64,largest_denormal64)
status,len,point,buffer = Grisu.fastdtoa(v, Grisu.FAST_DTOA_SHORTEST, 0, buffer)
if status
  @test "2225073858507201" == trimrep(buffer)
  @test -307 == point
  fill!(buffer,'0');
end


min_float = float32(1e-45)
status,len,point,buffer = Grisu.fastdtoa(min_float, Grisu.FAST_DTOA_SHORTEST_SINGLE, 0,buffer)
@test status
@test "1" == trimrep(buffer)
@test -44 == point
fill!(buffer,'0');

max_float = 3.4028234f38 #float32(3.4028234e38)
status,len,point,buffer = Grisu.fastdtoa(max_float, Grisu.FAST_DTOA_SHORTEST_SINGLE, 0,buffer)
@test status
@test "34028235" == trimrep(buffer)
@test 39 == point
fill!(buffer,'0');

status,len,point,buffer = Grisu.fastdtoa(float32(4294967272.0), Grisu.FAST_DTOA_SHORTEST_SINGLE, 0,buffer)
@test status
@test "42949673" == trimrep(buffer)
@test 10 == point
fill!(buffer,'0');

status,len,point,buffer = Grisu.fastdtoa(float32(3.32306998946228968226e+35), Grisu.FAST_DTOA_SHORTEST_SINGLE, 0,buffer)
@test status
@test "332307" == trimrep(buffer)
@test 36 == point
fill!(buffer,'0');

status,len,point,buffer = Grisu.fastdtoa(float32(1.2341e-41), Grisu.FAST_DTOA_SHORTEST_SINGLE, 0,buffer)
@test status
@test "12341" == trimrep(buffer)
@test -40 == point
fill!(buffer,'0');

status,len,point,buffer = Grisu.fastdtoa(float32(3.3554432e7), Grisu.FAST_DTOA_SHORTEST_SINGLE, 0,buffer)
@test status
@test "33554432" == trimrep(buffer)
@test 8 == point
fill!(buffer,'0');

status,len,point,buffer = Grisu.fastdtoa(float32(3.26494756798464e14), Grisu.FAST_DTOA_SHORTEST_SINGLE, 0,buffer)
@test status
@test "32649476" == trimrep(buffer)
@test 15 == point
fill!(buffer,'0');

status,len,point,buffer = Grisu.fastdtoa(float32(3.91132223637771935344e37), Grisu.FAST_DTOA_SHORTEST_SINGLE, 0,buffer)
if status  # Not all Grisu.fastdtoa variants manage to compute this number.
  @test "39113222" == trimrep(buffer)
  @test 38 == point
  fill!(buffer,'0');
end

smallest_normal32 = 0x00800000
v = reinterpret(Float32,smallest_normal32)
status,len,point,buffer = Grisu.fastdtoa(v, Grisu.FAST_DTOA_SHORTEST_SINGLE, 0, buffer)
if status
  @test "11754944" == trimrep(buffer)
  @test -37 == point
  fill!(buffer,'0');
end

largest_denormal32 = 0x007FFFFF
v = reinterpret(Float32,largest_denormal32)
status,len,point,buffer = Grisu.fastdtoa(v, Grisu.FAST_DTOA_SHORTEST_SINGLE, 0, buffer)
@test status
@test "11754942" == trimrep(buffer)
@test -37 == point
fill!(buffer,'0');


status,len,point,buffer = Grisu.fastdtoa(1.0, Grisu.FAST_DTOA_PRECISION, 3, buffer)
@test status
@test 3 >= len
@test "1" == trimrep(buffer)
@test 1 == point
fill!(buffer,'0');

status,len,point,buffer = Grisu.fastdtoa(1.5, Grisu.FAST_DTOA_PRECISION, 10, buffer)
if status
  @test 10 >= len
  @test "15" == trimrep(buffer)
  @test 1 == point
  fill!(buffer,'0');
end

min_double = 5e-324
status,len,point,buffer = Grisu.fastdtoa(min_double, Grisu.FAST_DTOA_PRECISION, 5,buffer)
@test status
@test "49407" == trimrep(buffer)
@test -323 == point
fill!(buffer,'0');

max_double = 1.7976931348623157e308
status,len,point,buffer = Grisu.fastdtoa(max_double, Grisu.FAST_DTOA_PRECISION, 7,buffer)
@test status
@test "1797693" == trimrep(buffer)
@test 309 == point
fill!(buffer,'0');

status,len,point,buffer = Grisu.fastdtoa(4294967272.0, Grisu.FAST_DTOA_PRECISION, 14,buffer)
if status
  @test 14 >= len
  @test "4294967272" == trimrep(buffer)
  @test 10 == point
  fill!(buffer,'0');
end

status,len,point,buffer = Grisu.fastdtoa(4.1855804968213567e298, Grisu.FAST_DTOA_PRECISION, 17,buffer)
@test status
@test "41855804968213567" == trimrep(buffer)
@test 299 == point
fill!(buffer,'0');

status,len,point,buffer = Grisu.fastdtoa(5.5626846462680035e-309, Grisu.FAST_DTOA_PRECISION, 1,buffer)
@test status
@test "6" == trimrep(buffer)
@test -308 == point
fill!(buffer,'0');

status,len,point,buffer = Grisu.fastdtoa(2147483648.0, Grisu.FAST_DTOA_PRECISION, 5,buffer)
@test status
@test "21475" == trimrep(buffer)
@test 10 == point
fill!(buffer,'0');

status,len,point,buffer = Grisu.fastdtoa(3.5844466002796428e+298, Grisu.FAST_DTOA_PRECISION, 10,buffer)
@test status
@test 10 >= len
@test "35844466" == trimrep(buffer)
@test 299 == point
fill!(buffer,'0');

smallest_normal64 = 0x0010000000000000
v = reinterpret(Float64,smallest_normal64)
status,len,point,buffer = Grisu.fastdtoa(v, Grisu.FAST_DTOA_PRECISION, 17, buffer)
@test status
@test "22250738585072014" == trimrep(buffer)
@test -307 == point
fill!(buffer,'0');

largest_denormal64 = 0x000FFFFFFFFFFFFF
v = reinterpret(Float64,largest_denormal64)
status,len,point,buffer = Grisu.fastdtoa(v, Grisu.FAST_DTOA_PRECISION, 17, buffer)
@test status
@test 20 >= len
@test "22250738585072009" == trimrep(buffer)
@test -307 == point
fill!(buffer,'0');

v = 3.3161339052167390562200598e-237
status,len,point,buffer = Grisu.fastdtoa(v, Grisu.FAST_DTOA_PRECISION, 18, buffer)
@test status
@test "331613390521673906" == trimrep(buffer)
@test -236 == point
fill!(buffer,'0');

v = 7.9885183916008099497815232e+191
status,len,point,buffer = Grisu.fastdtoa(v, Grisu.FAST_DTOA_PRECISION, 4, buffer)
@test status
@test "7989" == trimrep(buffer)
@test 192 == point
fill!(buffer,'0');

function test(tests,mode)
  const bufsize = 100
  buffer = Array(Char,bufsize);
  fill!(buffer,'0');
  iter = 1
  for t in tests
    r = mode == Grisu.FAST_DTOA_PRECISION ? t.number_digits : 0
    status,len,point,buffer = Grisu.fastdtoa(t.v,mode,r,buffer)
    if status
      @test status
      @test t.representation == trimrep(buffer)
      @test t.decimal_point == point
    end
    fill!(buffer,'0');
    iter += 1
  end
  return iter
end

if !isdefined(:ShortestTestNumbers)
  include("C:/Users/karbarcca/.julia/v0.3/Grisu/test/gay-shortest.jl")
end  
@time test(ShortestTestNumbers,Grisu.FAST_DTOA_SHORTEST)

if !isdefined(:ShortestSingleTestNumbers)
  include("C:/Users/karbarcca/.julia/v0.3/Grisu/test/gay-shortest-single.jl")
end
@time test(ShortestSingleTestNumbers,Grisu.FAST_DTOA_SHORTEST_SINGLE)

if !isdefined(:PrecisionTestNumbers)
  include("C:/Users/karbarcca/.julia/v0.3/Grisu/test/gay-precision.jl")
end
@time test(PrecisionTestNumbers,Grisu.FAST_DTOA_PRECISION)
