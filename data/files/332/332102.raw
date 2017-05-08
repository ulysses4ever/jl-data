using Base.Test

# Large Delta so it's easily verifiable
Delta = Inf
# Positive definite test
for n = 10:10:10
  m = round(Int,n/2);
  G = randn(n,n);
  G = G*G' + eye(n);
  g = randn(n);
  A = randn(m,n);
  (Q,R) = qr(A', thin=false);
  Z = Q[:,m+1:n];
  sol = -Z*((Z'*G*Z)\(Z'*g));

  x, k = QuadProg.solve(G, g, A, Delta)
  @test_approx_eq_eps x sol 1e-8
  x, k = QuadProg.solve(G, g, Z, Delta, null_matrix = true, ortho_null = true)
  @test_approx_eq_eps x sol 1e-8
  v = rand(n-m)
  x, k = QuadProg.solve(G, g, Z.*v', Delta, null_matrix = true, ortho_null = false)
  @test_approx_eq_eps x sol 1e-8
end
