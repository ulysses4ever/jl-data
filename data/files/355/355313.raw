function test_precision_gauss(g, a, b, exact)
  approx = gauss_legendre(g, a, b, n = 128)
  @test_approx_eq_eps(exact, approx, 5.0e-16)
  approx = gauss_lobatto(g, a, b, n = 128)
  @test_approx_eq_eps(exact, approx, 5.0e-16)
end

function test_gauss()
  g1(t) = t*log(1 + t)
  (a, b) = (0, 1.0)
  exact = 1/4
  test_precision_gauss(g1, a, b, exact)

  g2(t) = t^2*atan(t)
  (a, b) = (0, 1.0)
  exact = (pi - 2 + log(4))/12
  test_precision_gauss(g2, a, b, exact)

  g3(t) = exp(t)
  (a, b) = (0, 1.0)
  exact = e - 1
  test_precision_gauss(g3, a, b, exact)
end

test_gauss()