facts("Fused multiply-add") do
  context("Float32") do
    @fact fma(9.982642f2, 1.0018032f-3, -1f0) => 6.4295644f-5
    # The correct result is 6.432965f-5
  end

  context("Float64") do
    @fact fma(9.9826421385793060e2, 1.0018032458425164e-3, -1e0) => 6.432965130279311e-5
    # The correct results is 6.432965130281577e-5
  end
end

facts("Error-free fma") do
  a, b, c = (5.462577550234297e6,-2.7361786238478348e6,-2.6708293270125585e6)
  x, y, z = err_fma(a, b, c)
  @fact BigFloat(a)*BigFloat(b)+BigFloat(c) => BigFloat(x)+BigFloat(y)+BigFloat(z)
end

facts("Nearest error fma") do
  t = (875.9068547049504,18.125507806255648,52973.433931470114)
  x, y, z = err_fma(t...)
  @fact err_fma_nearest(t...) => x, y
end

facts("Approximated error fma") do
  a, b, c = (113.02200249893586,55.716264204969825,9141.765779129744)
  x, y = err_fma_approx(a, b, c)
  @fact BigFloat(a)*BigFloat(b)+BigFloat(c) => roughly(BigFloat(x)+BigFloat(y), ldexp(14*abs(x),-53))
end
