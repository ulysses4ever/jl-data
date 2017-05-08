facts("Float split") do
  context("Float32") do
    hi, lo = fsplit(float32(0x8017))
    # assuming hi and lo different from zero
    @fact exponent(hi)-exponent(lo) => greater_than_or_equal(12)
    @fact trailing_zeros(int32(ldexp(significand(hi), 23))) => greater_than_or_equal(12)
  end

  context("Float64") do
    hi, lo = fsplit(float64(0x8000005))
    # assuming hi and lo different from zero
    @fact exponent(hi)-exponent(lo) => greater_than_or_equal(27)
    @fact trailing_zeros(int64(ldexp(significand(hi), 52))) => greater_than_or_equal(27)
  end
end

facts("Error-free multiply") do
  a = float64(0x10000000000001)
  b = 3.0e0
  x, y = err_mul(a, b)
  @fact big(x)+big(y) => big(a)*big(b)
end

facts("Fast error-free multiply") do
  a = float64(0x10000000000001)
  b = 3.0e0
  @fact err_fast_mul(a, b) => err_mul(a, b)
end
