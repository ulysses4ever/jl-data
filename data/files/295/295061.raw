using NumInt
using Base.Test

function test_precision(func,a,b,g,integral)
  exact=integral(b)-integral(a)
  approx=func(g,a,b,2000)
  @test_approx_eq_eps(exact,approx,1e-6)
end

function test_closed_formulas()
  for func=[trapezoidal_rule,simpsons_rule]
  b=1
  for a=[-1,0]

    g(x)=x
    integral(x)=x^2/2
    test_precision(func,a,b,g,integral)

    g(x)=x^2
    integral(x)=x^3/3
    test_precision(func,a,b,g,integral)

    g(x)=5x+1
    integral(x)=x^2*5/2+x
    test_precision(func,a,b,g,integral)

    g(x)=sin(x)
    integral(x)=-cos(x)
    test_precision(func,a,b,g,integral)

    g(x)=1/(1+x^2)
    integral(x)=atan(x)
    test_precision(func,a,b,g,integral)

    g(x)=e^x
    integral(x)=e^x
    test_precision(func,a,b,g,integral)
  end
  end
end

test_closed_formulas()