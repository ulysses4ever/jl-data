
# Start by checking the byte-order.
ordered = 0x0123456789ABCDEF
@test 3512700564088504e-318 == reinterpret(Float64,ordered)

min_double64 = 0x0000000000000001
@test 5e-324 == reinterpret(Float64,min_double64)

max_double64 = 0x7fefffffffffffff
@test 1.7976931348623157e308 == reinterpret(Float64,max_double64)

# Start by checking the byte-order.
ordered = 0x01234567
@test float32(2.9988165487136453e-38) == reinterpret(Float32,ordered)

min_float32 = 0x00000001
@test float32(1.4e-45) == reinterpret(Float32,min_float32)

max_float32 = 0x7f7fffff
@test float32(3.4028234e38) == reinterpret(Float32,max_float32)

ordered = 0x0123456789ABCDEF
diy_fp  = Grisu.Float(reinterpret(Float64,ordered))
@test 0x12 - 0x3FF - 52 == uint64(diy_fp.e)
# The 52 mantissa bits, plus the implicit 1 in bit 52 as a UINT64.
@test 0x0013456789ABCDEF== diy_fp.s

min_double64 = 0x0000000000000001
diy_fp  = Grisu.Float(reinterpret(Float64,min_double64))
@test -0x3FF - 52 + 1 == uint64(diy_fp.e)
# This is a denormal so no hidden bit.
@test 1 == diy_fp.s

max_double64 = 0x7fefffffffffffff
diy_fp  = Grisu.Float(reinterpret(Float64,max_double64))
@test 0x7FE - 0x3FF - 52 == uint64(diy_fp.e)
@test 0x001fffffffffffff== diy_fp.s

ordered = 0x01234567
diy_fp  = Grisu.Float(reinterpret(Float32,ordered))
@test 0x2 - 0x7F - 23 == uint64(diy_fp.e)
# The 23 mantissa bits, plus the implicit 1 in bit 24 as a uint32_t.
@test 0xA34567 == uint64(diy_fp.s)

min_float32 = 0x00000001
diy_fp  = Grisu.Float(reinterpret(Float32,min_float32))
@test -0x7F - 23 + 1 == uint64(diy_fp.e)
# This is a denormal so no hidden bit.
@test 1 == uint64(diy_fp.s)

max_float32 = 0x7f7fffff
diy_fp  = Grisu.Float(reinterpret(Float32,max_float32))
@test 0xFE - 0x7F - 23 == uint64(diy_fp.e)
@test 0x00ffffff == uint64(diy_fp.s)

ordered = 0x0123456789ABCDEF
diy_fp  = Grisu.normalize(Grisu.Float(reinterpret(Float64,ordered)))
@test 0x12 - 0x3FF - 52 - 11 == uint64(diy_fp.e)
@test 0x0013456789ABCDEF<< 11 == diy_fp.s

min_double64 = 0x0000000000000001
diy_fp  = Grisu.normalize(Grisu.Float(reinterpret(Float64,min_double64)))
@test -0x3FF - 52 + 1 - 63 == uint64(diy_fp.e)
# This is a denormal so no hidden bit.
@test 0x8000000000000000== diy_fp.s

max_double64 = 0x7fefffffffffffff
diy_fp  = Grisu.normalize(Grisu.Float(reinterpret(Float64,max_double64)))
@test 0x7FE - 0x3FF - 52 - 11 == uint64(diy_fp.e)
@test (0x001fffffffffffff<< 11) == diy_fp.s

min_double64 = 0x0000000000000001
@test Grisu.isdenormal(reinterpret(Float64,min_double64))
bits = 0x000FFFFFFFFFFFFF
@test Grisu.isdenormal(reinterpret(Float64,bits))
bits = 0x0010000000000000
@test !Grisu.isdenormal(reinterpret(Float64,bits))

min_float32 = 0x00000001
@test Grisu.isdenormal(reinterpret(Float32,min_float32))
bits = 0x007FFFFF
@test Grisu.isdenormal(reinterpret(Float32,bits))
bits = 0x00800000
@test !Grisu.isdenormal(reinterpret(Float32,bits))

diy_fp = Grisu.normalize(Grisu.Float(1.5))
boundary_minus, boundary_plus = Grisu.normalizedbound(1.5)
@test diy_fp.e == boundary_minus.e
@test diy_fp.e == boundary_plus.e
# 1.5 does not have a significand of the form 2^p (for some p).
# Therefore its boundaries are at the same distance.
@test diy_fp.s - boundary_minus.s == boundary_plus.s - diy_fp.s
@test (1 << 10) == diy_fp.s - boundary_minus.s

diy_fp = Grisu.normalize(Grisu.Float(1.0))
boundary_minus, boundary_plus = Grisu.normalizedbound(1.0)
@test diy_fp.e == boundary_minus.e
@test diy_fp.e == boundary_plus.e
# 1.0 does have a significand of the form 2^p (for some p).
# Therefore its lower boundary is twice as close as the upper boundary.
@test boundary_plus.s - diy_fp.s > diy_fp.s - boundary_minus.s
@test (1 << 9) == diy_fp.s - boundary_minus.s
@test (1 << 10) == boundary_plus.s - diy_fp.s

min_double64 = 0x0000000000000001
diy_fp = Grisu.normalize(Grisu.Float(reinterpret(Float64,min_double64)))
boundary_minus, boundary_plus = Grisu.normalizedbound(reinterpret(Float64,min_double64))
@test diy_fp.e == boundary_minus.e
@test diy_fp.e == boundary_plus.e
# min-value does not have a significand of the form 2^p (for some p).
# Therefore its boundaries are at the same distance.
@test diy_fp.s - boundary_minus.s == boundary_plus.s - diy_fp.s
# Denormals have their boundaries much closer.
@test (uint64(1) << 62) == diy_fp.s - boundary_minus.s

smallest_normal64 = 0x0010000000000000
diy_fp = Grisu.normalize(reinterpret(Float64,smallest_normal64))
boundary_minus, boundary_plus = Grisu.normalizedbound(reinterpret(Float64,smallest_normal64))
@test diy_fp.e == boundary_minus.e
@test diy_fp.e == boundary_plus.e
# Even though the significand is of the form 2^p (for some p), its boundaries
# are at the same distance. (This is the only exception).
@test diy_fp.s - boundary_minus.s == boundary_plus.s - diy_fp.s
@test (1 << 10) == diy_fp.s - boundary_minus.s

largest_denormal64 = 0x000FFFFFFFFFFFFF
diy_fp = Grisu.normalize(reinterpret(Float64,largest_denormal64))
boundary_minus, boundary_plus = Grisu.normalizedbound(reinterpret(Float64,largest_denormal64))
@test diy_fp.e == boundary_minus.e
@test diy_fp.e == boundary_plus.e
@test diy_fp.s - boundary_minus.s == boundary_plus.s - diy_fp.s
@test (1 << 11) == diy_fp.s - boundary_minus.s

max_double64 = 0x7fefffffffffffff
diy_fp = Grisu.normalize(reinterpret(Float64,max_double64))
boundary_minus, boundary_plus = Grisu.normalizedbound(reinterpret(Float64,max_double64))
@test diy_fp.e == boundary_minus.e
@test diy_fp.e == boundary_plus.e
# max-value does not have a significand of the form 2^p (for some p).
# Therefore its boundaries are at the same distance.
@test diy_fp.s - boundary_minus.s == boundary_plus.s - diy_fp.s
@test (1 << 10) == diy_fp.s - boundary_minus.s

kOne64 = uint64(1)
diy_fp  = Grisu.normalize(Grisu.Float(float32(1.5)))
boundary_minus, boundary_plus = Grisu.normalizedbound(float32(1.5))
@test diy_fp.e == boundary_minus.e
@test diy_fp.e == boundary_plus.e
# 1.5 does not have a significand of the form 2^p (for some p).
# Therefore its boundaries are at the same distance.
@test diy_fp.s - boundary_minus.s == boundary_plus.s - diy_fp.s
# Normalization shifts the significand by 8 bits. Add 32 bits for the bigger
# data-type, and remove 1 because boundaries are at half a ULP.
@test (kOne64 << 39) == diy_fp.s - boundary_minus.s

diy_fp  = Grisu.normalize(Grisu.Float(float32(1.0)))
boundary_minus, boundary_plus = Grisu.normalizedbound(float32(1.0))
@test diy_fp.e == boundary_minus.e
@test diy_fp.e == boundary_plus.e
# 1.0 does have a significand of the form 2^p (for some p).
# Therefore its lower boundary is twice as close as the upper boundary.
@test boundary_plus.s - diy_fp.s > diy_fp.s - boundary_minus.s
@test (kOne64 << 38) == diy_fp.s - boundary_minus.s
@test (kOne64 << 39) == boundary_plus.s - diy_fp.s

min_float32 = 0x00000001
diy_fp  = Grisu.normalize(Grisu.Float(reinterpret(Float32,min_float32)))
boundary_minus, boundary_plus = Grisu.normalizedbound(reinterpret(Float32,min_float32))
@test diy_fp.e == boundary_minus.e
@test diy_fp.e == boundary_plus.e
# min-value does not have a significand of the form 2^p (for some p).
# Therefore its boundaries are at the same distance.
@test diy_fp.s - boundary_minus.s == boundary_plus.s - diy_fp.s
# Denormals have their boundaries much closer.
@test (kOne64 << 62) == diy_fp.s - boundary_minus.s

smallest_normal32 = 0x00800000
diy_fp  = Grisu.normalize(Grisu.Float(reinterpret(Float32,smallest_normal32)))
boundary_minus, boundary_plus = Grisu.normalizedbound(reinterpret(Float32,smallest_normal32))
@test diy_fp.e == boundary_minus.e
@test diy_fp.e == boundary_plus.e
# Even though the significand is of the form 2^p (for some p), its boundaries
# are at the same distance. (This is the only exception).
@test diy_fp.s - boundary_minus.s == boundary_plus.s - diy_fp.s
@test (kOne64 << 39) == diy_fp.s - boundary_minus.s

largest_denormal32 = 0x007FFFFF
diy_fp  = Grisu.normalize(Grisu.Float(reinterpret(Float32,largest_denormal32)))
boundary_minus, boundary_plus = Grisu.normalizedbound(reinterpret(Float32,largest_denormal32))
@test diy_fp.e == boundary_minus.e
@test diy_fp.e == boundary_plus.e
@test diy_fp.s - boundary_minus.s == boundary_plus.s - diy_fp.s
@test (kOne64 << 40) == diy_fp.s - boundary_minus.s

max_float32 = 0x7f7fffff
diy_fp  = Grisu.normalize(Grisu.Float(reinterpret(Float32,max_float32)))
boundary_minus, boundary_plus = Grisu.normalizedbound(reinterpret(Float32,max_float32))
@test diy_fp.e == boundary_minus.e
@test diy_fp.e == boundary_plus.e
# max-value does not have a significand of the form 2^p (for some p).
# Therefore its boundaries are at the same distance.
@test diy_fp.s - boundary_minus.s == boundary_plus.s - diy_fp.s
@test (kOne64 << 39) == diy_fp.s - boundary_minus.s