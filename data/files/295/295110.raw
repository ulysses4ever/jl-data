function test_precision_simpsons_rule_inf(g, a, b, exact)
  approx = simpsons_rule_inf(g, a, b, n = 1e4)
  @test_approx_eq_eps(exact, approx, 1e-14)
end

function test_simpsons_rule_inf()

  g1(x) = x/e^(x/2)
  exact = 6/e^(1/2)
  (a, b) = (1, 1e60)
  test_precision_simpsons_rule_inf(g1, a, b, exact)

  g2(x) = 3x^2*e^(-x^3)
  exact = 1/e
  (a, b) = (1,1e60)
  test_precision_simpsons_rule_inf(g2, a, b, exact)

end

test_simpsons_rule_inf()
