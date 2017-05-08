function test_precision(g, a, b, exact)
  approx = simpsons_rule_inf(g, a, b, 1000)
  @test_approx_eq_eps(exact, approx, 1e-7)
end

function test_simpsons_rule_inf()

  g(x) = x/e^(x/2)
  exact = 6/e^(1/2)
  (a, b) = (1, 1e50)
  test_precision(g, a, b, exact)

  g(x) = 3x^2*e^(-x^3)
  exact = 1/e
  (a, b) = (1,1e50)
  test_precision(g, a, b, exact)

end

test_simpsons_rule_inf()
