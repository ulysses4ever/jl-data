function test_precision_clenshaw_rule(a,b,g,integral, n)
  exact = integral(b) - integral(a)
  approx = clenshaw_rule(g, a, b, n)
  @test_approx_eq_eps(exact, approx, 1e-10)
  approx2 = clenshaw_rule2(g, a, b, n)  
  @test_approx_eq_eps(exact, approx, 1e-10)
end

function test_clenshaw_rule()
    g1(x) = sin(x)
    integral1(x) = -cos(x)
    (a, b, n) = (0, pi, 12)
    test_precision_clenshaw_rule(a, b, g1, integral1, n)

    g2(x) = 1/(1+x^2)
    integral2(x) = atan(x)
    (a, b, n) = (-1, 1, 20)
    test_precision_clenshaw_rule(a, b, g2, integral2, n)

    g3(x) = exp(x)
    integral3(x) = exp(x)
    (a, b, n) = (0, 1, 8)
    test_precision_clenshaw_rule(a, b, g3, integral3, n)
end

test_clenshaw_rule()