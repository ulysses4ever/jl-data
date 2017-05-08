function test_precision_half_inf(g, exact)
  approx = half_inf(g, n = 9)
  @test_approx_eq_eps(exact, approx, 1.0e-14)
end

function test_precision_double_inf(g, exact)
  approx=double_inf(g, n = 10)
  @test_approx_eq_eps(exact, approx, 1.0e-10)
end

function test_precision_simpsons_inf(g, a, b, exact)
  approx = simpsons_inf(g, a, b, n = 10^4)
  @test_approx_eq_eps(exact, approx, 1.0e-14)
end

function test_half_inf()
  g1(t) = 1/(1 + t^2)
  exact = pi/2
  test_precision_half_inf(g1, exact)

  g2(t) = exp(-t)/sqrt(t)
  exact = sqrt(pi)
  test_precision_half_inf(g2, exact)

  g3(t) = exp(-t^2/2)
  exact = sqrt(pi/2)
  test_precision_half_inf(g3, exact)

  g4(t) = exp(-t)*cos(t)
  exact = 1/2
  test_precision_half_inf(g4, exact)
end

function test_double_inf()
  g1(t) = 1/(1 + t^2)
  exact = Float64(pi)
  test_precision_double_inf(g1, exact)

  g2(t) = 1/(25 + 4t^2)
  exact = pi/10
  test_precision_double_inf(g2, exact)
end

function test_simpsons_inf()
  g1(x) = x/exp(x/2)
  exact = 6/exp(1/2)
  (a, b) = (1, 1e60)
  test_precision_simpsons_inf(g1, a, b, exact)

  g2(x) = 3x^2*exp(-x^3)
  exact = 1/e
  (a, b) = (1, 1e60)
  test_precision_simpsons_inf(g2, a, b, exact)
end

test_half_inf()
test_double_inf()
test_simpsons_inf()