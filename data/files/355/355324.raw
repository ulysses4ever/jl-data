function test_precision(g, a, b, exact)
  approx=gaussian_quadrature(g, a, b; n = 1)
  @test_approx_eq_eps(exact, approx, 1e-16)
end

function test_gaussian_quadrature()

  g(t) = t^2
  exact = 1/3
  test_precision(g, 0, 1, exact)

  g(t) = 7t^3
  exact = 0.0
  test_precision(g, -1, 1, exact)

end

test_gaussian_quadrature()