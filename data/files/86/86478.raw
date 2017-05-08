using Base.Test
#using Grisu
cd("C:\\Users\\karbarcca\\.julia\\v0.3\\Grisu\\test")
include("C:/Users/karbarcca/.julia/v0.3/Grisu/src/Grisu.jl")

function trimrep(buffer)
  len = length(bytestring(pointer(buffer)))
  ind = len
  for i = len:-1:1
    buffer[i] != 0x30 && break
    ind -= 1
  end
  buffer[ind+1] = 0
  return bytestring(pointer(buffer))
end

const bufsize = 500
buffer = Array(Uint8,bufsize);
fill!(buffer,0);

include("float.jl")
include("fastdtoa.jl")
include("fastfixedtoa.jl")
include("bignum-dtoa.jl")

# Huge precomputed tests; 100,000 each
if !isdefined(:ShortestTestNumbers)
  include("gay-shortest.jl")
end
if !isdefined(:ShortestSingleTestNumbers)
  include("gay-shortest-single.jl")
end
if !isdefined(:PrecisionTestNumbers)
  include("gay-precision.jl")
end
if !isdefined(:FixedTestNumbers)
  include("gay-fixed.jl")
end  

function test(t::PrecomputedShortest,buffer,f)
    status,len,point,buffer = f(t.v,Grisu.SHORTEST,0,buffer)
    if status
      @test t.representation == bytestring(pointer(buffer))
      @test t.decimal_point == point 
    end
end
function test(t::PrecomputedShortestSingle,buffer,f)
    status,len,point,buffer = f(t.v,Grisu.SHORTEST,0,buffer)
    if status
      @test t.representation == bytestring(pointer(buffer))
      @test t.decimal_point == point 
    end
end
function test(t::PrecomputedFixed,buffer,f)
    n = t.number_digits
    status,len,point,buffer = f(t.v,Grisu.FIXED,n,buffer)
    if status
      @test n >= len - point - 1
      @test t.representation == trimrep(buffer)
      @test t.decimal_point == point
    end
end
function test(t::PP,buffer,f)
    n = t.number_digits
    status,len,point,buffer = f(t.v,Grisu.PRECISION,n,buffer)
    if status
      @test t.number_digits >= len-1
      @test t.representation == trimrep(buffer)
      @test t.decimal_point == point
    end
end

function test(tests,f)
  const bufsize = 500
  buffer = Array(Uint8,bufsize);
  fill!(buffer,0);
  iter = 1
  for t in tests
    test(t,buffer,f)
    fill!(buffer,0);
    iter += 1
  end
  return iter
end

@time test(ShortestTestNumbers,Grisu.fastdtoa)
@time test(ShortestSingleTestNumbers,Grisu.fastdtoa)
@time test(PrecisionTestNumbers,Grisu.fastdtoa)
@time test(FixedTestNumbers,Grisu.fastfixedtoa)

@time test(ShortestTestNumbers,Grisu.bignumdtoa)
@time test(ShortestSingleTestNumbers,Grisu.bignumdtoa)
@time test(PrecisionTestNumbers,Grisu.bignumdtoa)
@time test(FixedTestNumbers,Grisu.bignumdtoa)

include("dtoa.jl")