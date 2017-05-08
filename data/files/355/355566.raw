function test_precision(g, exact)
  approx = zero_to_inf(g, n = 9)
  @test_approx_eq_eps(exact, approx, 1e-14)
end

function test_sinh_tanh()

  g1(t) = 1/(1+t^2)
  exact = pi/2
  test_precision(g1, exact)

  g2(t) = e^(-t)/sqrt(t)
  exact = sqrt(pi)
  test_precision(g2, exact)

  g3(t) = e^(-t^2/2)
  exact = sqrt(pi/2)
  test_precision(g3, exact)

  g4(t) = e^(-t)*cos(t)
  exact = 1/2
  test_precision(g4, exact)

end

test_sinh_tanh()
