function test_precision_simpson1(g, a, b, exact)
  approx=adaptive_simpson(g, a, b, tol = 1.0e-14, N = 512)
  @test_approx_eq_eps(exact, approx, 1.0e-14)
end
function test_precision_simpson2(g, a, b, exact)
  approx=adaptive_simpson2(g, a, b, tol = 1.0e-14)
  @test_approx_eq_eps(exact, approx, 1.0e-14)
end

function test_adaptive()
  g1(t) = t*log(1 + t)
  (a, b) = (0, 1)
  exact = 1/4
  test_precision_simpson1(g1, a, b, exact)
  test_precision_simpson2(g1, a, b, exact)

  g2(t) = t^2*atan(t)
  (a, b) = (0, 1)
  exact = (pi - 2 + 2log(2))/12
  test_precision_simpson1(g2, a, b, exact)
  test_precision_simpson2(g2, a, b, exact)

  g3(t) = exp(t)
  (a, b) = (0, pi/2)
  exact = exp(pi/2) - 1
  test_precision_simpson1(g3, a, b, exact)
  test_precision_simpson2(g3, a, b, exact)

  g4(t) = 1/(1 + 25t^2)
  (a, b) = (-1, 1)
  exact = atan(5)/5 - atan(-5)/5
  test_precision_simpson1(g4, a, b, exact)
  test_precision_simpson2(g4, a, b, exact)
end

test_adaptive()