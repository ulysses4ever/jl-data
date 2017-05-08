function test_precision(g, exact)
  approx=double_inf(g, 10)
  @test_approx_eq_eps(exact, approx, 1e-7)
end

function test_double_inf()

  g(t) = 1/(1 + t^2)
  exact = pi*1.0
  test_precision(g, exact)

  g(t) = 1/(25 + 4t^2)
  exact = pi/10.0
  test_precision(g, exact)

end

test_double_inf()