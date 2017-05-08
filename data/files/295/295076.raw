function test_precision_trapezoidal_rule(a,b,g,integral)
  exact = integral(b) - integral(a)
  approx = trapezoidal_rule(g, a, b, n = 1e6)
  @test_approx_eq_eps(exact, approx, 1e-10)
end

function test_precision_simpsons_rule(a,b,g,integral)
  exact = integral(b) - integral(a)
  approx = simpsons_rule(g, a, b, n = 1e6)
  @test_approx_eq_eps(exact, approx, 1e-12)
end

function test_precision_simpsons_rule_2(a,b,g,integral)
  exact = integral(b) - integral(a)
  approx = simpsons_rule(g, a, b, n = 1e6-1)
  @test_approx_eq_eps(exact, approx, 1e-12)
end

function test_closed_formulas()
  b = 1
  for a = -1:0

    g1(x) = x
    integral1(x) = x^2/2
    test_precision_trapezoidal_rule(a, b, g1, integral1)
    test_precision_simpsons_rule(a, b, g1,integral1)
    test_precision_simpsons_rule_2(a, b, g1,integral1)

    g2(x) = x^2
    integral2(x) = x^3/3
    test_precision_trapezoidal_rule(a, b, g2, integral2)
    test_precision_simpsons_rule(a, b, g2, integral2)

    g3(x) = 5x+1
    integral3(x) = x^2*5/2+x
    test_precision_trapezoidal_rule(a, b, g3, integral3)
    test_precision_simpsons_rule(a, b, g3, integral3)

    g4(x) = sin(x)
    integral4(x) = -cos(x)
    test_precision_trapezoidal_rule(a, b, g4, integral4)
    test_precision_simpsons_rule(a, b, g4, integral4)

    g5(x) = 1/(1+x^2)
    integral5(x) = atan(x)
    test_precision_trapezoidal_rule(a, b, g5, integral5)
    test_precision_simpsons_rule(a, b, g5, integral5)

    g6(x) = e^x
    integral6(x) = e^x
    test_precision_trapezoidal_rule(a, b, g6, integral6)
    test_precision_simpsons_rule(a, b, g6, integral6)
  end
end

test_closed_formulas()