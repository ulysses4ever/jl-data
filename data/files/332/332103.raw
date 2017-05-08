using Base.Test

sizes = 5:5:500

print("Testing null space with Δ=∞... ")
# Positive definite test
# Large Δ so it's easily verifiable
Δ = Inf
for n = sizes
  m = round(Int,n/2);
  G = randn(n,n);
  G = G*G' + eye(n);
  g = randn(n);
  A = randn(m,n);
  (Q,R) = qr(A', thin=false);
  Z = Q[:,m+1:n];
  sol = -Z*((Z'*G*Z)\(Z'*g));

  x, qx, k = QuadProg.solve(G, g, A, Δ)
  @test_approx_eq_eps x sol 1e-8
  x, qx, k = QuadProg.solve(G, g, Z, Δ, null_matrix = true, ortho_null = true)
  @test_approx_eq_eps x sol 1e-8
  v = rand(n-m)
  x, qx, k = QuadProg.solve(G, g, Z.*v', Δ, null_matrix = true, ortho_null = false)
  @test_approx_eq_eps x sol 1e-8
end
println("passed")

print("Testing null space with Δ>|g_p|... ")
for n = sizes
  m = round(Int,n/2);
  G = randn(n,n);
  G = G*G' + eye(n);
  g = randn(n);
  A = randn(m,n);
  (Q,R) = qr(A', thin=false);
  Z = Q[:,m+1:n];
  dcp = -Z*Z'*g
  dcp = -dcp*dot(g,dcp)/dot(dcp,G*dcp)
  Δ = norm(dcp)*1.1

  q(d) = 0.5*dot(d,G*d) + dot(d,g)
  x, qx, k = QuadProg.solve(G, g, A, Δ)
  @test norm(A*x) < 1e-12
  @test q(x) < q(dcp)
  x, qx, k = QuadProg.solve(G, g, Z, Δ, null_matrix = true, ortho_null = true)
  @test norm(A*x) < 1e-12
  @test q(x) < q(dcp)
  v = rand(n-m)
  x, qx, k = QuadProg.solve(G, g, Z.*v', Δ, null_matrix = true, ortho_null = false)
  @test norm(A*x) < 1e-12
  @test q(x) < q(dcp)
end
println("passed")

print("Testing null space with Δ<|g_p|... ")
for n = sizes
  m = round(Int,n/2);
  G = randn(n,n);
  G = G*G' + eye(n);
  g = randn(n);
  A = randn(m,n);
  (Q,R) = qr(A', thin=false);
  Z = Q[:,m+1:n];
  dcp = -Z*Z'*g
  dcp = dcp*dot(g,dcp)/dot(dcp,G*dcp)
  Δ = norm(dcp)*0.9

  x, qx, k = QuadProg.solve(G, g, A, Δ)
  @test k == 1
  x, qx, k = QuadProg.solve(G, g, Z, Δ, null_matrix = true, ortho_null = true)
  @test k == 1
  v = rand(n-m)
  x, qx, k = QuadProg.solve(G, g, Z.*v', Δ, null_matrix = true, ortho_null = false)
  @test k == 1
end
println("passed")

print("Testing null space with variable Δ and indefinite matrix... ")
for n = sizes
  m = round(Int, n/2);
  Λ = linspace(-1-rand(), 100*rand(), n)
  (Q,R) = qr(rand(n,n))
  G = Q*diagm(Λ)*Q'
  g = randn(n)
  A = randn(m,n)
  (Q,R) = qr(A', thin=false);
  Z = Q[:,m+1:n];
  dcp = -Z*Z'*g
  λ = dot(dcp,dcp)/dot(dcp,G*dcp)
  Δ = (0.9+5*rand())*λ*norm(dcp)
  dcp = dcp*min(λ, Δ/norm(dcp))

  q(d) = 0.5*dot(d,G*d) + dot(d,g)
  x, qx, k = QuadProg.solve(G, g, A, Δ)
  @test q(x) <= q(dcp) + 1e-12
  x, qx, k = QuadProg.solve(G, g, Z, Δ, null_matrix = true, ortho_null = true)
  @test q(x) <= q(dcp) + 1e-12
  v = rand(n-m)
  x, qx, k = QuadProg.solve(G, g, Z.*v', Δ, null_matrix = true, ortho_null = false)
  @test q(x) <= q(dcp) + 1e-12
end
println("passed")
