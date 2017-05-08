using NumInt

function test_precision(g,a,b,exact)
  approx=simpsons_rule_adapted(g,a,b,1e-6,25)
  @test_approx_eq_eps(exact,approx,1e-6)
end

function test_simpsons_rule_adapted()

g(t)=t*log(1+t)
(a,b)=(0,1)
exact=1/4
test_precision(g,a,b,exact)

g(t)=t^2*atan(t)
(a,b)=(0,1)
exact=(pi-2+2log(2))/12
test_precision(g,a,b,exact)

g(t)=e^t
(a,b)=(0,pi/2)
exact=e^(pi/2)-1
test_precision(g,a,b,exact)

g(t)=1/(1+25t^2)
(a,b)=(-1,1)
exact=atan(5)/5-atan(-5)/5
test_precision(g,a,b,exact)

end

test_simpsons_rule_adapted()