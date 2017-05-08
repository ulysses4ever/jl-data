function test_precision_clenshaw_rule(a,b,g,integral, N)
  exact = integral(b) - integral(a)
  approx = clenshaw_rule(g, a, b, N = N)
  @test_approx_eq_eps(exact, approx, 1e-10)
end

function test_clenshaw_rule()
    g1(x) = sin(x)
    integral1(x) = -cos(x)
    (a, b, N) = (0, pi, 12)
    test_precision_clenshaw_rule(a, b, g1, integral1, N)

    g2(x) = 1/(1+x^2)
    integral2(x) = atan(x)
    (a, b, N) = (-1, 1, 20)
    test_precision_clenshaw_rule(a, b, g2, integral2, N)

    g3(x) = exp(x)
    integral3(x) = exp(x)
    (a, b, N) = (0, 1, 8)
    test_precision_clenshaw_rule(a, b, g3, integral3, N)
end

test_clenshaw_rule()