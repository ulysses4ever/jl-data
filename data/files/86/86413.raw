function tr(buffer)
    buffer = bytestring(pointer(buffer))
    buffer == "" && return ""
    ind = first(search(reverse(buffer),r"[^0]"))
    return buffer[1:length(buffer)-ind+1]
end
const bufsize = 500
buffer = zeros(Uint8,bufsize);
fill!(buffer,0);

len,point,buffer = Grisu.bignumdtoa(1.0, Grisu.BIGNUM_DTOA_SHORTEST, 0, buffer)
@test "1" == tr(buffer)
@test 1 == point
fill!(buffer,0);

len,point,buffer = Grisu.bignumdtoa(1.0, Grisu.BIGNUM_DTOA_FIXED, 3, buffer)
@test 3 >= len - 1 - point
@test "1" == tr(buffer)
@test 1 == point
fill!(buffer,0);

len,point,buffer = Grisu.bignumdtoa(1.0, Grisu.BIGNUM_DTOA_PRECISION, 3, buffer)
@test 3 >= len - 1
@test "1" == tr(buffer)
@test 1 == point
fill!(buffer,0);

len,point,buffer = Grisu.bignumdtoa(1.5, Grisu.BIGNUM_DTOA_SHORTEST, 0, buffer)
@test "15" == tr(buffer)
@test 1 == point
fill!(buffer,0);

len,point,buffer = Grisu.bignumdtoa(1.5, Grisu.BIGNUM_DTOA_FIXED, 10, buffer)
@test 10 >= len - 1 - point
@test "15" == tr(buffer)
@test 1 == point
fill!(buffer,0);

len,point,buffer = Grisu.bignumdtoa(1.5, Grisu.BIGNUM_DTOA_PRECISION, 10, buffer)
@test 10 >= len - 1
@test "15" == tr(buffer)
@test 1 == point
fill!(buffer,0);

len,point,buffer = Grisu.bignumdtoa(min_double, Grisu.BIGNUM_DTOA_SHORTEST, 0, buffer)
@test "5" == tr(buffer)
@test -323 == point
fill!(buffer,0);

len,point,buffer = Grisu.bignumdtoa(min_double, Grisu.BIGNUM_DTOA_FIXED, 5, buffer)
@test 5 >= len - 1 - point
@test "" == tr(buffer)

min_double = 5e-324
len,point,buffer = Grisu.bignumdtoa(min_double, Grisu.BIGNUM_DTOA_PRECISION, 5, buffer)
@test 5 >= len - 1
@test "49407" == tr(buffer)
@test -323 == point
fill!(buffer,0);

max_double = 1.7976931348623157e308
len,point,buffer = Grisu.bignumdtoa(max_double, Grisu.BIGNUM_DTOA_SHORTEST, 0, buffer)
@test "17976931348623157" == tr(buffer)
@test 309 == point
fill!(buffer,0);

len,point,buffer = Grisu.bignumdtoa(max_double, Grisu.BIGNUM_DTOA_PRECISION, 7, buffer)
@test 7 >= len - 1
@test "1797693" == tr(buffer)
@test 309 == point
fill!(buffer,0);

len,point,buffer = Grisu.bignumdtoa(4294967272.0, Grisu.BIGNUM_DTOA_SHORTEST, 0, buffer)
@test "4294967272" == bytestring(pointer(buffer))
@test 10 == point
fill!(buffer,0);

len,point,buffer = Grisu.bignumdtoa(4294967272.0, Grisu.BIGNUM_DTOA_FIXED, 5, buffer)
@test "429496727200000" == bytestring(pointer(buffer))
@test 10 == point
fill!(buffer,0);

len,point,buffer = Grisu.bignumdtoa(4294967272.0, Grisu.BIGNUM_DTOA_PRECISION, 14, buffer)
@test 14 >= len - 1
@test "4294967272" == tr(buffer)
@test 10 == point
fill!(buffer,0);

len,point,buffer = Grisu.bignumdtoa(4.1855804968213567e298, Grisu.BIGNUM_DTOA_SHORTEST, 0,buffer)
@test "4185580496821357" == tr(buffer)
@test 299 == point
fill!(buffer,0);

len,point,buffer = Grisu.bignumdtoa(4.1855804968213567e298, Grisu.BIGNUM_DTOA_PRECISION, 20,buffer)
@test 20 >= len - 1
@test "41855804968213567225" == tr(buffer)
@test 299 == point
fill!(buffer,0);

len,point,buffer = Grisu.bignumdtoa(5.5626846462680035e-309, Grisu.BIGNUM_DTOA_SHORTEST, 0, buffer)
@test "5562684646268003" == tr(buffer)
@test -308 == point
fill!(buffer,0);

len,point,buffer = Grisu.bignumdtoa(5.5626846462680035e-309, Grisu.BIGNUM_DTOA_PRECISION, 1, buffer)
@test 1 >= len - 1
@test "6" == tr(buffer)
@test -308 == point
fill!(buffer,0);

len,point,buffer = Grisu.bignumdtoa(2147483648.0, Grisu.BIGNUM_DTOA_SHORTEST, 0, buffer)
@test "2147483648" == tr(buffer)
@test 10 == point
fill!(buffer,0);

len,point,buffer = Grisu.bignumdtoa(2147483648.0, Grisu.BIGNUM_DTOA_FIXED, 2, buffer)
@test 2 >= len - 1 - point
@test "2147483648" == tr(buffer)
@test 10 == point
fill!(buffer,0);

len,point,buffer = Grisu.bignumdtoa(2147483648.0, Grisu.BIGNUM_DTOA_PRECISION, 5, buffer)
@test 5 >= len - 1
@test "21475" == tr(buffer)
@test 10 == point
fill!(buffer,0);

len,point,buffer = Grisu.bignumdtoa(3.5844466002796428e+298, Grisu.BIGNUM_DTOA_SHORTEST, 0, buffer)
@test "35844466002796428" == tr(buffer)
@test 299 == point
fill!(buffer,0);

len,point,buffer = Grisu.bignumdtoa(3.5844466002796428e+298, Grisu.BIGNUM_DTOA_PRECISION, 10, buffer)
@test 10 >= len - 1
@test "35844466" == tr(buffer)
@test 299 == point
fill!(buffer,0);

v = reinterpret(Float64,0x0010000000000000)
len,point,buffer = Grisu.bignumdtoa(v, Grisu.BIGNUM_DTOA_SHORTEST, 0, buffer)
@test "22250738585072014" == tr(buffer)
@test -307 == point
fill!(buffer,0);

len,point,buffer = Grisu.bignumdtoa(v, Grisu.BIGNUM_DTOA_PRECISION, 20, buffer)
@test 20 >= len - 1
@test "22250738585072013831" == tr(buffer)
@test -307 == point
fill!(buffer,0);

v = reinterpret(Float64,0x000FFFFFFFFFFFFF)
len,point,buffer = Grisu.bignumdtoa(v, Grisu.BIGNUM_DTOA_SHORTEST, 0, buffer)
@test "2225073858507201" == tr(buffer)
@test -307 == point
fill!(buffer,0);

len,point,buffer = Grisu.bignumdtoa(v, Grisu.BIGNUM_DTOA_PRECISION, 20, buffer)
@test 20 >= len - 1
@test "2225073858507200889" == tr(buffer)
@test -307 == point
fill!(buffer,0);

len,point,buffer = Grisu.bignumdtoa(4128420500802942e-24, Grisu.BIGNUM_DTOA_SHORTEST, 0, buffer)
@test "4128420500802942" == tr(buffer)
@test -8 == point
fill!(buffer,0);

v = 3.9292015898194142585311918e-10;
len,point,buffer = Grisu.bignumdtoa(v, Grisu.BIGNUM_DTOA_SHORTEST, 0, buffer)
@test "39292015898194143" == tr(buffer)

v = 4194304.0;
len,point,buffer = Grisu.bignumdtoa(v, Grisu.BIGNUM_DTOA_FIXED, 5, buffer)
@test 5 >= len - 1 - point
@test "4194304" == tr(buffer)

v = 3.3161339052167390562200598e-237;
len,point,buffer = Grisu.bignumdtoa(v, Grisu.BIGNUM_DTOA_PRECISION, 19, buffer)
@test 19 >= len - 1
@test "3316133905216739056" == tr(buffer)
@test -236 == point
fill!(buffer,0);

v = 7.9885183916008099497815232e+191;
len,point,buffer = Grisu.bignumdtoa(v, Grisu.BIGNUM_DTOA_PRECISION, 4, buffer)
@test 4 >= len - 1
@test "7989" == tr(buffer)
@test 192 == point
fill!(buffer,0);

v = 1.0000000000000012800000000e+17;
len,point,buffer = Grisu.bignumdtoa(v, Grisu.BIGNUM_DTOA_FIXED, 1, buffer)
@test 1 >= len - 1 - point
@test "100000000000000128" == tr(buffer)
@test 18 == point
fill!(buffer,0);


min_float = float32(1e-45)
len,point,buffer = Grisu.bignumdtoa(min_float, Grisu.BIGNUM_DTOA_SHORTEST_SINGLE, 0, buffer)
@test "1" == tr(buffer)
@test -44 == point
fill!(buffer,0);

max_float = float32(3.4028234e38)
len,point,buffer = Grisu.bignumdtoa(max_float, Grisu.BIGNUM_DTOA_SHORTEST_SINGLE, 0, buffer)
@test "34028235" == tr(buffer)
@test 39 == point
fill!(buffer,0);

len,point,buffer = Grisu.bignumdtoa(float32(4294967272.0), Grisu.BIGNUM_DTOA_SHORTEST_SINGLE, 0, buffer)
@test "42949673" == tr(buffer)
@test 10 == point
fill!(buffer,0);

len,point,buffer = Grisu.bignumdtoa(float32(3.32306998946228968226e+35), Grisu.BIGNUM_DTOA_SHORTEST_SINGLE, 0, buffer)
@test "332307" == tr(buffer)
@test 36 == point
fill!(buffer,0);

len,point,buffer = Grisu.bignumdtoa(float32(1.2341e-41), Grisu.BIGNUM_DTOA_SHORTEST_SINGLE, 0, buffer)
@test "12341" == tr(buffer)
@test -40 == point
fill!(buffer,0);

len,point,buffer = Grisu.bignumdtoa(float32(3.3554432e7), Grisu.BIGNUM_DTOA_SHORTEST_SINGLE, 0, buffer)
@test "33554432" == tr(buffer)
@test 8 == point
fill!(buffer,0);

len,point,buffer = Grisu.bignumdtoa(float32(3.26494756798464e14), Grisu.BIGNUM_DTOA_SHORTEST_SINGLE, 0, buffer)
@test "32649476" == tr(buffer)
@test 15 == point
fill!(buffer,0);

len,point,buffer = Grisu.bignumdtoa(float32(3.91132223637771935344e37), Grisu.BIGNUM_DTOA_SHORTEST_SINGLE, 0, buffer)
@test "39113222" == tr(buffer)
@test 38 == point
fill!(buffer,0);

v = reinterpret(Float32,0x00800000)
len,point,buffer = Grisu.bignumdtoa(v, Grisu.BIGNUM_DTOA_SHORTEST_SINGLE, 0, buffer)
@test "11754944" == tr(buffer)
@test -37 == point
fill!(buffer,0);

v = reinterpret(Float32,0x007FFFFF)
len,point,buffer = Grisu.bignumdtoa(v, Grisu.BIGNUM_DTOA_SHORTEST_SINGLE, 0, buffer)
@test "11754942" == tr(buffer)
@test -37 == point
fill!(buffer,0);

function test(tests)
  const bufsize = 500
  buffer = Array(Uint8,bufsize);
  fill!(buffer,0);
  iter = 1
  for t in tests
    test(t,buffer)
    fill!(buffer,0);
    iter += 1
  end
  return iter
end

if !isdefined(:ShortestTestNumbers)
  include("C:/Users/karbarcca/.julia/v0.3/Grisu/test/gay-shortest.jl")
end
if !isdefined(:ShortestSingleTestNumbers)
  include("C:/Users/karbarcca/.julia/v0.3/Grisu/test/gay-shortest-single.jl")
end
if !isdefined(:PrecisionTestNumbers)
  include("C:/Users/karbarcca/.julia/v0.3/Grisu/test/gay-precision.jl")
end
if !isdefined(:FixedTestNumbers)
  include("C:/Users/karbarcca/.julia/v0.3/Grisu/test/gay-fixed.jl")
end  

function test(t::PrecomputedFixed,buffer)
    n = t.number_digits
    len,point,buffer = Grisu.bignumdtoa(t.v,Grisu.BIGNUM_DTOA_FIXED,n,buffer)
    @test n >= len - point - 1
    @test t.representation == tr(buffer)
    @test t.decimal_point == point
end
function test(t::PP,buffer)
    n = t.number_digits
    len,point,buffer = Grisu.bignumdtoa(t.v,Grisu.BIGNUM_DTOA_PRECISION,n,buffer)
    @test t.number_digits >= len-1
    @test t.representation == tr(buffer)
    @test t.decimal_point == point
end
function test(t::PrecomputedShortest,buffer)
    len,point,buffer = Grisu.bignumdtoa(t.v,Grisu.BIGNUM_DTOA_SHORTEST,0,buffer)
    @test t.representation == bytestring(pointer(buffer))
    @test t.decimal_point == point 
end
function test(t::PrecomputedShortestSingle,buffer)
    len,point,buffer = Grisu.bignumdtoa(t.v,Grisu.BIGNUM_DTOA_SHORTEST_SINGLE,0,buffer)
    @test t.representation == bytestring(pointer(buffer))
    @test t.decimal_point == point 
end

@time test(ShortestTestNumbers)
@time test(ShortestSingleTestNumbers)
@time test(PrecisionTestNumbers)
@time test(FixedTestNumbers)