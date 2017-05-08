export zero_to_inf
export double_inf
export SR_inf_well

function zero_to_inf (f,n)
approx=0

s=2.0^n

h=4.5/2.0^n

x(k)=e^(pi*sinh(k*h))
w(k)=x(k)*pi*cosh(k*h)

for k=[-s:s-1]
  approx+=(f(x(k))*w(k)+f(x(k+1))*w(k+1))*h/2
end
return approx
end

function double_inf (f,n)
approx=0

s=2.0^n

h=4.5/2.0^n

x(k)=sinh(pi*sinh(k*h)/2)
w(k)=cosh(pi*sinh(k*h)/2)*pi*cosh(k*h)/2

for k=[-s:s-1]
  approx+=(f(x(k))*w(k)+f(x(k+1))*w(k+1))*h/2
end
return approx
end

function SR_inf_well (f,a,b,n)
  x(t)=1/t
  g(t)=f(x(t))/t^2
  approx=SR(g,1/b,1/a,n)
  return approx
end

