function test_precision_trapezoidal(a, b, g, integral)
  exact = integral(b) - integral(a)
  approx = trapezoidal_rule(g, a, b, n = 1e6)
  @test_approx_eq_eps(exact, approx, 1e-10)
end

function test_precision_simpsons(a, b, g, integral)
  exact = integral(b) - integral(a)
  approx = simpsons_rule(g, a, b, n = 1e6)
  @test_approx_eq_eps(exact, approx, 1e-12)
end

function test_precision_midpoint(a, b, g, integral)
  exact = integral(b) - integral(a)
  approx = midpoint_rule(g, a, b, n = 1e6)
  @test_approx_eq_eps(exact, approx, 1e-10)
end

function test_precision_simpsons_2(a, b, g, integral)
  exact = integral(b) - integral(a)
  approx = simpsons_rule(g, a, b, n = 1e6-1)
  @test_approx_eq_eps(exact, approx, 1e-12)
end

function test_precision_romberg(a, b, g, integral)
  exact = integral(b) - integral(a)
  approx = romberg_rule(g, a, b, 256)
  @test_approx_eq_eps(exact, approx, 1e-12)
end

function test_closed_formulas()
  b = 1
  for a = -1:0

    g1(x) = x^2
    integral1(x) = x^3/3
    test_precision_trapezoidal(a, b, g1, integral1)
    test_precision_simpsons(a, b, g1, integral1)
    test_precision_simpsons_2(a, b, g1, integral1)
    test_precision_midpoint(a, b, g1, integral1)
    test_precision_romberg(a, b, g1, integral1)

    g2(x) = sin(x)
    integral2(x) = -cos(x)
    test_precision_trapezoidal(a, b, g2, integral2)
    test_precision_simpsons(a, b, g2, integral2)
    test_precision_midpoint(a, b, g2, integral2)
    test_precision_romberg(a, b, g2, integral2)

    g3(x) = 1/(1+x^2)
    integral3(x) = atan(x)
    test_precision_trapezoidal(a, b, g3, integral3)
    test_precision_simpsons(a, b, g3, integral3)
    test_precision_midpoint(a, b, g3, integral3)
    test_precision_romberg(a, b, g3, integral3)

    g4(x) = exp(x)
    integral4(x) = exp(x)
    test_precision_trapezoidal(a, b, g4, integral4)
    test_precision_simpsons(a, b, g4, integral4)
    test_precision_midpoint(a, b, g4, integral4)
    test_precision_romberg(a, b, g4, integral4)
  end
end

test_closed_formulas()