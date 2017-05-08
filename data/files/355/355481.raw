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