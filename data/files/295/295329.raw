function sinh_tanh(f,a,b,n)

approx=0

s=2.0^n

h=4.0/2.0^n

x(t)=(a+b+t*(b-a))/2.0

g(t)=f(x(t))*(b-a)/2.0

for k=[-s:s]

  w_k=h*pi*cosh(k*h)/(2.0*cosh((pi*sinh(k*h))/2.0)^2.0)

  x_k=tanh(pi*sinh(k*h)/2.0)

  approx+=g(x_k)*w_k

end
return approx
end

  
  