function test_precision_trapezoidal_rule(a,b,g,integral)
  exact = integral(b) - integral(a)
  approx = trapezoidal_rule(g, a, b, 1e6)
  @test_approx_eq_eps(exact, approx, 1e-10)
end

function test_precision_simpsons_rule(a,b,g,integral)
  exact = integral(b) - integral(a)
  approx = simpsons_rule(g, a, b, 1e6)
  @test_approx_eq_eps(exact, approx, 1e-12)
end

function test_closed_formulas()
  b = 1
  for a = -1:0

    g(x) = x
    integral(x) = x^2/2
    test_precision_trapezoidal_rule(a, b, g, integral)
    test_precision_simpsons_rule(a,b,g,integral)

    g(x) = x^2
    integral(x) = x^3/3
    test_precision_trapezoidal_rule(a, b, g, integral)
    test_precision_simpsons_rule(a,b,g,integral)

    g(x) = 5x+1
    integral(x) = x^2*5/2+x
    test_precision_trapezoidal_rule(a, b, g, integral)
    test_precision_simpsons_rule(a,b,g,integral)

    g(x) = sin(x)
    integral(x) = -cos(x)
    test_precision_trapezoidal_rule(a, b, g, integral)
    test_precision_simpsons_rule(a,b,g,integral)

    g(x) = 1/(1+x^2)
    integral(x) = atan(x)
    test_precision_trapezoidal_rule(a, b, g, integral)
    test_precision_simpsons_rule(a,b,g,integral)

    g(x) = e^x
    integral(x) = e^x
    test_precision_trapezoidal_rule(a, b, g, integral)
    test_precision_simpsons_rule(a,b,g,integral)
  end
end

test_closed_formulas()