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