function test_precision(g, exact)
  approx = zero_to_inf(g, 12)
  @test_approx_eq_eps(exact, approx, 1e-6)
end

function test_sinh_tanh()

  g(t) = 1/(1+t^2)
  exact = pi/2
  test_precision(g, exact)

  g(t) = e^(-t)/sqrt(t)
  exact = sqrt(pi)
  test_precision(g, exact)

  g(t) = e^(-t^2/2)
  exact = sqrt(pi/2)
  test_precision(g, exact)

  g(t) = e^(-t)*cos(t)
  exact = 1/2
  test_precision(g, exact)

end

test_sinh_tanh()
