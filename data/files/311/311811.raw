facts("Fused multiply-add") do
  context("Float32") do
    a = float32(0x1000002)
    b = 3.0f0
    c = -float32(0x300000a)
    @fact fma(a, b, c) => big(a)*big(b)+big(c)
  end

  context("Float64") do
    a = float64(0x10000000000001)
    b = 3.0e0
    c = -float64(0x30000000000004)
    @fact fma(a, b, c) => big(a)*big(b)+big(c)
  end
end

facts("Error-free fma") do
  a = ldexp(float64(0x10000000000001), -52)
  b = ldexp(float64(0x10000000000001), -51)
  c = ldexp(float64(0x10000000000001), -48)

  context("Standard") do
    x, y, z = err_fma(a, b, c)
    @fact x => fma(a, b, c)
    @fact big(x)+big(y)+big(z) => big(a)*big(b)+big(c)
  end

  context("Compressed error") do
    x, y, z = err_fma_compr(a, b, c)
    @fact x => fma(a, b, c)
    @fact big(x)+big(y)+big(z) => big(a)*big(b)+big(c)
    # assuming non-zero y, z
    @fact exponent(y)-exponent(z) => greater_than_or_equal(53)
  end

  context("Nearest error") do
    x, y, z = err_fma(a, b, c)
    @fact err_fma_nearest(a, b, c) => x, y+z
  end

  context("Approximated error") do
    x, y = err_fma_approx(a, b, c)
    @fact big(a)*big(b)+big(c) => roughly(big(x)+big(y), ldexp(14*abs(x),-53))
  end
end
